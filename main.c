/*
 * ice_ice.c
 *
 * Created: 26.08.2020 14:28:49
 * Author : magneah
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "USART.h"
#include <stdio.h>
#include <string.h>
#include "sram_test.h"
#include "joystick_driver.h"
#include "OLED_driver.h"
#include "DEFINITIONS.h"
#include "protagonists.h"

#include "menu.h"
#include "menu_list.h"

uint8_t currentMenu = 0;
uint8_t menuMax = 2;

const int *BASE = 0x1000;

typedef struct{
	struct menuItem* prev;
	struct menuItem* next;
	struct menuItem* parent;
	struct menuItem* child;
	uint8_t line;
	char* label;
} menuItem;




int main(void){
	
	joyVal joystick; 
	sliderVal slider; 
	volatile amap* atmelMap = (amap*) BASE;
	
	MCUCR |= (1<<SRE);

	SFIOR &= ~(1<<XMM0);
	SFIOR &= ~(1<<XMM1);
	SFIOR |= (1<<XMM2);
	
	DDRA |= 0x18;
	

	USART_Init ( MYUBRR );
	SRAM_test(); _delay_ms(5000);
		
	struct menuItem* head;
	list_init();



	oled_init(atmelMap);
	clear_oled(atmelMap);
	
		
	go_to_line(7);
	
	for(int i = 0; i < 92; i++){
		printf("\n");
	}
	
	
	while(1){
		
		uint8_t val = 1;
		atmelMap->ADC[1] = 0x04; 
		uint8_t valx = atmelMap->ADC[1];
		uint8_t valy = atmelMap->ADC[1];
		uint8_t vall = atmelMap->ADC[1];
		uint8_t valr = atmelMap->ADC[1];
		
		uint8_t left_button = PIND & (1<< PIND4);
		uint8_t right_button = PIND & (1<< PIND5);
		uint8_t joy_button = PINB & (1<< PINB1);
		
		
			
		
		//get_adc_data(atmelMap, &joystick, &slider);
		
		calc_pos(&joystick,valx,valy);
		calc_pos_slider(&slider,vall,valr);
		//printf("\r J_x: %4d, J_y: %4d, J_b: %3d Slider 1: %3d, Slider 2: %3d |||| %3d,%3d",joystick.x_val,joystick.y_val,joy_button,slider.l_val,slider.r_val,left_button,right_button);
		

		_delay_ms(1);
		
		
		direction = joystick_check(direction, joystick);
		update_position(direction);
		
		if(button_check(joy_button)){
			button_action();
		}
		
		
	}
	
	return 0;
}

