/*
 * adc_controller.c
 *
 * Created: 28.10.2020 10:48:14
 *  Author: bendil
 */ 
#include "adc_controller.h"

#include "sam.h"

void adc_init(){
	
	PMC->PMC_PCER1 = PMC_PCER1_PID37; //enable adc controller
	
	
	//Enable interrupt in NVIC
	NVIC_EnableIRQ(ID_ADC);
	
	
	ADC->ADC_CHER = ADC_CHER_CH1; //pin a6 på arduino due
	//ADC->ADC_MR = ADC_MR_TRGEN_EN;
	ADC->ADC_MR = ADC_MR_FREERUN;
	
	ADC->ADC_CR = ADC_CR_START;
	ADC->ADC_IER = ADC_IER_COMPE;
	//ADC->ADC_IER |= ADC_IER_DRDY;
	ADC->ADC_EMR |= ADC_EMR_CMPMODE_LOW;

	//ADC->ADC_EMR = (0x0u << 9);
	ADC->ADC_EMR |= ADC_EMR_CMPSEL(1);
	ADC->ADC_CWR = ADC_CWR_LOWTHRES(0x00f);
	//ADC->ADC_EMR |= ADC_EMR_CMPFILTER(0);
	
	
}
