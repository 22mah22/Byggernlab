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

int main(void){
	USART_Init ( MYUBRR );
	while(1){
		DDRA = 0x01;
		PORTA |= (1<<PA0);
		_delay_ms(1000);
		PORTA &= ~(1<<PA0);
		_delay_ms(1000);
		//USART_Transmit('h');
		//USART_Receive();
		printf("%s", "hei");
		
	}
		
		
	printf("%d",1);
	printf("%d", USART_Receive());
	return 0;
}

