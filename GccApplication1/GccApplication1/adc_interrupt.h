/*
 * adc_interrupt.h
 *
 * Created: 28.10.2020 09:58:09
 *  Author: bendil
 */ 


#ifndef ADC_INTERRUPT_H_
#define ADC_INTERRUPT_H_

#include <stdint.h>

void start_timer();
void ADC_Handler       ( void );

extern uint8_t TO_INCREMENT;
extern uint8_t TOTAL_GOALS;

void goal_counter();


#endif /* ADC_INTERRUPT_H_ */