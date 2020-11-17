/**
 * @file
 * @brief Module for sending CAN messages over CAN bus back to node 1.
 */

#pragma once
#include "can_controller.h"

/**
 * @brief Send amount of time node 2 has been active
 * @param msgToSend Pointer to a CAN_MESSAGE allocated in memory
 */
void send_time_to_node_1(CAN_MESSAGE* msgToSend);

/**
 * @brief Notifies node 1 that a goal has been scored and at which time
 * @param msgToSend Pointer to a CAN_MESSAGE allocated in memory
 */
void send_goal_to_node_1(CAN_MESSAGE* msgToSend);

/**
 * @brief Send motor position to node 1
 * @param msgToSend Pointer to a CAN_MESSAGE allocated in memory
 * @param y_pos Position of the motor
 * @param solenoid 1 if shot, else 0
 */
void send_motor_info_to_node_1(CAN_MESSAGE* msgToSend, uint8_t y_pos, uint8_t solenoide);

/**
 * @brief Send reaction time to node 1
 * @param msgToSend Pointer to a CAN_MESSAGE allocated in memory
 * @param ms Amount of ms used to react
 */
void send_reaction_time_to_node_1(CAN_MESSAGE* msgToSend, uint16_t ms);