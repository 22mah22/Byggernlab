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
void init_ch1_PI();

uint8_t get_controller_runs();

void reset_controller_runs();

void TC1_Handler       ( void );



#endif /* TIMER_DRIVER_H_ */