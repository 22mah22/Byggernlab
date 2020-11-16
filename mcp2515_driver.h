/*
 * can_driver.h
 *
 * Created: 30.09.2020 11:23:38
 *  Author: magneah
 */ 

/**
 * @file
 * @brief Driver module for for the mcp2515 CAN controller specifically
 */

#pragma once

#include <avr/io.h>
#include <stdint.h>
#include "mcp2515.h"
#include "spi_driver.h"

/**
 * @brief Struct for the contents of a CAN message
 */
typedef struct{
	uint16_t id;
	uint8_t data_length;
	int8_t data[8];
}can_message;

/**
 * @brief Sets the mcp2515 in read mode and reads the selected address using spi
 * @param address address to read
 * @return data at address
 */
uint8_t mcp2515_read(uint8_t address);
/**
 * @brief Sets the mcp2515 in write mode and writes the selected address using spi
 * @param address address to write
 * @param data data to write
 */
void mcp2515_write(uint8_t address, uint8_t data);
/**
 * @param command mcp2515 command to be sent according to datasheet
 */
void mcp2515_request_to_send(uint8_t command);
/**
 * @brief Function to modify a bit at an address in the mcp2515
 * @param address address to read
 * @param mask to choose which bit in the byte to change
 * @param data to be written
 */
void mcp2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data);
/**
 * @brief Resets the mcp2515
 */
void mcp2515_reset();
/**
 * @brief Function to get the status of the mcp2515
 * @return MCP2515 status
 */
uint8_t mcp2515_read_status();
/**
 * @brief Initializes spi and resets the mcp2515
 */
void mcp2515_init();