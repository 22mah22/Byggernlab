#include "feedback.h"
#include "can_controller.h"
#include "timer.h"

void send_time_to_node_1(CAN_MESSAGE* msgToSend){
    //Somewhat random test that fails 75% of the time to avoid spamming the CAN bus
	if(!(return_milliseconds()%4)){ 
        msgToSend->data_length = 2;
        //High ID  since this is a non-urgent message
        msgToSend->id = 0x7;
        msgToSend->data[0] = (uint8_t) (return_seconds() & 0x00FF);
        msgToSend->data[1] = (uint8_t) (return_seconds() & 0xFF00);
		can_send(msgToSend, 0);
	}
}

void send_goals_to_node_1(CAN_MESSAGE* msgToSend, uint8_t goals){
    msgToSend->data_length = 1;
    //Low ID  since this is an urgent message
    msgToSend->id = 0x1;    
    msgToSend->data[0] = goals;
	can_send(msgToSend, 0);
}

void send_motor_info_to_node_1(CAN_MESSAGE* msgToSend, uint8_t y_pos, uint8_t solenoide){
    msgToSend->data_length = 2;
    msgToSend->id = 0x4;    
    msgToSend->data[0] = y_pos;
    msgToSend->data[1] = solenoide;
	can_send(msgToSend, 0);
}