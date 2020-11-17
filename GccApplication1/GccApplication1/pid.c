#include "pid.h"
#include "sam.h"
#include "motor_controller.h"

double prev_error = 0;
double error = 0;
int paadrag = 0;
double kp = 20;
double ki = 20;
double kd = 1;
double sum_error = 0;
double T_periode = 0.02;

uint8_t difficulty = 0;

void TC1_Handler( void ){
	
	prev_error = error;
	error = joystick.left_val - get_pi_value();
	sum_error += error;
	paadrag = (kp+difficulty*10)*error+T_periode*(ki-difficulty*4)*sum_error+((kd + difficulty*1)/T_periode)*(error-prev_error);
	if(joystick.left_button){
		sum_error = 0; 
	}
	change_motor_speed_using_paadrag(paadrag);
	//printf("x: %d \n\r",paadrag);
	int a = tc->TC_CHANNEL[1].TC_SR; // funker uten?!
	NVIC_ClearPendingIRQ(ID_TC1);
	ti_counter++;
}
uint8_t get_difficulty(){
	return difficulty;
};
void set_difficulty(uint8_t difficulty_to_set){
	difficulty = difficulty_to_set;
};