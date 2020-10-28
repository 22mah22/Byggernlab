#include "joystick_driver.h"



uint8_t x_offset = 160;
uint8_t y_offset = 160;

uint8_t previous = 1;
DIRECTION joydir = NEUTRAL;

DIRECTION direction;


void get_adc_data(amap* atmelMap, joyVal* stick, sliderVal* slider){
	uint8_t val = 1;
	atmelMap->ADC[1] = 0x04;
	stick->x_val = atmelMap->ADC[1];
	stick->y_val = atmelMap->ADC[1];
	slider->l_val = atmelMap->ADC[1];
	slider->r_val = atmelMap->ADC[1];
}

void calc_offset(){
	volatile char *adc = (char *) 0x1400;
	adc[0] = 0x01;
	x_offset = adc[0];
	y_offset = adc[0];
}

/* no longer in use
void calc_pos_stick(joyVal* values, char* adc){

	uint8_t x = adc[0];
	uint8_t y = adc[0];
	if(x>=x_offset){
		values->x_val = (x-x_offset)*(100)/(255-x_offset);
		}else if(x<x_offset){
		values->x_val = -(x_offset-x)*(100)/x_offset;
	}
	if(y>=y_offset){
		values->y_val = (y-y_offset)*(100)/(255-y_offset);
		}else if(y<y_offset){
		values->y_val = -(y_offset-y)*(100)/y_offset;
	}
}


void calc_pos_slider(sliderVal* values, uint8_t left, uint8_t right){
	values->l_val = left*100/255;
	values->r_val = right*100/255;
} */

uint8_t button_check(uint8_t current){
	if(current == 0 && previous == 1){
		previous = 0;
		printf("%s", "B");
		return 1;
	}else if(current != 0){
		previous = 1;
		//printf("%s", "C");
	}
	return 0;
}

void update_adc_values(joyVal* stick, sliderVal* slider){
	volatile char *adc = (char *) 0x1400;
	adc[0] = 0x01; // Må skrives til for å oppdatere adc registrene.
	uint8_t x = adc[0];
	uint8_t y = adc[0];
	uint8_t left = adc[0];
	uint8_t right = adc[0];
	
	if(x>=x_offset){
		stick->x_val = (x-x_offset)*(100)/(255-x_offset);
	}
	else if(x<x_offset){
		stick->x_val = -(x_offset-x)*(100)/x_offset;
	}
	if(y>=y_offset){
		stick->y_val = (y-y_offset)*(100)/(255-y_offset);
	}
	else if(y<y_offset){
		stick->y_val = -(y_offset-y)*(100)/y_offset;
	}
	
	slider->l_val = left*100/255;
	slider->r_val = right*100/255;
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

DIRECTION joystick_direction(DIRECTION dir, joyVal stick){
	if(stick.x_val < 50 && stick.x_val > -50 && stick.y_val < 50 && stick.y_val > -50 ){
		dir = NEUTRAL;
	}
	if(dir == NEUTRAL){
		if(stick.x_val > 95){
			return RIGHT;
		}
		if(stick.x_val < -95){
			return LEFT;
		}
		if(stick.y_val < -95){
			return DOWN;
		}
		if(stick.y_val > 95){
			return UP;
		}
		return NEUTRAL;
	}
	return WAITING;
}

void send_stick_can(){
	
	update_adc_values(&joystick, &slider);
	
	can_message msgToSend;
	msgToSend.data_length = 5;
	msgToSend.data[0] = abs(joystick.x_val);
	msgToSend.data[1] = abs(joystick.y_val);
	msgToSend.data[2] = PINB & (1<< PINB1); // button pressed?
	
	uint8_t x_positive = (joystick.x_val < 0) ? 0x00 : 0x11;
	uint8_t y_positive = (joystick.y_val < 0) ? 0x00 : 0x11;
	
	msgToSend.data[3] = x_positive;
	msgToSend.data[4] = y_positive;
	
	msgToSend.id = 0x0010;
	send_can_msg(&msgToSend);
	
}