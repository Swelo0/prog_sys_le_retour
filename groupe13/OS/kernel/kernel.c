//////////////////////////////////////////////////////////////////////////////////////////
/// \file kernel.c
/// \author Thierry Mourao
/// \author Sylvain Thullen
/// \author Sacha Conti
/// \date 29 november 2015
/// \brief Implementation of the kernel main function
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
	timer_init(100);
	
	// Keyboard
	printf("| Init Keyboard ..................... ");
	keyboard_init();
 
	// Activation interruptions matérielles
	sti();
	
	printf("+-------------------------------------+");
	sleep(2000);
	
	// Splash screen
	char buffer[4096];
	file_read("splash.txt", buffer);
	clear_display();
	printf("%s\n", &buffer);
	sleep(5000);
	clear_display();
	
	// Message
	printf("+------------------------------------------------------------------------------+\n");
	printf("                         Welcome in our humble kernel.\n");
	printf("+------------------------------------------------------------------------------+\n");
	
	// Tests
    #ifdef TEST
		runTests();
    #endif
	
	//printf("Exec -> %d\n", exec("app.elf"));
	
	// Reading keyboard and printing input
    while (1) 
		keyboard_print(getc());
	
}

