#include "idt.h"

// IDT
static idt_entry_t idt[IDT_ENTRIES];
// Pointer on the IDT
static idt_ptr_t idt_ptr;

// Function pointers arrays
// ISR
static void* isr_tab[CPU_EXCEPTS] = { _isr_0,  _isr_1,  _isr_2,  _isr_3,  _isr_4,  _isr_5,  _isr_6,  _isr_7,  _isr_8,  _isr_9, 
								     _isr_10, _isr_11, _isr_12, _isr_13, _isr_14, _isr_15, _isr_16, _isr_17, _isr_18, _isr_19, _isr_20};
// IRQ
static void* irq_tab[IRQ_LIMIT]   = { _irq_0,  _irq_1,  _irq_2,  _irq_3,  _irq_4,  _irq_5, _irq_6, _irq_7, _irq_8, _irq_9,
								     _irq_10, _irq_11, _irq_12, _irq_13, _irq_14, _irq_15 };
								
// CPU context used when saving/restoring context from an interrupt
typedef struct regs_st {
    uint32_t gs, fs, es, ds;
    uint32_t ebp, edi, esi;
    uint32_t edx, ecx, ebx, eax;
    uint32_t number, error_code;
    uint32_t eip, cs, eflags, esp, ss;
} regs_t;

// Build and return an IDT entry.
// selector is the code segment selector in which resides the ISR (Interrupt Service Routine)
// offset is the address of the ISR (NOTE: for task gates, offset must be 0)
// type indicates the IDT entry type
// dpl is the privilege level required to call the associated ISR
static idt_entry_t idt_build_entry(uint16_t selector, uint32_t offset, uint8_t type, uint8_t dpl) {
	idt_entry_t entry;
    entry.offset15_0 = offset & 0xffff;
    entry.selector = selector;
    entry.reserved = 0;
    entry.type = type;
    entry.dpl = dpl;
    entry.p = 1;
    entry.offset31_16 = (offset >> 16) & 0xffff;
	return entry;
}

// Exception handler
void exception_handler(struct regs_st *regs) {
	
	// Message en rouge
	set_text_color(RED);
	printf("Exception %d ! Kernel will now halt.\r\n", regs->number);
	
	// Arrêt du kernel
	halt();
	
}

// IRQ handler
void irq_handler(struct regs_st *regs) {
	
	// Message de test
	printf("IRQ %d\r\n", regs->number);
	
	// Fin d'interruption
	pic_eoi(regs->number);
	
}

void idt_init() {

	// Initialisation IDT
	memset(&idt, 0, IDT_ENTRIES);
	
	// Initialisation pointeur
	idt_ptr.limit = IDT_ENTRIES;
	idt_ptr.base  = (uint32_t) &idt;
	
	// [0..20]  --> Exceptions processeur
	for (uint16_t i = 0; i < CPU_EXCEPTS; i++)
		idt[i] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR, (uint32_t) &isr_tab[i], TYPE_INTERRUPT_GATE, DPL_KERNEL);
	// [32..47] --> 16 IRQ
	for (uint16_t i = 0; i < IRQ_LIMIT; i++)
		idt[i + IRQ_BASE] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR, (uint32_t) &irq_tab[i], TYPE_INTERRUPT_GATE, DPL_KERNEL);

	// Chargement IDT dans le CPU
	idt_flush(&idt_ptr);
	
}

