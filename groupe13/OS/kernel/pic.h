#ifndef _PIC_H_
#define _PIC_H_

#include "periph.h"
#include "io.h"

#define PIC1_CMD        0x20
#define PIC1_DATA       0x21
#define PIC2_CMD        0xA0
#define PIC2_DATA       0xA1

// End Of Interrupt (reactivate the specified PIC)
#define PIC_EOI         0x20

extern void pic_init();
extern void pic_eoi(int irq);

#endif

