//////////////////////////////////////////////////////////////////////////////////////////
/// \file timer.h
/// \author Thierry Mourao
/// \author Sylvain Thullen
/// \author Sacha Conti
/// \date 29 november 2015
/// \brief Definition of timer functions: PIT initialisation, handler for time interrupt
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef _TIMER_H_
#define _TIMER_H_

#include "../common/types.h"
#include "periph.h"
#include "io.h"

extern void timer_init(uint32_t freq_hz);
extern void timer_handler();
extern uint get_ticks();
extern void sleep(uint ms);

#define FREQUENCE_MAX 1193180 //la fréquence max de l'horloge est de 1'193'180 Hz
#define CHAN_IRQ 0x40 // Chan permettant d'envoyer une interruption IRQ0
#define CHAN_CONTROLE 0x43 // Chan de contrôle du PIT

#endif
