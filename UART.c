#include "UART.h"
#include <stdio.h>
#define clear_bit( reg, bit ) (reg &= ~(1 << bit))

void USART_Init (unsigned int ubrr ){
	
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	
	UCSR1C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);
	clear_bit(UCSR0C, 0); // Clock polarity
	fdevopen(USART_Transmit, USART_Receive);
}
void USART_Transmit(unsigned char data){
	while (!(UCSR0A & (1<<UDRE0)));
	
	UDR0 = data;
}

void USART_Transmit9(unsigned char data){
	while (!(UCSR0A & (1<<UDRE0)));
	UCSR0B &= ~(1<<TXB80);
	if (data & 0x0100) {
		UCSR0B |= (1<<TXB80);
	}
	UDR0 = data;
	
}

unsigned int USART_Receive9(void)
{
	unsigned char status, resh, resl;
	while (!(UCSR0A & (1<<RXC0)));
	status = UCSR0A;
	resh = UCSR0B;
	resl = UDR0;
	if (status & (1<<FE0)|(1<<DOR0)|(1<<UPE0)){
		return -1;
	}
	resh = (resh >> 1) & 0x01;
	return ((resh << 8) | resl);
}

unsigned int USART_Receive(void)
{
	
	while (!(UCSR0A & (1<<RXC0)));
	

	return UDR0;
}