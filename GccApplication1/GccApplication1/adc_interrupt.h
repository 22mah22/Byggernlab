/*
 * adc_interrupt.h
 *
 * Created: 28.10.2020 09:58:09
 *  Author: bendil
 */ 


#ifndef ADC_INTERRUPT_H_
#define ADC_INTERRUPT_H_

#include <stdint.h>

uint8_t get_total_goals();

uint8_t get_goal_flag();

 void reset_goal_flag();
/*void start_timer();*/
void ADC_Handler       ( void );




#endif /* ADC_INTERRUPT_H_ */