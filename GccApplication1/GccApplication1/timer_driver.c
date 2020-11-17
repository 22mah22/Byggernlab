/*
 * timer_driver.c
 *
 * Created: 14.10.2020 17:55:55
 *  Author: magneah
 */ 

#include "sam.h"
#include "motor_controller.h"
#include "timer_driver.h"
	
static Tc *tc = 0x40080000;
uint8_t ti_counter = 0;
	
#define DEBUG_INTERRUPT 1

uint8_t get_controller_runs(){
	return ti_counter;
}

void increment_controller_runs(){
	ti_counter++;
}

void reset_controller_runs(){
	ti_counter = 0;
}

void timer_init(){
		
	PMC->PMC_PCER0 |= PMC_PCER0_PID27; //enable timer counter channel 0
		
	PIOB->PIO_PDR |= PIO_PDR_P25; //disable io on pinb 25
	PIOB->PIO_ABSR |= PIO_ABSR_P25; //PIO set peripheral b on pinb 25*/

	PIOB->PIO_PDR |= PIO_PDR_P27; //disable io on pinb 27
	PIOB->PIO_ABSR |= PIO_ABSR_P27; //PIO set peripheral b on pinb 27*/
	
	tc->TC_CHANNEL[0].TC_CMR = 0x0909C000;
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
void timer_change_duty_buzzer(uint8_t dutyCycle){
	
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
	
	tc->TC_CHANNEL[2].TC_RA = 0x000CD140 - (0xA410 + 0x1A4*dutyCycle); // TC_RA - (min_value + dutyCycle*1prosentOfDifference)
	
}

/*
double prev_error = 0;
double error = 0;
int paadrag = 0;
double kp = 20;
double ki = 20;
double kd = 1;
double sum_error = 0;
double T_periode = 0.02;

void TC1_Handler( void ){
	
	prev_error = error;
	error = joystick.left_val - get_pi_value();
	sum_error += error;
	paadrag = kp*error+T_periode*ki*sum_error+(kd/T_periode)*(error-prev_error);
	if(joystick.left_button){
		sum_error = 0; 
	}
	change_motor_speed_using_paadrag(paadrag);
	//printf("x: %d \n\r",paadrag);
	int a = tc->TC_CHANNEL[1].TC_SR; // funker uten?!
	NVIC_ClearPendingIRQ(ID_TC1);
	ti_counter++;
}*/

void TC2_Handler( void ){
	
	
	printf("wtrffffff\n\r");
	int a = tc->TC_CHANNEL[2].TC_SR; // funker uten?!
	NVIC_ClearPendingIRQ(ID_TC2);
}

void init_ch1_PI(){
	
	
	PMC->PMC_PCER0 |= PMC_PCER0_PID28; //enable timer counter channel 1
	
	NVIC_EnableIRQ(ID_TC1);
	
	PIOB->PIO_PDR |= PIO_PDR_P0; //disable io on pinb 0
	PIOB->PIO_ABSR |= PIO_ABSR_P0; //PIO set peripheral b on pinb 0*/
	
	tc->TC_CHANNEL[1].TC_CMR = 0x0009C000;
	tc->TC_CHANNEL[1].TC_RC = 0x000CD140;
	
	tc->TC_CHANNEL[1].TC_IER |= TC_IER_CPCS; // enable interrupt on compare with RC
	
	tc->TC_CHANNEL[1].TC_CCR = 0x00000001; //enables the clock
	tc->TC_CHANNEL[1].TC_CCR |= 0x1 << 2;
} 
void init_ch2(){
	
	
	PMC->PMC_PCER0 |= PMC_PCER0_PID29; //enable timer counter channel 2
	
	//NVIC_EnableIRQ(ID_TC2);
	
	PIOC->PIO_PDR |= PIO_PDR_P28; //disable io on pinb 0
	PIOC->PIO_ABSR |= PIO_ABSR_P28; //PIO set peripheral b on pinb 0*/
	
	tc->TC_CHANNEL[2].TC_CMR = 0x0909C000;
	tc->TC_CHANNEL[2].TC_RC = 0x000CD140;
	
	//tc->TC_CHANNEL[2].TC_IER |= TC_IER_CPCS; // enable interrupt on compare with RC
	
	tc->TC_CHANNEL[2].TC_CCR = 0x00000001; //enables the clock
	tc->TC_CHANNEL[2].TC_CCR |= 0x1 << 2;
	}