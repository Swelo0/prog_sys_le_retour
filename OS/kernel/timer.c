#include "timer.h"

static uint32_t ticks = 0;
static uint32_t freq  = 100;

void timer_init(uint32_t freq_hz) {

	freq = freq_hz;

	// Diviseur de l'horloge
	uint16_t div = PIT_default / freq;
	// Sélection du diviseur et mode "répétition" du compteur
	outb(PIT_command, 0x36);
	// LSB
	outb(PIT_c0, (uint8_t) div);
	// MSB
	outb(PIT_c0, (uint8_t) (div >> 8));
	
}

void timer_handler() { ticks++; }

uint get_ticks() { return ticks; }

void sleep(uint ms) {

	// Ticks to wait
	uint32_t wait = freq * (ms / 1000);
	// Reference
	uint32_t ref  = ticks;
	// Loop
	while (ticks <= (ref + wait));
	
}


