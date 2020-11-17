#include "joystick_driver.h"
#include <util/delay.h>




uint8_t x_offset = 160;
uint8_t y_offset = 160;

uint8_t previous = 1;
DIRECTION joydir = NEUTRAL;

static joyVal joystick;
static sliderVal slider;
DIRECTION direction;

joyVal get_joyvals(){
	return joystick;
}

sliderVal get_slidervals(){
	return slider;
}

void calc_offset(){
	volatile char *adc = (char *) 0x1400;
	adc[0] = 0x01;
	x_offset = adc[0];
	y_offset = adc[0];
}

uint8_t button_check(uint8_t current){
	if(current == 0 && previous == 1){
		previous = 0;
		return 1;
	}else if(current != 0){
		previous = 1;
	}
	return 0;
}

void update_adc_values(){
	volatile char *adc = (char *) 0x1400;
	adc[0] = 0x01; // M� skrives til for � oppdatere adc registrene.
	uint8_t x = adc[0];
	uint8_t y = adc[0];
	uint8_t left = adc[0];
	uint8_t right = adc[0];
	
	if(x>=x_offset){
		joystick.x_val = (x-x_offset)*(100)/(255-x_offset);
	}
	else if(x<x_offset){
		joystick.x_val = -(x_offset-x)*(100)/x_offset;
	}
	if(y>=y_offset){
		joystick.y_val = (y-y_offset)*(100)/(255-y_offset);
	}
	else if(y<y_offset){
		joystick.y_val = -(y_offset-y)*(100)/y_offset;
	}
	
	slider.l_val = left*100/255;
	slider.r_val = right*100/255;
}
/*
DIRECTION joystick_direction(joyVal stick){
	if(joydir == NEUTRAL){
		if(stick.x_val > 80){
			joydir = RIGHT;
			return joydir;
		}
		if(stick.x_val < -80){
			joydir = LEFT;
			return joydir;
		}
		if(stick.y_val > 80){
			joydir = UP;
			return joydir;
		}
		if(stick.y_val < -80){
			joydir = DOWN;
			return joydir;
		}
	}
	joydir = NEUTRAL;
	return joydir;
	
}*/

DIRECTION joystick_direction(DIRECTION dir){
	if(joystick.x_val < 50 && joystick.x_val > -50 && joystick.y_val < 50 && joystick.y_val > -50 ){
		dir = NEUTRAL;
	}
	if(dir == NEUTRAL){
		if(joystick.x_val > 95){
			return RIGHT;
		}
		if(joystick.x_val < -95){
			return LEFT;
		}
		if(joystick.y_val < -95){
			return DOWN;
		}
		if(joystick.y_val > 95){
			return UP;
		}
		return NEUTRAL;
	}
	return WAITING;
}
