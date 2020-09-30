/*
 * spi_driver.c
 *
 * Created: 30.09.2020 11:22:46
 *  Author: magneah
 */ 

#include "spi_driver.h"




uint8_t spi_read(){
	
	spi_write(0xf0);
	return SPDR;
}

void spi_init(){
	DDRB = (1<<DDB4)|(1<<DDB5)|(1<<DDB7); //chip select, mosi, clock
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

void spi_write(char data){
	SPDR = data;
	while(!(SPSR & (1<<SPIF))){
		
	}
}