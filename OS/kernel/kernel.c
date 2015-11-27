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
	printf("| Init Global Descriptor Table ...... ");
	gdt_init();
	
	// PIC
	printf("| Init PIC .......................... ");
	pic_init();
	
	// IDT
	printf("| Init Interrupt Descriptor Table ... ");
	idt_init();
	
	// 100Hz timer
	printf("| Init Timer ........................ ");
	timer_init(100);
	
	printf("+----------------------------------------------\r\n");
	
	// Wait 3s
	sleep(3000);
	
	// Message
	printf("\r\n\t\tWelcome in our humble kernel.\r\n");
	
	// Tests
    #ifdef TEST
		runTests();
    #endif
 
	// Activation interruptions matérielles
	sti();
	
    while(1);
	
}

