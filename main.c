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
struct {
	uint8_t OLED_CMD[512];
	uint8_t OLED_DATA[512];
	uint8_t ADC[1024];
	uint8_t SRAM[2048];
} amap;

int main(void){
	MCUCR |= (1<<SRE);
	
	
	//DDRC = 0xFF;
	//PORTC = 0x00;
	
	
	SFIOR &= ~(1<<XMM0);
	SFIOR &= ~(1<<XMM1);
	SFIOR |= (1<<XMM2);


	USART_Init ( MYUBRR );
	//SRAM_test();
	
	_delay_ms(500);
	volatile char *ext_adc = (char *) 0x1000;
	for (uint16_t i = 0; i < 0x400; i++) {
		uint8_t some_value = rand();
		ext_adc[i] = some_value;
		
	}
	
	/*DDRA = 0x01;

	
	PORTE |= (1<<PE1); // set ALE high
	
	_delay_ms(100);
	
	PORTA |= (1<<PA0);
	
	_delay_ms(100);
	
	PORTE &= ~(1<<PE1); // set ALE low (valid addr)
	
	_delay_ms(100);
*/
	
	
	/*
	
	while(1){
		DDRA = 0x01;
		PORTA |= (1<<PA0);
		_delay_ms(1000);
		PORTA &= ~(1<<PA0);
		_delay_ms(1000);
		//USART_Transmit('h');
		//USART_Receive();
		printf("%s", "hei");
		led_test();
		
	}
		
		
	printf("%d",1);
	printf("%d", USART_Receive());
	*/
	return 0;
}

