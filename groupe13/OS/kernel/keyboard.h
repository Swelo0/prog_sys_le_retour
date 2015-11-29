//////////////////////////////////////////////////////////////////////////////////////////
/// \file keyboard.h
/// \author Thierry Mourao
/// \author Sylvain Thullen
/// \author Sacha Conti
/// \date 29 november 2015
/// \brief Definition of keyboard functions
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include "x86.h"
#include "../common/types.h"
#include "periph.h"
#include "io.h"
#include "string.h"

#define KEYBOARD_DATA		0x60
#define CHARS_ARRAY_SIZE	64
#define BUFFER_SIZE			32
// Special characters
#define CODE_BACKSPACE		0xE
#define CODE_LEFT_SHIFT		0x2A
#define CODE_RIGHT_SHIFT	0x36
#define CODE_ENTER			0x1C
#define CODE_ALT			0x38
#define CODE_ALT_GR			0x60
#define CODE_CTRL			0x1D

extern void keyboard_init();
extern void keyboard_handler();
extern int getc();

#endif