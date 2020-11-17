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

void spi_write(char data);


uint8_t spi_read();


void spi_init();