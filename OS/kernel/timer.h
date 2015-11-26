#ifndef _TIMER_H_
#define _TIMER_H_

#include "../common/types.h"
#include "periph.h"

extern void timer_init(uint32_t freq_hz);
extern void timer_handler();
extern uint get_ticks();
extern void sleep(uint ms);

#define PIT_default 1193180	// 1.19318 MHz
#define PIT_c0		0x40
#define PIT_c1		0x41
#define PIT_c2		0x42
#define PIT_command	0x43

#endif
