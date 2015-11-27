#include "timer.h"

static uint32_t ticks;
static uint32_t freq;

void timer_init(uint32_t freq_hz) {

	ticks = 0;
	freq = freq_hz;

	// Diviseur de l'horloge
	uint32_t div = PIT_default / freq;
	if (div < (1 << 16)) {
	
		// Sélection du diviseur et mode "répétition" du compteur
		outb(PIT_command, 0x36);
		// LSB
		outb(PIT_c0, (uint8_t) div);
		// MSB
		outb(PIT_c0, (uint8_t) (div >> 8));
		
		// Message de confirmation
		set_text_color(LIGHT_GREEN);
		printf("OK");
		set_text_color(WHITE);
		printf(" %dHz\r\n", freq);
		
	}
	// Message d'erreur
	else {
		set_text_color(RED);
		printf("KO");
		set_text_color(WHITE);
		printf(" %dHz\r\n", freq);
	}
	
}

void timer_handler() { ticks++; }

uint get_ticks() { return ticks; }

void sleep(uint ms) {

	// Ticks à attendre
	uint32_t wait = freq * (ms / 1000);
	// Référence
	uint32_t ref  = ticks;
	// Boucle
	while (ticks <= (ref + wait));
	
}


