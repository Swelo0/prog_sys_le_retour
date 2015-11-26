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
	
	// VGA
	init_display();
	
    // GDT
	gdt_init();
	print_str("GDT loaded.\r\n");
	
	// PIC
	pic_init();
	print_str("PIC init.\r\n");
	
	// IDT
	idt_init();
	print_str("IDT loaded.\r\n");
	
	// 100Hz timer
	timer_init(100);
	
	// Message
	print_str("Welcome in our humble kernel.\r\n");
	
	// Tests
    #ifdef TEST
		runTests();
    #endif
 
	// Activation interruptions matérielles
	sti();
	print_str("IRQ enabled\r\n");
	
    while(1);
	
}

