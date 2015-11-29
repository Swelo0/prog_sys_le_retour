#include "timer.h"

static uint ticks = 0;
// Variable contenant la fréquence divisée
static uint32_t frequence_divise;
static bool first = true;
static bool clignote = true;
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
	// Confirmation visuelle
	#ifndef TEST
	if(first){
		backup = get_cursor_offset();
		set_cursor_position(TEXT_DISPLAY_LINES, TEXT_DISPLAY_COLUMNS - 7);
		offset = get_cursor_offset();
		first = false;
		set_text_color(RED);
		printf("TICK!!");
		set_cursor_offset(backup);
	}else{
		backup = get_cursor_offset();
		set_cursor_offset(offset);
		if(clignote){
			set_text_color(RED);
			printf("TICK!!");
			clignote = false;
		}
		else{
			set_text_color(GREEN);
			printf("TICK!!");
			clignote = true;
		}
		set_cursor_offset(backup);		
	}
	#endif
}

uint get_ticks() {
	return ticks;
}

void sleep(uint ms) {
// Ticks à attendre
	uint wait = (FREQUENCE_MAX / frequence_divise) * (ms / 1000);
// Message de confirmation
	printf("\nVariable wait = %d\n", wait);
// Référence
	uint ref = ticks;
	// Message de confirmation
	printf("\nVariable ref = %d\n", ref);
// Boucle
	while (get_ticks() <= (ref + wait)){
		//printf("%d\n", get_ticks());
	}
	printf("Fin du sleep");
}
