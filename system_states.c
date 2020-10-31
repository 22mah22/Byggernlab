#include "system_states.h"


nodeStates* init_states(){
    nodeStates* states = malloc(sizeof(nodeStates));
    states->joyvals.x_val = 0;
    states->joyvals.y_val = 0;
    states->slidervals.r_val = 0;
    states->slidervals.l_val = 0;
    states->direction = NEUTRAL;
    states->clockcycles = 0;
    states->joybutton_held = 1;
    return states;
}
//Exports system state variable for use in other modules
extern nodeStates* systemState = init_states();