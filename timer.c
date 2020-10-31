#include "timer.h"
#include "system_states.h"
#include <stdint.h>
#include <time.h>

void timer_set(nodeStates* states){
    states->clockcycles = clock();
}

int check_ms_passed(nodeStates* states, uint8_t milliseconds){
    uint8_t current_clockcycles = clock();
    if((states->clockcycles + milliseconds*CLOCKS_PER_SEC/1000) < current_clockcycles){
        return 1;
    }
    return 0;
}