/*
 * adc_interrupt.c
 *
 * Created: 28.10.2020 09:57:57
 *  Author: bendil
 */ 

#include "adc_interrupt.h"
#include "motor_controller.h"


#include <stdio.h>
#include "sam.h"

#include "printf-stdarg.h"
#include "timer.h"
#include "feedback.h"

#define DEBUG_INTERRUPT 1

uint8_t goal_flag = 0;
uint8_t TOTAL_GOALS = 0;
static uint32_t last_goal_time = 0;

uint8_t get_total_goals(){
	 return TOTAL_GOALS;
 }

uint8_t get_goal_flag(){
	 return goal_flag;
 }

 void reset_goal_flag(){
	 goal_flag = 0;
 }

void ADC_Handler( void ){
	//printf("Aa");
	if(last_goal_time + 800 < return_milliseconds()){
		TOTAL_GOALS += 1;
		last_goal_time = return_milliseconds();
		goal_flag = 1;
	}

	change_motor_speed_using_paadrag(0);

	int i = ADC->ADC_ISR;
	
	NVIC_ClearPendingIRQ(ID_ADC);
	
}

