#pragma once

#include "system_states.h"

void timer_set(nodeStates* states);

int check_ms_passed(nodeStates* states, uint8_t milliseconds);