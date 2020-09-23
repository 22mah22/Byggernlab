#pragma once
#include <avr/io.h>
#include "DEFINITIONS.h"

void USART_Init (unsigned int ubrr );
void USART_Transmit(unsigned char data);

void USART_Transmit9(unsigned char data);

unsigned int USART_Receive9(void);

unsigned int USART_Receive(void);