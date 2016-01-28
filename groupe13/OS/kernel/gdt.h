#ifndef _GDT_H_
#define _GDT_H_

#include "../common/types.h"
#include "x86.h"
#include "string.h"
#include "io.h"
#include "task.h"
#include "pfs.h"

// Structure of a GDT descriptor. There are 2 types of descriptors: segments and TSS.
// Section 3.4.5 of Intel 64 & IA32 architectures software developer's manual describes
// segment descriptors while section 6.2.2 describes TSS descriptors.
typedef struct gdt_entry_st {
    uint16_t lim15_0;
    uint16_t base15_0;
    uint8_t base23_16;

    uint8_t type : 4;
    uint8_t s : 1;
    uint8_t dpl : 2;
    uint8_t present : 1;

    uint8_t lim19_16 : 4;
    uint8_t avl : 1;
    uint8_t l : 1;
    uint8_t db : 1;
    uint8_t granularity : 1;

    uint8_t base31_24;
} __attribute__((packed)) gdt_entry_t;

// Structure describing a pointer to the GDT descriptor table.
// This format is required by the lgdt instruction.
typedef struct gdt_ptr_st {
    uint16_t limit;    // Limit of the table (ie. its size)
    uint32_t base;     // Address of the first entry
} __attribute__((packed)) gdt_ptr_t;

typedef struct task_st {
	uint8_t free;
	uint32_t addr;
} __attribute__((packed)) task_t;

extern void gdt_init();
extern void gdt_flush(gdt_ptr_t *gdt_ptr);
extern void load_task_register(uint16_t tss_selector); 
int exec(char* bin);

#endif
