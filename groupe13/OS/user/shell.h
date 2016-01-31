#ifndef _SHELL_H_
#define _SHELL_H_

#include "ulibc.h"

#define INPUT_MAX_LENGTH 100

void shell_handler();

void Prompt();

void resetCmd();

void GetCmd();

int ExecCmd();


#endif