#include "timer.h"

static uint ticks;
// Variable contenant la fréquence divisée
static uint32_t frequence_divise;

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
	outb(CHAN_CONTROLE, 0x34);
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
	set_text_color(LIGHT_GREEN);
	printf("Ticks incrémenté !! Valeur de ticks:");
	set_text_color(WHITE);
	printf(" %d\n", ticks);
}

uint get_ticks() {
	return ticks;
}

void sleep(uint ms) {
// Ticks à attendre
	uint wait = frequence_divise * (ms / 1000);
// Référence
	uint ref  = get_ticks();
// Boucle
	while (get_ticks() <= (ref + wait));
}


