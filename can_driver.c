/*
 * can_driver.c
 *
 * Created: 30.09.2020 16:54:41
 *  Author: magneah
 */ 
#include "can_driver.h"

#include <avr/interrupt.h>

#define idBufferHighAddress 0x31
#define idBufferLowAddress 0x32
#define dataLengthBufferAddress 0x35
#define dataBufferAddress 0x36

uint8_t buffer_number = 0;


uint8_t can_init(){
	
	mcp2515_init();
	
	
	mcp2515_bit_modify(MCP_CANINTE,0b00000111,0b00000111);
	//mcp2515_write(MCP_CANCTRL, MODE_LOOPBACK);	
	mcp2515_write(MCP_CNF3, 0x01); //0x01 // 0b00000010
	mcp2515_write(MCP_CNF2, 0xb5); //0xb5 // 0b10010010
	mcp2515_write(MCP_CNF1, 0x43); //0x43 // 0b01000000
	
	
	mcp2515_write(MCP_CANCTRL, MODE_NORMAL);
	
	
// 	cli();
// 	
// 	
// 	MCUCR |= 1 << ISC01;
// 	MCUCR &= ~(1 << ISC00);
// 	GICR |= 1 << INT0;
// 	
// 	sei();
	
}

void send_can_msg(can_message *msg){
	
	/*while(!can_check_complete(buffer_number)){
		buffer_number += 1;
		if(buffer_number > 2){
			buffer_number = 0;
		}
	}*/
	
	mcp2515_write(idBufferHighAddress+16*buffer_number, msg->id>>3);
	uint8_t lowbufferval = mcp2515_read(0x32);
	
	mcp2515_write(idBufferLowAddress+16*buffer_number, 0x00ff & ((lowbufferval&0b00011111) | (msg->id<<5)));
	
	uint8_t regvalue = mcp2515_read(0x35);
	mcp2515_write(dataLengthBufferAddress+16*buffer_number, (regvalue&0b11110000) | msg->data_length);
	
	for(uint8_t m = 0; m < msg->data_length; m++){
		mcp2515_write(dataBufferAddress+m+16*buffer_number, msg->data[m]);
	}
	
	/*buffer_number += 1;
	if(buffer_number > 2){
		buffer_number = 0;
	}*/
	
	mcp2515_request_to_send(MCP_RTS_TX0+buffer_number);
	//mcp2515_bit_modify(MCP_TXB0CTRL+16*buffer_number,0b00001000,0b00001000);
	//mcp2515_bit_modify(0x0D,0b00000111,0b00000111);
}

can_message* receive_can_msg(uint8_t buffer_number){
	static can_message msg;
	msg.id = 0x00;
	uint16_t idHigh = mcp2515_read(idBufferHighAddress+16*buffer_number);
	uint16_t idLow = mcp2515_read(idBufferLowAddress+16*buffer_number);
	
	msg.id |= idLow>>5;
	msg.id |= idHigh<<3;
	
	uint8_t length;
	length = 0b00001111 & mcp2515_read(dataLengthBufferAddress);
	msg.data_length = length;
	
	for(uint8_t m = 0; m < length; m++){
		msg.data[m] = mcp2515_read(dataBufferAddress+m+16*buffer_number);
	}
	
	//flag recieved
	
	return &msg;
}

uint8_t can_check_complete(uint8_t buffer_number){
	uint8_t active_flags = mcp2515_read(MCP_CANINTF);
	uint8_t isBufferTransmitted = (active_flags & (MCP_TX0IF+2*buffer_number));
	printf("%d || \r", active_flags);
	if(!(isBufferTransmitted & (MCP_TX0IF+2*buffer_number)) ){
		return 0;
	}
	printf("check");
	mcp2515_bit_modify(MCP_CANINTF,MCP_TX0IF+2*buffer_number,0x00);
	return 1;
}