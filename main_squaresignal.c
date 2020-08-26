/*
 * ice_ice.c
 *
 * Created: 26.08.2020 14:28:49
 * Author : magneah
 */ 

#include <avr/io.h>
#define F_CPU 4915200
#include <util/delay.h>


int main(void)
{
    /* Replace with your application code */
	DDRA = 0x01;
    while (1) 
    {
		PORTA |= (1<<PA0);
		_delay_ms(1000);
		PORTA &= ~(1<<PA0);
		_delay_ms(1000);
    }
}

