/*
 * joystick.c
 *
 * Created: 14.10.2020 14:49:57
 *  Author: magneah
 */ 
 #include "joystick.h"
 #include "timer_driver.h"
 #include "printf-stdarg.h"
 #include "uart.h"
 
 
 
 
 void move_solenoid(){
	 printf("joystick.x_val : %d \n\r", joystick.x_val);
	 
	 if(joystick.x_val < 0){
		 uint8_t val = 50-abs(joystick.x_val)*0.5;
		 timer_change_duty(val);
	 }
	 if(joystick.x_val >= 0){
		 uint8_t val2 = 50+joystick.x_val*0.5;
		 timer_change_duty(val2);
	 }
 }