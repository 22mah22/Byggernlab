#include <time.h>
#include "pause.h"


void pause_150ms_wait (){
	clock_t x_countTime, x_startTime;
	float count_down_time = 0.15;
	float time_left = 0;

	x_startTime = clock();
	time_left = count_down_time;

	while(time_left > 0){
		x_countTime = clock();
		time_left = count_down_time - ((x_countTime - x_startTime)/(CLOCKS_PER_SEC));
		
	}
}

