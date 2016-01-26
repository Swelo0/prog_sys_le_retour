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
    
	file_iterator_t it = file_iterator();
	int block_size = SECTOR_SIZE * it.size_block;
	
	// Read file if existing
	char* file = "example.txt";
	stat_t* s;
	if ((file_exists(file)) && (!file_stat(file, s))) {
		// Allocating a integer number of blocks for the buffer
		char* buf[s->size + (block_size - (s->size % block_size))];
		if (!file_read(file, &buf)) printf("%s\n", buf);
	}
	else
		printf("File %s doesn't exist.\n", file);
	
	// Reading keyboard and printing input
    while (1) 
		keyboard_print(getc());
	
}

