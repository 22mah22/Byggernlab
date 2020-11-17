/**
 * @file
 * @brief Module for handling all things related to controlling the motor.
 */

/*
 * joystick.h
 *
 * Created: 14.10.2020 14:47:53
 *  Author: magneah
 */ 

#pragma once

#include <stdint.h>



/**
 * @brief Send amount of time node 2 has been active
 * @param msgToSend Pointer to a CAN_MESSAGE allocated in memory
 */
typedef struct {
	int8_t x_val;
	int8_t y_val;
	int8_t butt_pressed;
	int8_t left_val;
	int8_t right_val;
	int8_t left_button;
	int8_t right_button;
} joyVal;

joyVal joystick;

/**
 * @brief Set pi value (motor position) to be used in pid regulator
 * @param val Value to be set
 */
void set_pi_value(uint8_t val);

/**
 * @brief Return the current pi value (motor position)
 * @return returns the current pi value
 */
uint8_t get_pi_value();

/**
 * @brief Return whether solenoid has shot or not
 * @return shot(1) else 0
 */
uint8_t get_solenoid_status();

/**
 * @brief Reset solenoid status
 */
void reset_solenoid_status();

/**
 * @brief Move servo based on joystick values
 */
void move_servo();

/**
 * @brief Check if the solenoid has shot
 */
void check_solenoid_shot();

/**
 * @brief Change motor speed based on joystick position
 */
void change_motor_speed();

/**
 * @brief Change motor speed using the paadrag from the pid regulator
 * @param paadrag Value to be sent to motor box, deciding the speed of the motor
 */
void change_motor_speed_using_paadrag(int paadrag);

/**
 * @brief Initialize the motor box
 */
void motor_box_init();

/**
 * @brief Read the encoder values to find motor position
 */
void encoder_read();

/**
 * @brief Check if the button is pressed
 * @param current Current value of the button
 * @return 1 if pressed, else 0
 */
uint8_t button_check(uint8_t current);