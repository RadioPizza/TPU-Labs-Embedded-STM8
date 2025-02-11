#ifndef MAIN_H
#define MAIN_H

#include <iostm8s207.h>
#include <stdint.h>

// Объявление обработчика прерывания таймера 1
@far @interrupt void TIM1_IRQHandler(void);

#endif