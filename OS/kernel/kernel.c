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
    // Init GDT and IDT
    gdt_init();
	idt_init();
    
    // Init VGA
    init_display();
    
    #ifdef TEST
    
    // Runs the test procedure if test mode is enabled
    runTests();
    
    #else
    
    // Prints a welcome message in normal mode
    print_str("Welcome. This is the Kernel.\r\nThe GDT is ready.\r\nThe text display is ready.\r\n");
    
    #endif
    
    while(1);
}

