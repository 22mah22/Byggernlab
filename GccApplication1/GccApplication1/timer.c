#include "timer.h"
#include <stdint.h>
#include "sam.h"

static uint32_t milliseconds;
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

uint8_t return_seconds(){
  uint32_t big = (milliseconds/1000);
  uint8_t small = 0;
  if(big < 255){
    small = big;
  }
  return small;
}
/*uint32_t time_running_ms(){*/
  //  return (seconds*1000)+(SysTick->VAL)/(0xa037a0/1000);
//}