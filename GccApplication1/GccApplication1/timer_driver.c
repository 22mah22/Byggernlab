/*
 * timer_driver.c
 *
 * Created: 14.10.2020 17:55:55
 *  Author: magneah
 */ 

#include "sam.h"


void timer_init(){
	
	/*Tc.TC_CHANNEL[0]->TC_CCR &= 1 << TC_CCR_CLKDIS; // makes sure disable is off
	Tc.TC_CHANNEL[0]->TC_CCR |= 1 << TC_CCR_CLKEN; // enables clock on channel 1
	
	Tc.TC_CHANNEL[0]->TC_CMR |= 1 << TC_CMR_WAVE; // enables waveform mode
	Tc.TC_CHANNEL[0]->TC_CMR |= 0x0 << TC_CMR_TCCLKS_Pos; // choose which clock to use*/
	Pwm.PWM_CLK |= 0x00010001; // select mck with noe dividers
	Pwm.PWM_ENA |= 0x00000005;
}