#pragma once
#include <time.h>
#include <stdint.h>
#include "joystick_driver.h"

typedef struct
{
	joyVal joyvals;
    sliderVal slidervals;
    DIRECTION direction;
    clock_t clockcycles;
    uint8_t joybutton_held;
} nodeStates;

nodeStates* init_states();