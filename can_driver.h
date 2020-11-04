/**
 * @file
 * @brief Driver module for handling data transmission over the CAN-bus
 */


/*
 * can_driver.h
 *
 * Created: 30.09.2020 16:54:28
 *  Author: magneah
 */ 

#pragma once
#include <stdio.h>
#include "mcp2515_driver.h"

/**
 * @brief Initializes the CAN bus on the node by initializing the mcp2515 microcontroller
 * and writing to its CAN control-registers.
 */
void can_init();

/**
 * @brief Function to send a predetermined message to a reciever over the CAN bus
 * @param msg pointer to a memory location where a message is stored. Implemented as a pointer
 * to make sure the variable will not exit scope.
 */
void send_can_msg(can_message *msg);

/**
 * @brief Function to poll CAN bus for a message to be recieved.
 * @param buffer_number buffer to check for recieved message
 * @return returns a pointer to a recieved message now stored in memory
 */
can_message* receive_can_msg(uint8_t buffer_number);

/**
 * @brief Reads the "has been transmitted" - flag from the mcp2515 on the selected buffer
 * @param buffer_number which buffer to check transmitted-flag on.
 * @return return 1 and resets interuptflag if transmitted, 0 if not
 */
uint8_t can_check_complete(uint8_t buffer_number);
