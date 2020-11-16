/**
 * @file
 * @brief Driver module for handling data joystick and slider inputs
 */


#pragma once
#include <stdint.h>
#include "DEFINITIONS.h"
#include "can_driver.h"
/**
 * @brief Struct for joystick directions
 */
typedef enum{
		LEFT,
		RIGHT,
		UP,
		DOWN,
		NEUTRAL,
		WAITING
} DIRECTION;

/**
 * @brief Struct to store joystick values in both directions
 */
typedef struct {
	int8_t x_val;
	int8_t y_val;
} joyVal;

/**
 * @brief Struct to store left and right slider values
 */
typedef struct {
	uint8_t l_val;
	uint8_t r_val;
} sliderVal;

/**
 * @brief Function to return joystick values for other modules
 * @return joystick variable
 */
joyVal get_joyvals();

/**
 * @brief Function to return slider values for other modules
 * @return slider variable
 */
sliderVal get_slidervals();

/**
 * @brief Function that sets the x and y offsets to the joysticks current value
 * This needs the joystick to be in a neutral position in order to work
 */
void calc_offset();
/**
 * @brief Function to check if one of the three buttons is being pressed.
 * Uses a local previous variable to make sure an input is registered as just one input
 * @param current can be any button value represented by a boolean
 * @return 1 if button is being pressed, 0 otherwise
 */
uint8_t button_check(uint8_t current);

/**
 * @brief Updates all joystick and slider values from the adc
 * Sets values to 0-100 or (-100)-100 for the joystick.
 */
void update_adc_values();


/**
 * @brief Update a joysticks direction based on its x and y data
 * @param dir previous direction of the joystick
 * uses local joystick variable
 * @return the joysticks DIRECTION
 */
DIRECTION joystick_direction(DIRECTION dir);
