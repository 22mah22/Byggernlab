/*
 * can_driver.c
 *
 * Created: 30.09.2020 16:54:41
 *  Author: magneah
 */ 
#include "can_driver.h"

uint8_t buffer_number = 0;


uint8_t can_init(){
	
	mcp2515_init();
	
	
	//mcp2515_bit_modify(MCP_CANINTE,0b00001111,0b00001111);
	mcp2515_write(MCP_CANCTRL, MODE_LOOPBACK);	
}

void send_can_msg(can_message *msg){
	
	mcp2515_write(0x31+16*buffer_number, msg->id>>3);
	uint8_t lowbufferval = mcp2515_read(0x32);
	
	mcp2515_write(0x32+16*buffer_number, 0x00ff & ((lowbufferval&0b00011111) | (msg->id<<5)));
	
	uint8_t regvalue = mcp2515_read(0x35);
	mcp2515_write(0x35+16*buffer_number, (regvalue&0b11110000) | msg->data_length);
	
	for(uint8_t m = 0; m < msg->data_length; m++){
		mcp2515_write(0x36+m+16*buffer_number, msg->data[m]);
	}
	
	mcp2515_request_to_send(MCP_RTS_TX0+buffer_number);
}

can_message* receive_can_msg(uint8_t buffer_number){
	static can_message msg;
	msg.id = 0x00;
	uint16_t idHigh = mcp2515_read(0x31+16*buffer_number);
	uint16_t idLow = mcp2515_read(0x32+16*buffer_number);
	
	msg.id |= idLow>>5;
	msg.id |= idHigh<<3;
	
	uint8_t length;
	length = 0b00001111 & mcp2515_read(0x35);
	msg.data_length = length;
	
	for(uint8_t m = 0; m < length; m++){
		msg.data[m] = mcp2515_read(0x36+m+16*buffer_number);
	}
	
	//flag recieved
	
	return &msg;
}