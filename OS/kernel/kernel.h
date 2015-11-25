//////////////////////////////////////////////////////////////////////////////////////////
/// \file kernel.h
/// \author Benjamin Ganty
/// \author Thierry Mourao
/// \date 4 november 2015
/// \brief Definition of the main kernel function.
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef _KERNEL_H_
#define _KERNEL_H_

//////////////////////////////////////////////////////////////////////////////////////////
/// \fn void runKernel()
/// \brief Main kernel function.
///
/// This function is called by the bootloader. It should never return.
/// If the kernel is compiled in test mode, the test procedure is executed.
//////////////////////////////////////////////////////////////////////////////////////////
void runKernel();

#endif

