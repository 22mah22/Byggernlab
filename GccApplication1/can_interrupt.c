/*
 * interrupt.c
 *
 * Author: Gustav O. Often and Eivind H. J�lsgard
 *
 * For use in TTK4155 Embedded and Industrial Computer Systems Design
 * NTNU - Norwegian University of Science and Technology
 *
 */ 

#include "can_interrupt.h"

#include <stdio.h>
#include "sam.h"

#include "printf-stdarg.h"

#include "can_controller.h"
#include "timer.h"
#include "motor_controller.h"
#include "pid.h"

uint16_t starttime = 0;
#define DEBUG_INTERRUPT 1

/**
 * \brief CAN0 Interrupt handler for RX, TX and bus error interrupts
 *
 * \param void
 *
 * \retval 
 */
void CAN0_Handler( void )
{
	if(DEBUG_INTERRUPT){}/*printf("CAN0 interrupt\n\r")*/;
	char can_sr = CAN0->CAN_SR; 
	
	//RX interrupt
	if(can_sr & (CAN_SR_MB1 | CAN_SR_MB2) )//Only mailbox 1 and 2 specified for receiving
	{
		CAN_MESSAGE message;
		if(can_sr & CAN_SR_MB1)  //Mailbox 1 event
		{
			can_receive(&message, 1);

		}
		else if(can_sr & CAN_SR_MB2) //Mailbox 2 event
		
		{
			can_receive(&message, 2);
		}
		else
		{
			printf("CAN0 message arrived in non-used mailbox\n\r");
		}
		
		if(message.id < 0x00ff && message.id > 0x000f){
			//interpret_joystick
/*
			printf("Joystick %d \n\r", message.id);
			printf("Joystick %d \n\r", message.data[5]);
*/
			joystick.x_val = (message.data[3] == 0x11) ? message.data[0] : message.data[0]*-1;
			joystick.y_val = (message.data[4] == 0x11) ? message.data[1] : message.data[1]*-1;
			joystick.butt_pressed = message.data[2];
			if(!joystick.butt_pressed){
				set_trigger_time();
			}
			joystick.left_val = message.data[5];
			joystick.right_val = message.data[6];
			joystick.left_button = message.data[7] & 0b00000010;
			joystick.right_button = message.data[7] & 0b00000001;
			
			/*printf("Joystick message/data incoming: \n\r");
			if(DEBUG_INTERRUPT)printf("message id: %d\n\r", message.id);
			if(DEBUG_INTERRUPT)printf("message data length: %d\n\r", message.data_length);
			
			if(DEBUG_INTERRUPT)printf("joystick x-direction: %d ", joystick.x_val);
			if(DEBUG_INTERRUPT)printf("\n\r");
			if(DEBUG_INTERRUPT)printf("joystick y-direction: %d ", joystick.y_val);
			if(DEBUG_INTERRUPT)printf("\n\r");
			if(DEBUG_INTERRUPT)printf("joystick button: %d ", joystick.butt_pressed);
			if(DEBUG_INTERRUPT)printf("\n\r");*/
		}
		else if(message.id == 0x6){
			//Readjust PID controller
			//Bendik, any ideas?
			
			if(message.data[0] == 1){ //easy
				set_difficulty(1);
			}
			else if(message.data[0] == 3){ //hard
				set_difficulty(3);
			}
			else{ //medium
				set_difficulty(2);
			}
			
		}
		else if(message.id == 0x4){//start signal
			starttime = return_milliseconds();
		}
		else if(message.id == 0x3){//stop signal
			send_reaction_time_to_node_1(&message, return_milliseconds()-starttime);
		}
		else if(message.id == 0x2){//game start signal
			start_pid();
			set_starttime();
		}
		else{
			if(DEBUG_INTERRUPT)printf("message id: %d\n\r", message.id);
			if(DEBUG_INTERRUPT)printf("message data length: %d\n\r", message.data_length);
			for (int i = 0; i < message.data_length; i++)
			{
				if(DEBUG_INTERRUPT)printf("%d ", message.data[i]);
			}
			if(DEBUG_INTERRUPT)printf("\n\r");
		}
		
	}
	
	if(can_sr & CAN_SR_MB0)
	{
		/*if(DEBUG_INTERRUPT) printf("CAN0 MB0 ready to send \n\r");*/
		
	//Disable interrupt
		CAN0->CAN_IDR = CAN_IER_MB0;

	}

	if(can_sr & CAN_SR_ERRP)
	{
		if(DEBUG_INTERRUPT)printf("CAN0 ERRP error\n\r");

	}
	if(can_sr & CAN_SR_TOVF)
	{
		if(DEBUG_INTERRUPT)printf("CAN0 timer overflow\n\r");

	}
	
	NVIC_ClearPendingIRQ(ID_CAN0);
	//sei();*/
}
