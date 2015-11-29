//////////////////////////////////////////////////////////////////////////////////////////
/// \file kernel.c
/// \author Benjamin Ganty
/// \author Thierry Mourao
/// \date 4 november 2015
/// \brief Implementation of the kernel main function.
//////////////////////////////////////////////////////////////////////////////////////////

#include "kernel.h"

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
	timer_init(1000);
	
	// Keyboard
	printf("| Init Keyboard ..................... ");
	keyboard_init();
	
	// Message
	printf("+----------------------------------------------\n");
	printf("          Welcome in our humble kernel.\n");
	printf("+----------------------------------------------\n");
 
	// Activation interruptions matérielles
	sti();

	//Test du sleep
	printf("\n");
	printf("+----------------------------------------------\n");
	printf("          Avant le sleep de 3 secondes\n");
	printf("+----------------------------------------------\n");

	sleep(3000);

	printf("\n");
	printf("+----------------------------------------------\n");
	printf("          Après le sleep de 3 secondes\n");
	printf("+----------------------------------------------\n");
	
	// Tests
    #ifdef TEST
	runTests();
    #endif
	
	// Reading keyboard
    while(1) getc();
	
}

