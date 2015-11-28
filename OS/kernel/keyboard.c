#include "keyboard.h"

static char*    buffer[BUFFER_SIZE];
static uint16_t index;
static char chars[CHARS_ARRAY_SIZE] = { '\0', '?', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '\'', '^', '?' /*backspace*/, '\t', 
										'q', 'w', 'e', 'r', 't', 'z', 'u', 'i', 'o', 'p', '?', '?', '\n', '?', 'a', 's',
										'd', 'f', 'g', 'h', 'j', 'k', 'l', '?', '?', '?', '?' /*left shift*/, '$', 'y', 'x', 'c', 'v',
										'b', 'n', 'm', ',', '.', '-', '?' /*right shift*/, '?' , '?' /*alt*/, ' ', '?' };

void keyboard_init() {

	memset(&buffer, 0, BUFFER_SIZE);
	index = 0;
	
	// Message de confirmation
	set_text_color(LIGHT_GREEN);
	printf("OK\r\n");
	set_text_color(WHITE);
	
}

void keyboard_handler() {
	
	// Récupération scan code
	uint8_t sc    = inb(KEYBOARD_DATA);
	uint8_t code  = (sc & 0x7F);
	// Make (0) / Break (1)
	uint8_t state = (sc >> 7);  

	// Enregistrement au relachement (?)
	if (state == 1) {
	
		/* DEBUG
		if (code < CHARS_ARRAY_SIZE) 
			printf("%x --> \"%c\"\r\n", code, chars[code]);
		else 
			printf("%x --> Unknown\r\n", code);
		*/
			
		// Ajout du caractère dans le buffer
		buffer[index++] = chars[code];
		// Affichage
		getc();
		
	}
	
}

int getc() {

	// Bloquant si aucun caractère dans le buffer
	while (index == 0);
	
	// Lecture des caractères jusqu'à \0
	printf("%s", buffer);
	
	// Réinitialisation buffer
	memset(&buffer, 0, index);
	index = 0;
	
	return 0;
	
}
