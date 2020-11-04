/*
 * can_driver.c
 *
 * Created: 30.09.2020 11:23:27
 *  Author: magneah
 */ 
#include "mcp2515_driver.h"
#include "avr/interrupt.h"

//MCP_CANINTE to enable interupts
//MCP_CANINTF to read and clear interupts, need to clear before we can continue transmitting

uint8_t mcp2515_init(){
	uint8_t value;
	
	spi_init();
	mcp2515_reset();
	//sei();
	
	/*value = mcp2515_read(MCP_CANCTRL);
	value = MODE_LOOPBACK; */
	//mcp2515_write(MCP_CANCTRL, MODE_CONFIG); config is default after restart
	
}

uint8_t mcp2515_read(uint8_t address){
	uint8_t result;
	
	PORTB &= ~(1<<PB4); //ss
	spi_write(MCP_READ);
	spi_write(address);
	result = spi_read();
	
	PORTB |= (1<<PB4); //!ss
	
	return result;
}
void mcp2515_write(uint8_t address, uint8_t data){
	PORTB &= ~(1<<PB4); //slave select
	
	spi_write(MCP_WRITE);
	spi_write(address);
	spi_write(data);
	
	PORTB |= (1<<PB4); //slave deselect
}
void mcp2515_request_to_send(uint8_t command){
	PORTB &= ~(1<<PB4);
	
	spi_write(command);
	
	
	PORTB |= (1<<PB4);
}
void mcp2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data){
	PORTB &= ~(1<<PB4);
	
	spi_write(MCP_BITMOD);
	spi_write(address);
	spi_write(mask);
	spi_write(data);
	
	PORTB |= (1<<PB4);
}
void mcp2515_reset(){
	PORTB &= ~(1<<PB4);
	
	spi_write(MCP_RESET);
	
	PORTB |= (1<<PB4);
}
uint8_t mcp2515_read_status(){
	uint8_t result;
	
	PORTB &= ~(1<<PB4);
	
	spi_write(MCP_READ_STATUS);
	result = spi_read();
	
	
	PORTB |= (1<<PB4);
	
	return result;
}

