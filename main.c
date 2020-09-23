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

const int *BASE = 0x1000;

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

typedef struct{
	struct menuItem* prev;
	struct menuItem* next;
	
	uint8_t line;
	char* label;
} menuItem;




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
	SRAM_test(); _delay_ms(5000);
		
	struct menuItem* head;

	menuItem* ptr;
	ptr = (menuItem*)malloc(sizeof(menuItem));

	ptr->label = "first";
	ptr->line = 0;
	ptr->prev = NULL;
	ptr->next = NULL;
	head = ptr;

	ptr = (menuItem*)malloc(sizeof(menuItem));

	menuItem* temp = head;

	ptr->label = "second";
	while(temp->next != NULL){
		temp = temp->next;
	}
	temp->next = ptr;
	ptr->prev = temp;
	ptr->next = NULL;

	ptr = (menuItem*)malloc(sizeof(menuItem));

	temp = head;

	ptr->label = "third";
	while(temp->next != NULL){
		temp = temp->next;
	}
	temp->next = ptr;
	ptr->prev = temp;
	ptr->next = NULL;

	ptr = head;

	oled_init(atmelMap);
	clear_oled(atmelMap);
	
	uint8_t counter = 0;
	while(ptr != NULL){
		printf("%s \n", ptr->label);
		go_to_column(0);
		oled_write_string(counter,ptr->label, 8);
		ptr = ptr->next;
		counter ++;
	}
		
	go_to_line(7);
	//oled_write_string(0," Kongeriget Norge er et frit, uafhaengigt og udeleligt Rige. Dets Regjeringsform er indskraenket og arvelig-monarkisk.", 8);
	character_printer(atmelMap, wojak, 64, 40);
	/*
	go_to_line(atmelMap, 2);
	go_to_column(atmelMap, 0);
	for(int i = 0; i < 127; i++){
		
		go_to_column(atmelMap, i);
		atmelMap->OLED_DATA[1] = 0b10101010;
		if(i>20){
			go_to_column(atmelMap, i-21);
			atmelMap->OLED_DATA[1] = 0x00;
		}
		
		_delay_ms(20);
		
	}*/
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
		
		
		if(button_check(joy_button)){
			//do something
		}
			
		
		//get_adc_data(atmelMap, &joystick, &slider);
		
		calc_pos(&joystick,valx,valy);
		calc_pos_slider(&slider,vall,valr);
		printf("\r J_x: %4d, J_y: %4d, J_b: %3d Slider 1: %3d, Slider 2: %3d |||| %3d,%3d",joystick.x_val,joystick.y_val,joy_button,slider.l_val,slider.r_val,left_button,right_button);
	}

		/*
		printf("%d",1);
		printf("%d", USART_Receive());
		*/
	return 0;
}

