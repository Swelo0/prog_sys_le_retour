#ifndef _IDT_H_
#define _IDT_H_

#include "../common/types.h"
#include "x86.h"
#include "io.h"
#include "pic.h"
#include "string.h"

// Structure of an IDT descriptor. There are 3 types of descriptors:
// a task-gate, an interrupt-gate, and a trap-gate.
// See 5.11 of Intel 64 & IA32 architectures software developer's manual for more details.
// For task gates, offset must be 0.
typedef struct idt_entry_st {
    uint16_t offset15_0;   // only used by trap and interrupt gates
    uint16_t selector;     // segment selector for trap and interrupt gates;
                           // TSS segment selector for task gates
    uint16_t reserved : 8;
    uint16_t type : 5;
    uint16_t dpl : 2;
    uint16_t p : 1;

    uint16_t offset31_16;  // only used by trap and interrupt gates
} __attribute__((packed)) idt_entry_t;

// Structure describing a pointer to the IDT.
// This format is required by the lidt instruction.
typedef struct idt_ptr_st {
    uint16_t limit;   // Limit of the table (ie. its size)
    uint32_t base;    // Address of the first entry
} __attribute__((packed)) idt_ptr_t;

extern void idt_init();
extern void idt_flush(idt_ptr_t *idt_ptr);

// Don't look at me like that, I had no choice :'(
extern void _isr_0();
extern void _isr_1();
extern void _isr_2();
extern void _isr_3();
extern void _isr_4();
extern void _isr_5();
extern void _isr_6();
extern void _isr_7();
extern void _isr_8();
extern void _isr_9();
extern void _isr_10();
extern void _isr_11();
extern void _isr_12();
extern void _isr_13();
extern void _isr_14();
extern void _isr_15();
extern void _isr_16();
extern void _isr_17();
extern void _isr_18();
extern void _isr_19();
extern void _isr_20();
extern void _irq_0();
extern void _irq_1();
extern void _irq_2();
extern void _irq_3();
extern void _irq_4();
extern void _irq_5();
extern void _irq_6();
extern void _irq_7();
extern void _irq_8();
extern void _irq_9();
extern void _irq_10();
extern void _irq_11();
extern void _irq_12();
extern void _irq_13();
extern void _irq_14();
extern void _irq_15();

#define IDT_ENTRIES 256	// 256 entries in the IDT
#define CPU_EXCEPTS 21 	// 21 CPU exceptions
#define IRQ_LIMIT   16	// 16 IRQs
#define IRQ_BASE    32	// --> idt[32..47]

#endif
