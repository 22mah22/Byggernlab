/**
 * @file
 * @brief Module for handling the pid regulator.
 */

#pragma once
#include <stdint.h>

/**
 * @brief Function called x amount per second based on timer initialized in timer_driver, drives the pid regulator
 */
void TC1_Handler       ( void );

/**
 * @brief Return the current difficulty setting
 * @return Returns the current difficulty setting
 */
uint8_t get_difficulty();

/**
 * @brief Set the difficulty
 * @param difficulty_to_set Chosen difficulty to play with
 */
void set_difficulty(uint8_t difficulty_to_set);


void stop_pid();
void start_pid();