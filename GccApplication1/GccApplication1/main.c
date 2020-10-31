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
#include "timer_driver.h"
#include "adc_controller.h"
#include "adc_interrupt.h"
#include "dac_controller.h"
#include "motor_controller.h"


int main(void)
{
    /* Initialize the SAM system */
    SystemInit();
	WDT->WDT_MR |= 1 << 15;
	configure_uart();
	can_init_def_tx_rx_mb(0x00290561); // 0x00290561 = 0b 00000000001010010000010101100001// 0b000000000000100100010001000100010
	
	printf("hello\n\r");
	
	
	//PMC->PMC_MCKR = 0b00000000000000000000000001110010;

	/*
	PMC->PMC_PCER0 |= PMC_PCER0_PID11; //Peripheral Clock Enable Register 0, Peripheral Clock 14 Enable
	//PIOA->PIO_WPMR &= ~PIO_WPMR_WPEN; //Write Protect Mode Register, Write Protect Enable
	
	PMC->PMC_PCER0 |= PMC_PCER1_PID36; //enable pwm controller
	
	PWM->PWM_CLK |= 0x00010001; // select mck with noe dividers
	PWM->PWM_ENA |= PWM_ENA_CHID0;
	PWM->PWM_ENA |= PWM_ENA_CHID2;
	PWM->PWM_CH_NUM[2].PWM_CPRD |= 0x00000400;
	PWM->PWM_CH_NUM[0].PWM_CPRD |= 0x00000200;
	PWM->PWM_CH_NUM[2].PWM_CDTY |= 0x00000200;
	PWM->PWM_CH_NUM[0].PWM_CDTY |= 0x00000100;
	PWM->PWM_CH_NUM[0].PWM_CMR |= PWM_CMR_CPRE_MCK; //choose clock a?
	PWM->PWM_CH_NUM[2].PWM_CMR |= PWM_CMR_CPRE_MCK; //choose clock a?
	PWM->PWM_CH_NUM[0].PWM_CMR &= ~PWM_CMR_CPOL;
	PWM->PWM_CH_NUM[2].PWM_CMR &= ~PWM_CMR_CPOL;
	
	PIOA->PIO_ABSR |= PIO_ABSR_P5; //PIO set peripheral b on pin 5*/
	
	
	timer_init();
	timer_change_duty(100);
	//init_interrupt_PI();
	init_ch1_PI();
	
	adc_init();
	dac_init();
	
	
	motor_box_init();
	
	
	
	
	
	
	
	
	//enable and set high, pin to controll servo shoot, pin50 on shield
	PIOC->PIO_PER |= PIO_PER_P13; 
	PIOC->PIO_OER |= PIO_OER_P13; 
	PIOC->PIO_SODR |= PIO_SODR_P13;
	
	
	
	
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
		PIOA->PIO_CODR = PIO_CODR_P19; //Clear Output Data Register, Set Output Data
		PIOA->PIO_SODR = PIO_SODR_P20; //Set Output Data Register, Set Output Data
		for(int i = 0; i < 1600000; i++){
		}
		//printf("%x ", tc->TC_CHANNEL[0].TC_SR);
		PIOA->PIO_CODR |= PIO_CODR_P20; //Clear Output Data Register,
		
		
		
		move_solenoid();
		change_motor_speed();
		encoder_read();
		
		if(button_check(joystick.butt_pressed)){
			PIOC->PIO_CODR |= PIO_CODR_P13;
			for(int i = 0; i < 1600000; i++){
			}
			PIOC->PIO_SODR |= PIO_SODR_P13;
		}
		
		
		//printf("%d",ADC->ADC_ISR);
// 		printf("adc_input : %x   \n\r", ADC->ADC_CDR[1]);
 		printf("goals : %d   \n\r", TOTAL_GOALS);
		 printf("left_slider : %d   \n\r", joystick.left_val);
		//printf("adc_input : %d ::::", ADC->ADC_LCDR & 0x00000CE4);
		
		
		if(TO_INCREMENT){
			printf("to_increment");
			goal_counter();
			for(int j = 0; j < 5*1600000; j++){
				
			}
		}
		
		/*//printf("Gååååållll %d \n\r", ADC->ADC_ISR);
		
		if(ADC->ADC_ISR & (0x1 << 26)){
			printf("Gååååållll %x \r", ADC->ADC_ISR);
			
		}*/
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
