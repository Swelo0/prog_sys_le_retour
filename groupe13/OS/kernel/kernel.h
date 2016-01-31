//////////////////////////////////////////////////////////////////////////////////////////
/// \file kernel.h
/// \author Thierry Mourao
/// \author Sylvain Thullen
/// \author Sacha Conti
/// \date 29 november 2015
/// \brief Declaration of the kernel main function
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef _KERNEL_H_
#define _KERNEL_H_

#include "gdt.h"
#include "idt.h"
#include "ide.h"
#include "pfs.h"
#include "keyboard.h"
#include "../user/ulibc.h"

//////////////////////////////////////////////////////////////////////////////////////////
/// \fn void runKernel()
/// \brief Main kernel function.
///
/// This function is called by the bootloader. It should never return.
/// If the kernel is compiled in test mode, the test procedure is executed.
//////////////////////////////////////////////////////////////////////////////////////////
void runKernel();

#endif

