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
#include "io.h"
#include "timer.h"
#include "pic.h"

#ifdef TEST
#include "test.h"
#endif

//////////////////////////////////////////////////////////////////////////////////////////
void runKernel()
{
	
	// Init VGA
	init_display();
	
    // Init GDT
	gdt_init();
	print_str("GDT successfully loaded.\r\n");
	
	// Init PIC
	pic_init();
	print_str("PIC init.\r\n");
	
	// Init IDT
	idt_init();
	print_str("IDT successfully loaded.\r\n");
	
	// Init 100Hz timer
	timer_init(100);
	
	print_str("Welcome in our humble kernel.\r\n");
	
    #ifdef TEST
		runTests();
    #endif
 
	// Activation interruptions matérielles
	sti();
	print_str("IRQ enabled\r\n");
	
    while(1);
	
}

