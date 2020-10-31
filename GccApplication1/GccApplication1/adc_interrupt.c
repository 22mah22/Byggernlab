/*
 * adc_interrupt.c
 *
 * Created: 28.10.2020 09:57:57
 *  Author: bendil
 */ 

#include "adc_interrupt.h"


#include <stdio.h>
#include "sam.h"

#include "printf-stdarg.h"
#include <time.h>

#define DEBUG_INTERRUPT 1

uint8_t TO_INCREMENT = 0;
int8_t GOAL_IN_ACTION = 0;
uint8_t TOTAL_GOALS = 0;
time_t clockcycles = 84000;



void ADC_Handler( void ){
	//printf("Aa");
	/*if(SysTick->VAL < clockcycles - 42000){
		printf("Aa");
		TOTAL_GOALS += 1;
		clockcycles = SysTick->VAL;
	}*/
	TO_INCREMENT = 1; 
	int i = ADC->ADC_ISR;
	
	NVIC_ClearPendingIRQ(ID_ADC);
	
}


void goal_counter(){
	if(GOAL_IN_ACTION == 0 && TO_INCREMENT){
		TOTAL_GOALS += 1;
		GOAL_IN_ACTION = 1;
		
	}
	if(ADC->ADC_CDR[1] > 0x0ff){
		GOAL_IN_ACTION = 0;
	}
	TO_INCREMENT = 0;
}
