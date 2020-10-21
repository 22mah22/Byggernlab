/*
 * timer_driver.c
 *
 * Created: 14.10.2020 17:55:55
 *  Author: magneah
 */ 

#include "sam.h"
	
	static Tc *tc = 0x40080000;

void timer_init(){
	
	
	PMC->PMC_PCER0 |= PMC_PCER0_PID27; //enable timer counter channel 0
	
	PIOB->PIO_PDR |= PIO_PDR_P25; //disable io on pinb 25
	PIOB->PIO_ABSR |= PIO_ABSR_P25; //PIO set peripheral b on pinb 25*/
	
	tc->TC_CHANNEL[0].TC_CMR = 0x0009C000;
	tc->TC_CHANNEL[0].TC_RC = 0x000CD140;
	
	
	tc->TC_CHANNEL[0].TC_CCR = 0x00000001; //enables the clock
	tc->TC_CHANNEL[0].TC_CCR |= 0x1 << 2;
}

void timer_change_duty(uint8_t dutyCycle){
	
	//max = 84000 = 0x14820
	//min = 42000 = 0xA410
	//max - min = 42000
	// 1 prosent = 420 = 0x1A4
	//TC_RA = TC_RC - (0xC3D98 + 0x1F8*dutyCycle) = 0x000CD140 - (0xC3D98 + 0x1F8*dutyCycle)
	if(dutyCycle < 0){
		dutyCycle = 0;
	}
	if(dutyCycle > 100){
		dutyCycle = 100;
	}
	
	tc->TC_CHANNEL[0].TC_RA = 0x000CD140 - (0xA410 + 0x1A4*dutyCycle); // TC_RA - (min_value + dutyCycle*1prosentOfDifference)
	
	
}