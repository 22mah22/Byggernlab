#include "timer.h"
#include <stdint.h>

static uint16_t seconds;

void timer_init(){
    SysTick->CTRL = 0b111;
    SysTick->LOAD = 84000;
}

void SysTick_Handler       ( void ){
    seconds++;
}

uint16_t time_running_ms(){
    return (seconds*1000)+(SysTick->VAL)/84;
}