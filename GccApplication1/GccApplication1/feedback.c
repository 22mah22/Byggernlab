#include "feedback.h"
#include "can_controller.h"
#include "timer.h"

void send_time_to_node_1(CAN_MESSAGE* msgToSend){
    //Somewhat random test that fails 75% of the time to avoid spamming the CAN bus
	if(!(return_milliseconds()%4)){ 
        msgToSend->data_length = 2;
        //High ID  since this is a non-urgent message
		uint16_t temp = 0x8;
        msgToSend->id = temp;
        msgToSend->data[0] = (uint8_t) (return_seconds() & 0x00FF);
        msgToSend->data[1] = (uint8_t) (return_seconds() & 0xFF00);
		can_send(msgToSend, 0);
		printf("message id: %x \r\n", msgToSend->id);
		printf("message length: %x \r\n", msgToSend->data_length);
		printf("message data: %d \r\n", msgToSend->data[0]);
	}
}

void send_goal_to_node_1(CAN_MESSAGE* msgToSend){
    msgToSend->data_length = 2;
    //Low ID  since this is an urgent message
    msgToSend->id = 0x1;    
    msgToSend->data[0] = (uint8_t) (return_seconds() & 0x00FF);
    msgToSend->data[1] = (uint8_t) ((return_seconds() & 0xFF00) >> 8);
	can_send(msgToSend, 0);
}

void send_motor_info_to_node_1(CAN_MESSAGE* msgToSend, uint8_t y_pos, uint8_t solenoide){
    msgToSend->data_length = 2;
	uint16_t temp = 0x4;
    msgToSend->id = temp;
    msgToSend->data[0] = y_pos;
    msgToSend->data[1] = solenoide;
	can_send(msgToSend, 0);
	printf("message length: %x \r\n", msgToSend->data_length);
}

void send_reaction_time_to_node_1(CAN_MESSAGE* msgToSend, uint16_t ms){
    msgToSend->data_length = 2;
    //Low ID  since this is an urgent message
    msgToSend->id = 0x2;    
    msgToSend->data[0] = (uint8_t) (ms & 0x00FF);
    msgToSend->data[1] = (uint8_t) ((ms & 0xFF00) >> 8);
	can_send(msgToSend, 0);
}