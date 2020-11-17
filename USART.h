/**
 * @file
 * @brief Driver module for handling data transmission using USART.
 */

#pragma once
#include <avr/io.h>
#include "DEFINITIONS.h"

/**
 * @brief Function to initialize USART.
 * @param ubrr Value used to choose baudrate, ubrr = F_CPU/16/BAUD-1
 */

void USART_Init (unsigned int ubrr );

/**
 * @brief Function to transmit a 5 to 8 bit char.
 * @param data char to send using USART.
 */

void USART_Transmit(unsigned char data);

/**
 * @brief Function to transmit a 9 bit char.
 * @param data char to send using USART.
 */

void USART_Transmit9(unsigned char data);

/**
 * @brief Function to receive a 5 to 8 bit char.
 * @return data char to send using USART.
 */

unsigned int USART_Receive(void);

/**
 * @brief Function to receive a 9 bit char.
 * @return data char to send using USART.
 */

unsigned int USART_Receive9(void);