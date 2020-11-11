#pragma once
#include "can_controller.h"

void send_time_to_node_1(CAN_MESSAGE* msgToSend);

void send_goals_to_node_1(CAN_MESSAGE* msgToSend, uint8_t goals);

void send_motor_info_to_node_1(CAN_MESSAGE* msgToSend, uint8_t y_pos, uint8_t solenoide);