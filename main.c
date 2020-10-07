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
//#include "protagonists.h"
#include "mcp2515_driver.h"
#include "can_driver.h"

#include "menu.h"

uint8_t currentMenu = 0;
uint8_t menuMax = 2;

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
	struct menuItem* parent;
	struct menuItem* child;
	uint8_t line;
	char* label;
} menuItem;




int main(void){
	
//  	joyVal joystick; 
//  	sliderVal slider; 
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
		


	oled_init(atmelMap);
	clear_oled(atmelMap);
	
		
	go_to_line(7);
	//oled_write_string(0," Kongeriget Norge er et frit, uafhaengigt og udeleligt Rige. Dets Regjeringsform er indskraenket og arvelig-monarkisk.", 8);
	//character_printer(wojak, 64, 40);
	//_delay_ms(60000);
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
	
	menu** headPointer = NULL;
	
	menu* mainMenu;
	mainMenu = new_menu(NULL);
	menu* submenu = new_menu(mainMenu);
	submenu->labels[0] = "laks1";
	submenu->labels[1] = "laks2";
	submenu->labels[2] = "laks3";
	submenu->labels[3] = "laks4";
	submenu->labels[4] = "";
	submenu->labels[5] = "";
	submenu->labels[6] = "";
	mainMenu->links[0] = submenu;
	//submenu->fun_ptr = printwojak_prototyp;
	write_menu_to_screen(mainMenu);
	
	headPointer = &mainMenu;
	
	
	can_init();
	
	can_message msgToSend;
	msgToSend.data_length = 8;
	for(int i = 0; i < 8; i++){
		msgToSend.data[i] = 97+i;
	}
	msgToSend.id = 0xffff;
	
	can_message* msgToReceive;
	
	
	//msgToReceive = receive_can_msg(0);
	
	/*while(1){
		for(int i = 0; i < 8; i++){
			printf("\r   %c | %d | %d   \r",msgToReceive->data[i],msgToReceive->data_length,msgToReceive->id);
			_delay_ms(5000);
		}
	}*/
	
	/*
	mcp2515_init();
	char ch;
	while(1){
		mcp2515_write(0x36, 98);
		mcp2515_write(0x46, 99);
		mcp2515_write(0x56, 100);
		ch = mcp2515_read(0x36);
		printf("%c |||| \r\n", ch);
		ch = mcp2515_read(0x46);
		printf("%c |||| \r\n", ch);
		ch = mcp2515_read(0x56);
		printf("%c |||| \r\n", ch);
		_delay_ms(5000);
	}*/
	while(1){
		
		_delay_ms(5000);
		send_can_msg(&msgToSend);

		for(int i = 0; i < 8; i++){
			printf("\r   %c | %d | %d   \r",msgToSend.data[i],msgToSend.data_length,msgToSend.id);
			_delay_ms(1000);
		}
		
		
		
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
		DIRECTION current_dir = joystick_direction(current_dir, joystick);
		if(current_dir != NEUTRAL && current_dir != WAITING){
			change_selected(headPointer, current_dir);
		}
		if(button_check(joy_button)){
			button_pressed(headPointer);
		}
		
		
		
		
		
	}

		/*
		printf("%d",1);
		printf("%d", USART_Receive());
		*/
	return 0;
}

