/*
 * timer_driver.h
 *
 * Created: 14.10.2020 17:56:07
 *  Author: magneah
 */ 

/**
 * @file
 * @brief Driver module for setting pwm timer data
 */


#ifndef TIMER_DRIVER_H_
#define TIMER_DRIVER_H_

/**
 * @brief Function for setting up a timed pwm signal for the servo
 */
void timer_init();
/**
 * @brief Function for changing the duty cycle of the servo pwm signal
 * @param dutyCycle new duty cycle
 */
void timer_change_duty(uint8_t dutyCycle);
void timer_change_duty_buzzer(uint8_t dutyCycle);
void init_ch1_PI();

uint8_t get_controller_runs();

void reset_controller_runs();

void increment_controller_runs();


#endif /* TIMER_DRIVER_H_ */