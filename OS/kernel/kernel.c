//////////////////////////////////////////////////////////////////////////////////////////
/// \file kernel.c
/// \author Benjamin Ganty
/// \author Thierry Mourao
/// \date 4 november 2015
/// \brief Implementation of the kernel main function.
//////////////////////////////////////////////////////////////////////////////////////////

#include "kernel.h"

#include "gdt.h"
#include "idt.h"
#include "periph.h"
#include "io.h"

#ifdef TEST
#include "test.h"
#endif

//////////////////////////////////////////////////////////////////////////////////////////
void runKernel()
{
	
	// Init VGA
	init_display();
	
    // Init GDT and IDT
	gdt_init();
	print_str("GDT successfully loaded.\r\n");
	idt_init();
	print_str("IDT successfully loaded.\r\n");
	
	print_str("Welcome in our humble kernel.\r\n");
    
    #ifdef TEST
    
    // Runs the test procedure if test mode is enabled
    runTests();
    
    #endif
    
    while(1);
}

