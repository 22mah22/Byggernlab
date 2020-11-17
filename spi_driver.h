/**
 * @file
 * @brief Driver module for SPI communications.
 */

/*
 * spi_driver.h
 *
 * Created: 30.09.2020 11:22:29
 *  Author: magneah
 */ 


#pragma once

#include <avr/io.h>
#include <stdint.h>
#include "mcp2515.h"

/**
 * @brief Function to initialize SPI on the AtMega
 */

void spi_init();

/**
 * @brief Function to write a byte of data using spi
 * @param data byte to write
 */
void spi_write(char data);

/**
 * @brief Function to read data sent using spi
 */
uint8_t spi_read();

