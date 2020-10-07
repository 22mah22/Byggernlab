/*
 * can_driver.h
 *
 * Created: 30.09.2020 16:54:28
 *  Author: magneah
 */ 

#pragma once
#include <stdio.h>
#include "mcp2515_driver.h"


uint8_t can_init();

void send_can_msg(can_message *msg);

can_message* receive_can_msg(uint8_t buffer_number);

uint8_t can_check_complete(uint8_t buffer_number);
