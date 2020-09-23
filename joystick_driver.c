#include "joystick_driver.h"

uint8_t x_offset = 156;
uint8_t y_offset = 164;

void get_adc_data(amap* atmelMap, joyVal* stick, sliderVal* slider){
	uint8_t val = 1;
	atmelMap->ADC[1] = 0x04;
	stick->x_val = atmelMap->ADC[1];
	stick->y_val = atmelMap->ADC[1];
	slider->l_val = atmelMap->ADC[1];
	slider->r_val = atmelMap->ADC[1];
}

void calc_offset(amap* atmelMap){
	uint8_t val = 1;
	atmelMap->ADC[1] = val;
	x_offset = atmelMap->ADC[1];
	y_offset = atmelMap->ADC[1];
}

void calc_pos(joyVal* values, uint8_t x, uint8_t y){
	if(x>x_offset){
		values->x_val = (x-x_offset)*(100)/(255-x_offset);
		}else if(x<x_offset){
		values->x_val = -(x_offset-x)*(100)/x_offset;
	}
	if(y>y_offset){
		values->y_val = (y-y_offset)*(100)/(255-y_offset);
		}else if(y<y_offset){
		values->y_val = -(y_offset-y)*(100)/y_offset;
	}
}
void calc_pos_slider(sliderVal* values, uint8_t left, uint8_t right){
	values->l_val = left*100/255;
	values->r_val = right*100/255;
}