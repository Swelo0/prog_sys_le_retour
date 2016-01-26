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
	
	// Message
	printf("+----------------------------------------------\n");
	printf("          Welcome in our humble kernel.\n");
	printf("+----------------------------------------------\n");
 
	// Activation interruptions matérielles
	sti();
	
	// Tests
    #ifdef TEST
		runTests();
    #endif
    
	char* file = "example.txt";
	// Buffer size is equivalent to 4 blocks
    char buf[2048] = "";
	stat_t* s;
	if ((file_exists(file)) && (!file_stat(file, s))) {
		printf("File:\n   name : %s\n   size : %d bytes\nContent:\n", s->name, s->size);
		file_read(file, &buf);
	}
	else
		printf("File %s doesn't exist\n", file);
	
	/*
	file_remove(file);
	
	if ((file_exists(file)) && (!file_stat(file, s))) {
		printf("File:\n   name : %s\n   size : %d bytes\nContent:\n", s->name, s->size);
		file_read(file, &buf);
	}
	else
		printf("File %s doesn't exist anymore\n", file);
	*/
	
	// Reading keyboard and printing input
    while (1) 
		keyboard_print(getc());
	
}

