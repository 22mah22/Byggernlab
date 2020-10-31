/*
 * timer_driver.h
 *
 * Created: 14.10.2020 17:56:07
 *  Author: magneah
 */ 


#ifndef TIMER_DRIVER_H_
#define TIMER_DRIVER_H_

void timer_init();
void timer_change_duty(uint8_t dutyCycle);
void init_interrupt_PI();


void TC0_Handler       ( void );

#endif /* TIMER_DRIVER_H_ */