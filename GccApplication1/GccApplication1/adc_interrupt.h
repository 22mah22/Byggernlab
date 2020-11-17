/**
 * @file
 * @brief Module for handling goals while playing.
 */

/*
 * adc_interrupt.h
 *
 * Created: 28.10.2020 09:58:09
 *  Author: bendil
 */ 


#ifndef ADC_INTERRUPT_H_
#define ADC_INTERRUPT_H_

#include <stdint.h>

/**
 * @brief The function returns the number of goals you have.
 * @return Returns total goals.
 */
uint8_t get_total_goals();

/**
 * @brief The function returns the goal flag.
 * @return Returns goal flag which is high if goal interrupt has been activated.
 */
uint8_t get_goal_flag();

/**
 * @brief The function resets the goal flag.
 */
void reset_goal_flag();

/**
 * @brief The function is called when there has been a goal, it stops the motor and sets the goal flag.
 */
void ADC_Handler       ( void );




#endif /* ADC_INTERRUPT_H_ */