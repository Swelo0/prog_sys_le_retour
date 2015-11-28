#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include "periph.h"
#include "io.h"
#include "string.h"

#define KEYBOARD_DATA		0x60
#define CHARS_ARRAY_SIZE	64
#define BUFFER_SIZE			50

extern void keyboard_init();
extern void keyboard_handler();
extern int getc();

#endif
