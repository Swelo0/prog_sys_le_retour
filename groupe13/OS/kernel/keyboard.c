//////////////////////////////////////////////////////////////////////////////////////////
/// \file keyboard.c
/// \author Thierry Mourao
/// \author Sylvain Thullen
/// \author Sacha Conti
/// \date 29 november 2015
/// \brief Implementation of keyboard functions
//////////////////////////////////////////////////////////////////////////////////////////
#include "keyboard.h"

// Buffer du clavier
static char    buffer[BUFFER_SIZE];
// Pointeurs de lecture / écriture dans le buffer
static int 	   buffer_read;
static int     buffer_write;
// Caractères neutres (sans Alt, Shift ou Ctrl)
static char chars_neutral[CHARS_ARRAY_SIZE] = { '\0', '\0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '\'', '^', '\0', '\t', 
												'q', 'w', 'e', 'r', 't', 'z', 'u', 'i', 'o', 'p', '\0', '\0', '\0', '\0', 'a', 's',
												'd', 'f', 'g', 'h', 'j', 'k', 'l', '\0', '\0', '\0', '\0', '$', 'y', 'x', 'c', 'v',
												'b', 'n', 'm', ',', '.', '-', '\0', '\0' , '\0', ' ', '\0' };
// Caractères "shiftés"
static char chars_shift[CHARS_ARRAY_SIZE] =   { '\0', '\0', '+', '"', '*', '?', '%', '&', '/', '(', ')', '=', '?', '`', '\0', '\0', 
												'Q', 'W', 'E', 'R', 'T', 'Z', 'U', 'I', 'O', 'P', '?', '!', '\n', '?', 'A', 'S',
												'D', 'F', 'G', 'H', 'J', 'K', 'L', '\0', '\0', '\0', '\0', '\0', 'Y', 'X', 'C', 'V',
												'B', 'N', 'M', ';', ':', '_', '\0', '\0' , '\0', ' ', '\0' };
												
// Touche shift enfoncée									
static bool shift;
// Buffer plein
static bool buffer_full;

void keyboard_init() {

	// Booléens
	shift 		= false;
	buffer_full = false;

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
	
	// Position curseur (pour les flèches / backspace)
	uint16_t offset = get_cursor_offset();
	// Récupération scan code
	uint8_t sc    = inb(KEYBOARD_DATA);
	uint8_t code  = (sc & 0x7F);
	// Make (0) / Break (1)
	uint8_t state = (sc >> 7);  
	
	switch (code) {
		
		// Shift
		case CODE_LEFT_SHIFT:
		case CODE_RIGHT_SHIFT:
				shift = !shift;
				break;
				
		// Entrée
		case CODE_ENTER:
			if (((buffer_write + 1) % BUFFER_SIZE) != buffer_read) {
				buffer[buffer_write] = '\n'; 
				buffer_write = (buffer_write + 1) % BUFFER_SIZE; 
			}
			break;
			
		// Flèches directionnelles
		case CODE_UP:
			if ((!state) && (offset >= TEXT_DISPLAY_COLUMNS))
				set_cursor_offset(offset - TEXT_DISPLAY_COLUMNS);
			break;
			
		case CODE_DOWN:
			if ((!state) && (offset < (TEXT_DISPLAY_COLUMNS * (TEXT_DISPLAY_LINES - 1))))
				set_cursor_offset(offset + TEXT_DISPLAY_COLUMNS);
			break;
			
		case CODE_LEFT:
			if ((!state) && ((offset % TEXT_DISPLAY_COLUMNS) != 0))
				set_cursor_offset(offset - 1);
			break;
		
		case CODE_RIGHT:
			if ((!state) && (offset != (TEXT_DISPLAY_COLUMNS - 1)))
				set_cursor_offset(offset + 1);
			break;
			
		// Effacement caractère
		case CODE_BACKSPACE:
			if ((!state) && (offset > 0)) {
				set_cursor_offset(offset - 1);
				print_char(' ');
				set_cursor_offset(offset - 1);
			}
			break;
			
		// Caractère
		default:
		
			// On ajoute à la pression de la touche et quand le buffer n'est pas plein
			if ((!state) && (!buffer_full)) {
				
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
					
						// Ajout dans buffer si pas plein
						if (((buffer_write + 1) % BUFFER_SIZE) != buffer_read) {
							buffer[buffer_write] = c; 
							buffer_write = (buffer_write + 1) % BUFFER_SIZE; 
						}
						// Sinon on n'est pas content et on le montre !
						else {
								
								printf("\n+----------------------------------------------\n");
								set_text_color(RED);
								printf("                Buffer is full. \n");
								printf("         Type slower for Christ's sake !\n");
								set_text_color(WHITE);
								printf("+----------------------------------------------\n");
								buffer_full = true;
								
						}
						
					}
					
			}
			break;
		
	}
	
}

int getc() {

	// Bloquant si aucun caractère dans le buffer
	while (buffer_write == buffer_read);
	
	// Lecture des caractères jusqu'à ce que buffer_read rattrape buffer_write
	while (buffer_read != buffer_write) {
		print_char(buffer[buffer_read]); 
		buffer_read = (buffer_read + 1) % BUFFER_SIZE;
		buffer_full = false;
	}
	
	return 0;
	
}
