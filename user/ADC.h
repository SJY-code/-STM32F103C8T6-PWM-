#ifndef _ADC_H_
#define _ADC_H_
#include "stm32f10x.h"                  // Device header

void ADCinit(void);
uint16_t ADCgetvalue(void);

#endif
