//////////////////////////////////////////////////////////////////////////////////////////
/// \file keyboard.c
/// \author Thierry Mourao
/// \author Sylvain Thullen
/// \author Sacha Conti
/// \date 29 november 2015
/// \brief Implementation of keyboard functions
//////////////////////////////////////////////////////////////////////////////////////////
#include "keyboard.h"

static char    buffer[BUFFER_SIZE];
static int 	   buffer_read;
static int     buffer_write;
static char chars_neutral[CHARS_ARRAY_SIZE] = { '\0', '?', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '\'', '^', '\0', '\t', 
												'q', 'w', 'e', 'r', 't', 'z', 'u', 'i', 'o', 'p', '?', '?', '\0', '?', 'a', 's',
												'd', 'f', 'g', 'h', 'j', 'k', 'l', '?', '?', '?', '\0', '$', 'y', 'x', 'c', 'v',
												'b', 'n', 'm', ',', '.', '-', '\0', '?' , '?', ' ', '\0' };
static char chars_shift[CHARS_ARRAY_SIZE] =   { '\0', '?', '+', '"', '*', '?', '%', '&', '/', '(', ')', '=', '?', '`', '\0', '?', 
												'Q', 'W', 'E', 'R', 'T', 'Z', 'U', 'I', 'O', 'P', '?', '!', '\n', '?', 'A', 'S',
												'D', 'F', 'G', 'H', 'J', 'K', 'L', '?', '?', '?', '\0', '\0', 'Y', 'X', 'C', 'V',
												'B', 'N', 'M', ';', ':', '_', '\0', '?' , '\0', ' ', '\0' };
												
static bool shift;

void keyboard_init() {

	shift = false;

	// Buffer
	memset(&buffer, 0, BUFFER_SIZE);
	buffer_read = 0;
	buffer_write = 0;
	
	// Message de confirmation
	set_text_color(LIGHT_GREEN);
	printf("OK\n");
	set_text_color(WHITE);
	
}

void keyboard_handler() {
	
	// Récupération scan code
	uint8_t sc    = inb(KEYBOARD_DATA);
	uint8_t code  = (sc & 0x7F);
	// Make (0) / Break (1)
	uint8_t state = (sc >> 7);  
	
	// Inversion shift
	if ((code == CODE_LEFT_SHIFT) || (code == CODE_RIGHT_SHIFT))
		shift = !shift; 
	// Retour à la ligne
	else if ((code == CODE_ENTER) && (((buffer_write + 1) % BUFFER_SIZE) != buffer_read)) {
		buffer[buffer_write] = '\n'; 
		buffer_write = (buffer_write + 1) % BUFFER_SIZE; 
	}
	// Caractères
	else if (state == 0) {
			
		char c;
		if (shift) c = chars_shift[code];
		else	   c = chars_neutral[code];		
		
		// Si imprimable et défini dans le tableau de caractères
		if ((c != '\0') && (code <= CHARS_ARRAY_SIZE)) {
		
			// Si 'Q' --> arrêt du kernel
			if (c == 'Q') {
				printf("\n+----------------------------------------------\n");
				set_text_color(RED);
				printf("                 'Q' pressed. \n");
				printf("             Kernel will now halt.\n");
				set_text_color(WHITE);
				printf("+----------------------------------------------\n");
				halt();
			}
		
			// Ajout dans buffer si non plein
			if (((buffer_write + 1) % BUFFER_SIZE) != buffer_read) {
				buffer[buffer_write] = c; 
				buffer_write = (buffer_write + 1) % BUFFER_SIZE; 
			}
			
		}
		
		
	}
	
}

int getc() {

	// Bloquant si aucun caractère dans le buffer
	while (buffer_write == buffer_read);
	
	// Lecture des caractères jusqu'à ce que buffer_read rattrape buffer_write
	while (buffer_read != buffer_write) {
		print_char(buffer[buffer_read]); 
		buffer_read = (buffer_read + 1) % BUFFER_SIZE;
	}
	
	return 0;
	
}
