/*
 * GccApplication1.c
 *
 * Created: 07.10.2020 08:47:43
 * Author : bendil
 */ 


#include "sam.h"
#include "can_controller.h"
#include "uart.h"
#include "printf-stdarg.h"


int main(void)
{
    /* Initialize the SAM system */
    SystemInit();
	WDT->WDT_MR |= 1 << 15;
	configure_uart();
	can_init_def_tx_rx_mb(0x00290561); // 0x00290561 = 0b 00000000001010010000010101100001// 0b000000000000100100010001000100010
	
	printf("hello\n\r");
	//PMC->PMC_MCKR = 0b00000000000000000000000001110010;

	
	PMC->PMC_PCER0 |= PMC_PCER0_PID11; //Peripheral Clock Enable Register 0, Peripheral Clock 14 Enable
	//PIOA->PIO_WPMR &= ~PIO_WPMR_WPEN; //Write Protect Mode Register, Write Protect Enable
	
	PMC->PMC_PCER0 |= PMC_PCER1_PID36; //enable pwm controller
	
	
	PIOA->PIO_PER |= PIO_PER_P19; //PIO Enable Register, PIO Enable
	PIOA->PIO_OER |= PIO_OER_P19; //Output Enable Register, Output Enable
	
	PIOA->PIO_PER |= PIO_PER_P20; //PIO Enable Register, PIO Enable
	PIOA->PIO_OER |= PIO_OER_P20; //Output Enable Register, Output Enable
	
	/*PIOA->PIO_PER |= PIO_PER_P8; //PIO Enable Register, PIO Enable
	PIOA->PIO_OER |= PIO_OER_P8; //Output Enable Register, Output Enable
	PIOA->PIO_PER |= PIO_PER_P9; //PIO Enable Register, PIO Enable
	PIOA->PIO_OER |= PIO_OER_P9; //Output Enable Register, Output Enable*/
	volatile CAN_MESSAGE msg;
    while (1) 
    {
		PIOA->PIO_SODR = PIO_SODR_P19; //Set Output Data Register, Set Output Data
		for(int i = 0; i < 1600000; i++){
		}
		//PIOA->PIO_CODR = PIO_CODR_P19; //Clear Output Data Register, Set Output Data
		PIOA->PIO_SODR = PIO_SODR_P20; //Set Output Data Register, Set Output Data
		for(int i = 0; i < 1600000; i++){
		}
		//PIOA->PIO_CODR = PIO_CODR_P20; //Clear Output Data Register,
		
		
		
		/*if(!can_receive(&msg, 0)){
			for(int i = 0; i < 8; i++){
				for(int j = 0; j < 5*1600000; j++){
					//printf("%d \r", i);
				}
				printf("Data 0: %d %d %d %d |||||||\r", msg.data[i], msg.data_length, msg.id, i);
				
			}
		}
		if(!can_receive(&msg, 1)){
			for(int i = 0; i < 8; i++){
				for(int j = 0; j < 5*1600000; j++){
					//printf("%d \r", i);
				}
				printf("Data 1: %d %d %d %d          \r", msg.data[i], msg.data_length, msg.id, i);
				
			}
		}
		if(!can_receive(&msg, 2)){
			for(int i = 0; i < 8; i++){
				for(int j = 0; j < 5*1600000; j++){
					//printf("%d \r", i);
				}
				printf("Data 2: %d %d %d %d |||||||\r", msg.data[i], msg.data_length, msg.id, i);
				
			}
		}*/
		
		
		
    }
}
