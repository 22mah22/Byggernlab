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
	
	_delay_ms(100);
	
	oled_init(atmelMap);
	clear_oled(atmelMap);
	go_to_line(atmelMap,7);
	//oled_write_string("Gorbatsjov", 4);
	character_printer(atmelMap, pepe3, 104, 48);
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
		
		uint8_t pin4 = PIND & (1<< PIND4);
		uint8_t pin5 = PIND & (1<< PIND5);
		
		
		//get_adc_data(atmelMap, &joystick, &slider);
		calc_pos(&joystick,valx,valy);
		calc_pos_slider(&slider,vall,valr);
		printf("\r J_x: %4d, J_y: %4d, Slider 1: %3d, Slider 2: %3d |||| %3d,%3d",joystick.x_val,joystick.y_val,slider.l_val,slider.r_val,pin4,pin5);
		
		
	}

		/*
		printf("%d",1);
		printf("%d", USART_Receive());
		*/
	return 0;
}

