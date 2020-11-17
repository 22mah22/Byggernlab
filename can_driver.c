/*
 * can_driver.c
 *
 * Created: 30.09.2020 16:54:41
 *  Author: magneah
 */ 
#include "can_driver.h"
#include "DEFINITIONS.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include "joystick_driver.h"
#include <util/delay.h>

#define idBufferHighAddress 0x31
#define idBufferLowAddress 0x32
#define dataLengthBufferAddress 0x35
#define dataBufferAddress 0x36

uint8_t buffer_number = 0;

volatile uint8_t can_flag = 0;

ISR(INT0_vect){
	can_flag = 1;
}

uint8_t can_interrupted(){
	if (can_flag){	
		can_flag = 0;
		return 1;
	}
	return 0;
}

void can_interrupt_enable(){
	cli();
	set_bit(MCUCR, ISC01);
	clear_bit(MCUCR, ISC00);
	// Enable interrupt on PD2/INT0 on the AtMega
	set_bit(GICR,INT0);
	sei();
}

void can_init(){
	
	mcp2515_init();
	mcp2515_reset();
	
	//mcp2515_bit_modify(MCP_CANINTE,0b11111111,0b11111111);
	//mcp2515_write(MCP_CANCTRL, MODE_LOOPBACK);	
	
	
	
	
	/*mcp2515_bit_modify(MCP_CNF3, 0b00000111, 0x01);		//PS2: 2*Tq
	
	mcp2515_bit_modify(MCP_CNF2, 0b00000111, 0x05);		//PRSEG: 6*Tq
	mcp2515_bit_modify(MCP_CNF2, 0b00111000, 0x06<<3);	//PHSEG1: 7*Tq
	mcp2515_bit_modify(MCP_CNF2, 0b01000000, 0x00<<6);	//SAM: 0 Busline sample once
	mcp2515_bit_modify(MCP_CNF2, 0b10000000, 0x01<<7);	//BTLMODE: Length of PS2 determined by PHSEG2 bits in CNF3
	
	mcp2515_bit_modify(MCP_CNF1, 0b11000000, 0x00<<6);	//SJW: 1*Tq
	mcp2515_bit_modify(MCP_CNF1, 0b00111111, 0x03);*/
	
	mcp2515_write(MCP_CNF3, 0x01); //0x01 // 0b00000010
	mcp2515_write(MCP_CNF2, 0xb5); //0xb5 // 0b10010010 original
	mcp2515_write(MCP_CNF1, 0x43); //0x43 // 0b01000000
	
	mcp2515_bit_modify(MCP_CANINTE, 0b00000011, MCP_RX_INT);
	
	mcp2515_write(MCP_CANCTRL, MODE_NORMAL);
	//mcp2515_write(MCP_CANCTRL, MODE_LOOPBACK);	
	
	
	
	
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
	//mcp2515_bit_modify(MCP_CANINTF, 0xff, 0x00);
	mcp2515_request_to_send(MCP_RTS_TX0+buffer_number);
	//mcp2515_bit_modify(MCP_TXB0CTRL+16*buffer_number,0b00001000,0b00001000);
	//mcp2515_bit_modify(0x0D,0b00000111,0b00000111);
}

can_message* receive_can_msg(uint8_t buffer_number){
	uint8_t status = mcp2515_read_status();
	static can_message msg;
	msg.id = 0x00;
	uint16_t idHigh = mcp2515_read(0x61+16*buffer_number);
	uint16_t idLow = mcp2515_read(0x62+16*buffer_number);
	
	msg.id |= idLow>>5;
	msg.id |= idHigh<<3;
	
	uint8_t length;
	length = 0b00001111 & mcp2515_read(0x65);
	msg.data_length = length;
	for(uint8_t m = 0; m < length; m++){
		//msg.data[m] = mcp2515_read(dataBufferAddress+m+16*buffer_number);
		msg.data[m] = mcp2515_read(0x66+m+16*buffer_number);
	}
	
	//Reset interrupt flag
	mcp2515_bit_modify(MCP_CANINTF, 1, 0);
	mcp2515_bit_modify(MCP_CANINTF, 2, 0);
	
	return &msg;
}

uint8_t can_check_complete(uint8_t buffer_number){
	uint8_t active_flags = mcp2515_read(MCP_CANINTF);
	uint8_t isBufferTransmitted = (active_flags & (MCP_TX0IF+2*buffer_number));
	if(!(isBufferTransmitted & (MCP_TX0IF+2*buffer_number)) ){
		return 0;
	}
	printf("check");
	mcp2515_bit_modify(MCP_CANINTF,MCP_TX0IF+2*buffer_number,0x00);
	return 1;
}

void send_stick_can(){
	
	update_adc_values();
	joyVal joystick = get_joyvals();
	sliderVal slider = get_slidervals();
	
	can_message msgToSend;
	msgToSend.data_length = 8;
	msgToSend.data[0] = abs(joystick.x_val);
	msgToSend.data[1] = abs(joystick.y_val);
	msgToSend.data[2] = PINB & (1<< PINB1); // button pressed?
	
	uint8_t x_positive = (joystick.x_val < 0) ? 0x00 : 0x11;
	uint8_t y_positive = (joystick.y_val < 0) ? 0x00 : 0x11;
	
	msgToSend.data[3] = x_positive;
	msgToSend.data[4] = y_positive;
	msgToSend.data[5] = slider.l_val;
	msgToSend.data[6] = slider.r_val;
	msgToSend.data[7] = (PIND & (1<< PIND4)) >> 3 | (PIND & (1<< PIND5)) >> 5; 
	//left and right button on second least significant and least significant

	 
	
	msgToSend.id = 0x0016;
	_delay_ms(20);
	send_can_msg(&msgToSend);
	
}

void send_difficulty_can(uint8_t diff){
	can_message msgToSend;
	msgToSend.data_length = 1;
	if(diff == 1){//easy
		msgToSend.data[0] = 1;
	}
	else if (diff == 3){//hard
		msgToSend.data[0] = 3;
	}
	else{ //set to medium
		msgToSend.data[0] = 2;
	}

	msgToSend.id = 0x6;
	_delay_ms(20);
	send_can_msg(&msgToSend);
	
}

void send_game_start_can(){
	can_message msgToSend;
	msgToSend.data_length = 1;
	msgToSend.id = 0x2;
	//placeholder
	msgToSend.data[0] = 0;
	send_can_msg(&msgToSend);
}

void send_reaction_start_can(){
	can_message msgToSend;
	msgToSend.data_length = 1;
	msgToSend.id = 0x4;
	//
	msgToSend.data[0] = 0;
	send_can_msg(&msgToSend);
}

void send_reaction_stop_can(){
	can_message msgToSend;
	msgToSend.data_length = 1;
	msgToSend.id = 0x3;
	//placeholder
	msgToSend.data[0] = 0;
	send_can_msg(&msgToSend);
}