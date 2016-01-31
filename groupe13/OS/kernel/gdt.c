//////////////////////////////////////////////////////////////////////////////////////////
/// \file kernel.c
/// \author Thierry Mourao
/// \author Sylvain Thullen
/// \author Sacha Conti
/// \date 29 november 2015
/// \brief Implementation of the kernel main function
//////////////////////////////////////////////////////////////////////////////////////////

#include "gdt.h"

#define GDT_INDEX_TO_SELECTOR(idx) ((idx) << 3)

// Task structures array
int tasks_nb = 8;
task_t tasks[8];

// GDT = Null + Code + Data + TSS + 8x (TSS + LDT) = 20
static gdt_entry_t gdt[20];

// Pointer on the GDT
static gdt_ptr_t gdt_ptr;

// Build and return a GDT entry given the various arguments (see Intel manuals).
static gdt_entry_t build_entry(uint32_t base, uint32_t limit, uint8_t type, uint8_t s, uint8_t db, uint8_t granularity, uint8_t dpl) {
	gdt_entry_t entry;
    // For a TSS and LDT, base is the addresse of the TSS/LDT structure
    // and limit is the size of the structure.
    entry.lim15_0 = limit & 0xffff;
    entry.base15_0 = base & 0xffff;
    entry.base23_16 = (base >> 16) & 0xff;
    entry.type = type;  // See TYPE_xxx flags
    entry.s = s;        // 1 for segments; 0 for system (TSS, LDT, gates)
    entry.dpl = dpl;    // privilege level
    entry.present = 1;  // present in memory
    entry.lim19_16 = (limit >> 16) & 0xf;
    entry.avl = 0;      // available for use
    entry.l = 0;        // should be 0 (64-bit code segment)
    entry.db = db;      // 1 for 32-bit code and data segments; 0 for system (TSS, LDT, gate)
    entry.granularity = granularity;  // granularity of the limit value: 0 = 1 byte; 1 = 4096 bytes
    entry.base31_24 = (base >> 24) & 0xff;
	return entry;
}

// Return a NULL entry.
static gdt_entry_t null_segment() {
	gdt_entry_t entry;
    memset(&entry, 0, sizeof(gdt_entry_t));
	return entry;
}

// Return a code segment specified by the base, limit and privilege level passed in arguments.
static gdt_entry_t code_segment(uint32_t base, uint32_t limit, uint8_t dpl) {
    return build_entry(base, limit, TYPE_CODE_EXECREAD, S_CODE_OR_DATA, DB_SEG, 1, dpl);
}

// Return a data segment specified by the base, limit and privilege level passed in arguments.
static gdt_entry_t data_segment(uint32_t base, uint32_t limit, uint8_t dpl) {
    return build_entry(base, limit, TYPE_DATA_READWRITE, S_CODE_OR_DATA, DB_SEG, 1, dpl);
}

// Return a TSS entry  specified by the TSS structure and privilege level passed in arguments.
// NOTE: a TSS entry can only reside in the GDT!
gdt_entry_t gdt_make_tss(tss_t *tss, uint8_t dpl) {
	return build_entry((uint32_t)tss, sizeof(tss_t)-1, TYPE_TSS, S_SYSTEM, DB_SYS, 0, dpl);
}

// Can only be set in the GDT!
gdt_entry_t gdt_make_ldt(uint32_t base, uint32_t limit, uint8_t dpl) {
	return build_entry(base, limit, TYPE_LDT, S_SYSTEM, DB_SYS, 0, dpl);
}

// Returns a GDT entry selector
uint gdt_entry_to_selector(gdt_entry_t *entry) {
	return GDT_INDEX_TO_SELECTOR(entry - gdt);
}

// Init a task in the GDT at specified index (LDT at index + 1)
void setup_task(int index) {

	static tss_t task_tss;
	static gdt_entry_t task_ldt[2];

	// Add the task's TSS and LDT to the GDT
	gdt[4 + 2 * index] = gdt_make_tss(&task_tss, DPL_KERNEL);
	gdt[5 + 2 * index] = gdt_make_ldt((uint32_t)task_ldt, sizeof(task_ldt)-1, DPL_KERNEL);
	int gdt_tss_sel = gdt_entry_to_selector(&gdt[4 + 2 * index]); 
	int gdt_ldt_sel = gdt_entry_to_selector(&gdt[5 + 2 * index]);
	
	// Define code and data segments in the LDT; both segments are overlapping
	uint32_t task_addr = 0x80000 + index * TASK_LIMIT;  // 8MB for each task
	int ldt_code_idx = 0;
	int ldt_data_idx = 1;
	uint limit = 0x10000;  // limit of 64KB
	task_ldt[ldt_code_idx] = code_segment(task_addr, limit / 4096, DPL_USER);  // code
	task_ldt[ldt_data_idx] = data_segment(task_addr, limit / 4096, DPL_USER);  // data + stack
	
	// Initialize the TSS fields
	// The LDT selector must point to the task's LDT
	task_tss.ldt_selector = gdt_ldt_sel;

	// Setup code and stack pointers
	task_tss.eip = 0;
	task_tss.esp = task_tss.ebp = limit;  // stack pointers

	// Code and data segment selectors are in the LDT
	task_tss.cs = GDT_INDEX_TO_SELECTOR(ldt_code_idx) | DPL_USER | LDT_SELECTOR;
	task_tss.ds = task_tss.es = task_tss.fs = task_tss.gs = task_tss.ss = GDT_INDEX_TO_SELECTOR(ldt_data_idx) | DPL_USER | LDT_SELECTOR;
	task_tss.eflags = 512;  // Activate hardware interrupts (bit 9)

	// Task's kernel stack
	static uchar task_kernel_stack[8192];
	task_tss.ss0 = GDT_KERNEL_DATA_SELECTOR;
	task_tss.esp0 = (uint32_t) (task_kernel_stack) + sizeof(task_kernel_stack);
	
	// Structure array update
	tasks[index].free = 0;
	tasks[index].addr = task_addr;
	tasks[index].task_tss  = task_tss;
	tasks[index].gdt_tss_sel = gdt_tss_sel;
	
}

// Executes a binary program
int exec(char* bin) {
	
	// Looking for free task
	int index = -1;
	for (int i = 0; i < tasks_nb; i++)
		if (!tasks[i].free) {
			index = i;
			tasks[i].free = 1;
			break;
		}
	if (index < 0) return 1;

	// Read program if existing
	if (file_exists(bin)) {
		
		// Copy binary program at the right address
		if (file_read(bin, (uint32_t*) tasks[index].addr)) return 3;
		
		// Commute to task with corresponding TSS as argument
		call_task(tasks[index].gdt_tss_sel); 
		
		// Structure array reset
		tasks[index].task_tss.eip = tasks[index].free         = 0;
		tasks[index].task_tss.esp = tasks[index].task_tss.ebp = TASK_LIMIT;  // stack pointers
		
		// End of routine
		return 0;
		
	}
	else return 2;
	
}

// Initialize the GDT
void gdt_init() {

	// Tasks setup
	for (int i = 0; i < tasks_nb; i++)
		setup_task(i);
		
	// Set the address and the size of the GDT in the pointer
	gdt_ptr.limit = sizeof(gdt);
	gdt_ptr.base = (uint32_t)&gdt;
	
	// Initializing the three segment descriptors in the GDT : NULL, code segment, data segment
	gdt[0] = null_segment();
	gdt[1] = code_segment(0, 1048575, DPL_KERNEL);
	gdt[2] = data_segment(0, 1048575, DPL_KERNEL);
	
	// gdt[3] : entry for initial kernel TSS (CPU state of first task saved there)
	static uint8_t initial_tss_kernel_stack[65536];  // 64KB of stack
	static tss_t initial_tss;
	gdt[3] = gdt_make_tss(&initial_tss, DPL_KERNEL);
	memset(&initial_tss, 0, sizeof(tss_t));
	initial_tss.ss0 = GDT_KERNEL_DATA_SELECTOR;
	initial_tss.esp0 = ((uint32_t) initial_tss_kernel_stack) + sizeof(initial_tss_kernel_stack);

	// Load the GDT
    gdt_flush(&gdt_ptr);
	
	// Load the task register to point to the initial TSS selector
	load_task_register(gdt_entry_to_selector(&gdt[3]));
	
	// Confirmation message
	set_text_color(LIGHT_GREEN);
	printf("OK\n");
	set_text_color(WHITE);
	
}