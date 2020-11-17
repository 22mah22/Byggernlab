#include "pid.h"
#include "sam.h"
#include "motor_controller.h"
#include "timer_driver.h"

static Tc *tc = 0x40080000;

double prev_error = 0;
double error = 0;
int paadrag = 0;
double kp = 20;
double ki = 20;
double kd = 1;
double sum_error = 0;
double T_periode = 0.02;
int active = 0;

uint8_t difficulty = 0;

void TC1_Handler( void ){
	
	prev_error = error;
	error = joystick.left_val - get_pi_value();
	sum_error += error;
	paadrag = active*((kp+difficulty*10)*error+T_periode*(ki-difficulty*4)*sum_error+((kd + difficulty*1)/T_periode)*(error-prev_error));
	if(joystick.left_button){
		sum_error = 0; 
	}
	change_motor_speed_using_paadrag(paadrag);
	//printf("x: %d \n\r",paadrag);
	int a = tc->TC_CHANNEL[1].TC_SR; // funker uten?!
	NVIC_ClearPendingIRQ(ID_TC1);
	increment_controller_runs();
}
uint8_t get_difficulty(){
	return difficulty;
};
void set_difficulty(uint8_t difficulty_to_set){
	difficulty = difficulty_to_set;
};

void stop_pid(){
	active = 0;
}
void start_pid(){
	active = 1;
}