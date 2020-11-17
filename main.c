/*
 * ice_ice.c
 *
 * Created: 26.08.2020 14:28:49
 * Author : magneah
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "DEFINITIONS.h"
#include <util/delay.h>
#include "USART.h"
#include <stdio.h>
#include <string.h>
//#include "sram_test.h"
#include "joystick_driver.h"
#include "OLED_driver.h"

//#include "protagonists.h"
#include "mcp2515_driver.h"
#include "can_driver.h"

#include "menu.h"

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

int main(void){
	
//  	joyVal joystick; 
//  	sliderVal slider; 
//	volatile amap* atmelMap = (amap*) BASE;
	
	USART_Init ( MYUBRR );
	
	//enable external memory interface
	MCUCR |= (1<<SRE);
	
	//select which c pins on atmega to be released for normal use, the rest is used for high address bytes
	SFIOR &= ~(1<<XMM0);
	SFIOR &= ~(1<<XMM1);
	SFIOR |= (1<<XMM2);
	
	DDRA |= 0x18;
	/*
	_delay_ms(1000);
	volatile char * sram = (char *) 0x1800;
	uint8_t value5 = 5;
	
	printf("\n\n\n\n\nasdhfkajsdhfjksa %d \r\n\n\n\n\n", ext_ram[15]);
	printf("\n\n\n\n\nasdhfkajsdhfjksa %d \r\n\n\n\n\n", ext_ram[16]);
	_delay_ms(1000);
	*//*
	volatile char * sram = (char *) 0x1800;*/
	can_init();
	

	can_interrupt_enable();
	//SRAM_test(); _delay_ms(1000);
	launch_menusystem();
	
	while(1){
		// CAN BUS TEST
		//msgToReceive = receive_can_msg(0);
		//_delay_ms(5000);
		//send_can_msg(&msgToSend);
		send_stick_can();
		_delay_ms(50);


		printf("fail");
	}
	
	return 0;
}

