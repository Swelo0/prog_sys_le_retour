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
    
    printf("\nAffichage du contenu de example.txt");
    char buf[2048] = "";
    file_read("example.txt", &buf);
    printf("\nAffichage du contenu de example2.txt");
    char buf2[2048] = "";
    file_read("example2.txt", &buf2);
    
	stat_t* s;
	char* file = "example.txt";
	if (file_exists(file)) {
		file_stat("example.txt", s);
		printf("File:\n   name : %s\n   size : %d bytes\n", s->name, s->size);
	}
	else
		printf("File %s doesn't exist\n", file);
	
	file_remove(file);
	
	if (file_exists(file)) {
		file_stat("example.txt", s);
		printf("File:\n   name : %s\n   size : %d bytes\n", s->name, s->size);
	}
	else
		printf("File %s doesn't exist anymore\n", file);
	
	// Reading keyboard and printing input
    while (1) 
		keyboard_print(getc());
	
}

