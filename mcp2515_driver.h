/*
 * can_driver.h
 *
 * Created: 30.09.2020 11:23:38
 *  Author: magneah
 */ 

#pragma once

#include <avr/io.h>
#include <stdint.h>
#include "mcp2515.h"
#include "spi_driver.h"

typedef struct{
	uint16_t id;
	uint8_t data_length;
	int8_t data[8];
}can_message;


uint8_t mcp2515_read(uint8_t address);
void mcp2515_write(uint8_t address, uint8_t data);
void mcp2515_request_to_send(uint8_t command);
void mcp2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data);
void mcp2515_reset();
uint8_t mcp2515_read_status();
uint8_t mcp2515_init();