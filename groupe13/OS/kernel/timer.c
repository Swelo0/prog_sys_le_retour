//////////////////////////////////////////////////////////////////////////////////////////
/// \file timer.c
/// \author Thierry Mourao
/// \author Sylvain Thullen
/// \author Sacha Conti
/// \date 29 november 2015
/// \brief Implementation of timer functions: PIT initialisation, handler for time interrupt
//////////////////////////////////////////////////////////////////////////////////////////

#include "timer.h"

static uint ticks = 0;
// Variable contenant la fréquence divisée
static uint32_t frequence_divise;
int offset, backup;

void timer_init(uint32_t freq_hz) {
// La frequence divisée est obtenue en divisant la fréquence max par la frequence entrée en argument de fonction
	frequence_divise = FREQUENCE_MAX / freq_hz;
// Test pour debug et anti-plantage
	if (frequence_divise <= 0 || frequence_divise > 65536){
		// Message d'erreur
		set_text_color(RED);
		printf("KO");
		set_text_color(WHITE);
		printf(" %dHz\n", frequence_divise);
	}
// Accès au chan de contrôle: on y écrit 0x36 pour indiquer la sélection du diviseur et le mode “répetition”
	outb(CHAN_CONTROLE, 0x36);
// On envoie les 8 bits de poids faibles du diviseur
	outb(CHAN_IRQ, (frequence_divise & 0xFF));
// On envoie les 8 bits de poids faibles du diviseur
	outb(CHAN_IRQ, (frequence_divise >> 8) & 0xFF);
// Message de confirmation
	set_text_color(LIGHT_GREEN);
	printf("OK");
	set_text_color(WHITE);
	printf(" %dHz\n", frequence_divise);
}

void timer_handler() { 
	ticks++;
}

uint get_ticks() {
	return ticks;
}

void sleep(uint ms) {
// Ticks à attendre
	uint wait = (FREQUENCE_MAX / frequence_divise) * (ms / 1000);
// Référence
	uint ref = ticks;
// Boucle
	while (get_ticks() <= (ref + wait)){
		//printf("%d\n", get_ticks());
	}
}
