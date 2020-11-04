/*
 * ice_ice.c
 *
 * Created: 26.08.2020 14:28:49
 * Author : magneah
 */ 

#include <avr/io.h>
#include "DEFINITIONS.h"
#include <util/delay.h>
#include "USART.h"
#include <stdio.h>
#include <string.h>
#include "sram_test.h"
#include "joystick_driver.h"
#include "OLED_driver.h"

//#include "protagonists.h"
#include "mcp2515_driver.h"
#include "can_driver.h"

#include "menu.h"

uint8_t currentMenu = 0;
uint8_t menuMax = 2;

//const int *BASE = 0x1000;

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
//	volatile amap* atmelMap = (amap*) BASE;
	
	
	
	//enable external memory interface
	MCUCR |= (1<<SRE);
	
	//DDRC = 0xFF;
	//PORTC = 0x00;
	
	
	//select which c pins on atmega to be released for normal use, the rest is used for high address bytes
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
	SRAM_test(); _delay_ms(1000);
		
		
	//Check if the whole thing just works from up here:
	launch_menusystem();
	
		
	go_to_line(7);
	//oled_write_string(0," Kongeriget Norge er et frit, uafhaengigt og udeleligt Rige. Dets Regjeringsform er indskraenket og arvelig-monarkisk.", 8);
	//character_printer(wojak, 64, 40);
	//_delay_ms(60000);

	for(int i = 0; i < 92; i++){
		printf("\n");
		
		
	}
	
	can_init();
	
	can_message msgToSend;
	msgToSend.data_length = 8;
	for(int i = 0; i < 8; i++){
		msgToSend.data[i] = 97+i;
	}
	msgToSend.id = 0x0006;
	
	can_message* msgToReceive;
	
	
	//msgToReceive = receive_can_msg(0);
	
	/*while(1){
		for(int i = 0; i < 8; i++){
			printf("\r   %c | %d | %d   \r",msgToReceive->data[i],msgToReceive->data_length,msgToReceive->id);
			_delay_ms(5000);
		}
	}*/
	
	
	
	calc_offset();
	while(1){
		// CAN BUS TEST
		
		//_delay_ms(5000);
		//send_can_msg(&msgToSend);
		printf("Program running %d \r\n", 2);
		send_stick_can(&msgToSend);
		_delay_ms(5);

		/*for(int i = 0; i < 8; i++){
			printf("\r   %c | %d | %d   \n\r",msgToSend.data[i],msgToSend.data_length,msgToSend.id);
			_delay_ms(200);
		}*/
		
	}

		/*
		printf("%d",1);
		printf("%d", USART_Receive());
		*/
	return 0;
}

