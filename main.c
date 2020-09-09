/*
 * ice_ice.c
 *
 * Created: 26.08.2020 14:28:49
 * Author : magneah
 */ 

#include <avr/io.h>
#define F_CPU 4915200
#include <util/delay.h>
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1
#include "UART.h"
#include <stdio.h>
#include "sram_test.c"

uint8_t x_offset = 156;
uint8_t y_offset = 164;

void led_test(void){
	
	DDRA = 0x01;
	PORTE |= (1<<PE1); // set ALE high
	
	PORTA |= (1<<PA0);
	//_delay_ms(10);
	PORTE &= ~(1<<PE1); // set ALE low (valid addr)
	//_delay_ms(10);
	PORTE |= (1<<PE1); // set ALE high
	PORTA &= ~(1<<PA0);
	//_delay_ms(10);
	PORTE &= ~(1<<PE1); // set ALE low (valid addr)
}

const int *BASE = 0x0FFF;
typedef struct {
	uint8_t OLED_CMD[512];
	uint8_t OLED_DATA[512];
	uint8_t ADC[1024];
	uint8_t SRAM[2048];
} amap;

typedef struct {
	int8_t x_val;
	int8_t y_val;
} joyVal;

typedef struct {
	uint8_t l_val;
	uint8_t r_val;
} sliderVal;

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

typedef enum{
		LEFT,
		UPLEFT,
		RIGHT,
		UPRIGHT,
		UP,
		DOWN,
		NEUTRAL,
} DIRECTION;

DIRECTION calc_dir(joyVal* val){
	//if()
	return LEFT;
}

int main(void){
	
	joyVal joystick;
	sliderVal slider;
	volatile amap* atmelMap = (amap*) BASE;
	
	
	MCUCR |= (1<<SRE);
	
	
	//DDRC = 0xFF;
	//PORTC = 0x00;
	
	SFIOR &= ~(1<<XMM0);
	SFIOR &= ~(1<<XMM1);
	SFIOR |= (1<<XMM2);
	
	DDRA |= 0x18;
	
	
	//calc_offset(atmelMap);
	
	/*
	PORTB |= (1<<DDB1);
	TCCR2 |= (1<<WGM20);
	TCCR2 |= (1<<WGM20);	
	TCCR2 |= (1<<COM21);
	TCCR2 |= (1<<COM20);
	*/

	USART_Init ( MYUBRR );
	SRAM_test();
	
	_delay_ms(500);
	
	while(1){

		uint8_t val = 1;
		atmelMap->ADC[1] = 0x04;
		uint8_t valx = atmelMap->ADC[1];
		uint8_t valy = atmelMap->ADC[1];
		uint8_t vall = atmelMap->ADC[1];
		uint8_t valr = atmelMap->ADC[1];
		
		uint8_t pin4 = PIND & (1<< PIND4);
		uint8_t pin5 = PIND & (1<< PIND5);
		
		
		//get_adc_data(atmelMap, &joystick, &slider);
		calc_pos(&joystick,valx,valy);
		calc_pos_slider(&slider,vall,valr);
		printf("%d,%d,%d,%d ||| %d,%d \n",joystick.x_val,joystick.y_val,slider.l_val,slider.r_val,pin4,pin5);
		
	}

		/*
		printf("%d",1);
		printf("%d", USART_Receive());
		*/
	return 0;
}

