/**
 * @file
 * @brief Module for handling what happens to all CAN messages from node 1.
 */

/*
 * can_interrupt.h
 *
 * Author: Gustav O. Often and Eivind H. Jølsgard
 *
 * For use in TTK4155 Embedded and Industrial Computer Systems Design
 * NTNU - Norwegian University of Science and Technology
 *
 */ 


#ifndef CAN_INTERRUPT_H_
#define CAN_INTERRUPT_H_


/**
 * @brief Decide what happens to messages of different IDs
 */
void CAN0_Handler       ( void );






#endif /* CAN_INTERRUPT_H_ */