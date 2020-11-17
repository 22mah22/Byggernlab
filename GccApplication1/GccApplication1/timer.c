#include "timer.h"
#include <stdint.h>
#include "sam.h"

static uint32_t milliseconds;
static uint16_t starttime = 0;
//SysTick_Type* SysTick = SysTick_BASE;

void SysTick_init(){
    SysTick->CTRL = 0b011;
    SysTick->LOAD = 0x2904;
}

void SysTick_Handler       ( void ){
    milliseconds++;
}

uint32_t return_milliseconds(){
	return milliseconds;
}

uint16_t return_seconds(){
  uint16_t secs = (milliseconds/1000);
  return secs;
}

uint16_t return_starttime(){
	return starttime;
}

void set_starttime(){
	starttime = return_seconds();
}