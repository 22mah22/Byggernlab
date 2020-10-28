/*
 * dac_controller.c
 *
 * Created: 28.10.2020 14:25:06
 *  Author: bendil
 */ 

#include "dac_controller.h"
#include "sam.h"



void dac_init(){
	
	PMC->PMC_PCER1 = PMC_PCER1_PID38;
	
	
	DACC->DACC_MR |= DACC_MR_USER_SEL_CHANNEL1;
	DACC->DACC_MR &= ~(1<<0); //disable trigger, set freemode
	//DACC->DACC_MR |= DACC_MR_WORD_WORD;
	//DACC->DACC_CHER |= DACC_CHER_CH0;
	DACC->DACC_CHER = DACC_CHER_CH1;
	
	DACC->DACC_CDR = 0x05ff;
	
	
}