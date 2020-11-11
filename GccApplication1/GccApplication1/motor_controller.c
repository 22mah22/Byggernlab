/*
 * joystick.c
 *
 * Created: 14.10.2020 14:49:57
 *  Author: magneah
 */ 
 #include "motor_controller.h"
 #include "timer_driver.h"
 #include "printf-stdarg.h"
 #include "uart.h"
 #include "sam.h"
 #include "timer.h"
 
 uint8_t previous = 1;
 uint8_t y_value_pi = 0;
 uint8_t solenoide_status = 0;

 uint8_t get_solenoid_status(){
	 return solenoide_status;
 }

void reset_solenoid_status(){
	solenoide_status = 0;
 }
 
 void move_solenoid(){
	 //printf("joystick.x_val : %d \n\r", joystick.x_val);
	 
	  
	 
	 if(joystick.x_val < 0){
		 uint8_t val = 50-abs(joystick.x_val)*0.5;
		 timer_change_duty(val);
	 }
	 if(joystick.x_val >= 0){
		 uint8_t val2 = 50+joystick.x_val*0.5;
		 timer_change_duty(val2);
	 }
 }

 void check_solenoid_shot(){
	static uint32_t last_time_pressed = 0;
	if(button_check(joystick.butt_pressed)){
		last_time_pressed = return_milliseconds();
		PIOC->PIO_CODR |= PIO_CODR_P13;
		solenoide_status = 1;
	}
	else{
		if(return_milliseconds() > (last_time_pressed + 10)){
			PIOC->PIO_SODR |= PIO_SODR_P13;
			solenoide_status = 0;
		}
	}
 }
 
 void change_motor_speed(){
	 //printf("joystick.y_val : %d \n\r", joystick.y_val);
	 
	 if(joystick.y_val < - 10){
		 PIOD->PIO_CODR = PIO_CODR_P10; //set direction left
		 uint16_t val = 0x01ff+abs(joystick.y_val)*5;
		 DACC->DACC_CDR = val;
	 }
	 if(joystick.y_val >= 10){
		 PIOD->PIO_SODR = PIO_SODR_P10; //set direction right
		 uint16_t val2 = 0x01ff+abs(joystick.y_val)*5;
		 DACC->DACC_CDR = val2;
	 }
	 
	 if(joystick.y_val > -10 && joystick.y_val < 10){
		 DACC->DACC_CDR = 0;
	 }
 }

void change_motor_speed_using_paadrag(int paadrag){
	//printf("joystick.y_val : %d \n\r", joystick.y_val);
	
	if(paadrag < 0){
		PIOD->PIO_CODR = PIO_CODR_P10; //set direction left
		uint16_t val = abs(paadrag);
		DACC->DACC_CDR = val;
	}else{
		PIOD->PIO_SODR = PIO_SODR_P10; //set direction right
		uint16_t val2 = abs(paadrag);
		DACC->DACC_CDR = val2;
	}
}
 

void motor_box_init(){
	PIOD->PIO_PER |= PIO_PER_P10; //PIO Enable Register, PIO Enable //pin32 DIR PD10
	PIOD->PIO_OER |= PIO_OER_P10; //Output Enable Register, Output Enable //pin32 DIR PD10
	PIOD->PIO_PER |= PIO_PER_P9; //PIO Enable Register, PIO Enable //pin30 EN PD9
	PIOD->PIO_OER |= PIO_OER_P9; //Output Enable Register, Output Enable //pin30 EN PD9
	
	PIOD->PIO_SODR = PIO_SODR_P9; //Set Output Data Register, Set Output Data
	PIOD->PIO_CODR = PIO_CODR_P10; //Clear Output Data Register, Set Output Data
	
	PMC->PMC_PCER0 = PMC_PCER0_PID13;

	
	//allow counter to start
	PIOD->PIO_SODR |= PIO_SODR_P1; //!RST high
	
	//enable pins for reading encoder
	PIOC->PIO_PER |= PIO_PER_P8; //DO7
	PIOC->PIO_PER |= PIO_PER_P7; //DO6
	PIOC->PIO_PER |= PIO_PER_P6; //DO5
	PIOC->PIO_PER |= PIO_PER_P5; //DO4
	PIOC->PIO_PER |= PIO_PER_P4; //DO3
	PIOC->PIO_PER |= PIO_PER_P3; //DO2
	PIOC->PIO_PER |= PIO_PER_P2; //DO1
	PIOC->PIO_PER |= PIO_PER_P1; //DO0
}


uint8_t encoder_read(){
	// PIO (Output) Enable Register, PIO Enable
	PIOD->PIO_PER |= PIO_PER_P2; // Pin 27 sel PD2 SEL
	PIOD->PIO_OER |= PIO_OER_P2; // 
	PIOD->PIO_PER |= PIO_PER_P1; // Pin 26 not_rst PD1 !RST
	PIOD->PIO_OER |= PIO_OER_P1; // 
	PIOD->PIO_PER |= PIO_PER_P0; // Pin 25 not_oe PD0 !OE
	PIOD->PIO_OER |= PIO_OER_P0; // 
	
	PIOD->PIO_CODR |= PIO_CODR_P0; //!OE low
	PIOD->PIO_CODR |= PIO_CODR_P2; //SEL low
	
	//10 microsec
	for(int i = 0; i < 3200; i++){
	}
	
	uint8_t MSB = (PIOC->PIO_PDSR >> 1);
	//printf("PIO_PDSR: -----%x \n\r", PIOC->PIO_PDSR);
	PIOD->PIO_SODR |= PIO_SODR_P2; //SEL high
	
	//10 microsec
	for(int i = 0; i < 3200; i++){
	}
	uint8_t LSB = PIOC->PIO_PDSR >> 1;
	
	PIOD->PIO_CODR |= PIO_CODR_P1; //!RST low
	PIOD->PIO_SODR |= PIO_SODR_P1; //!RST high
	PIOD->PIO_SODR |= PIO_SODR_P0; //!OE high
	
	uint16_t encoder_data = (LSB | (MSB << 8));
	int encoder_data_int = LSB | (MSB << 8);
	y_value_pi = (8888-encoder_data_int)/88; //scaled so that value is 0-100;
 	printf("Encoder             data: %x \n\r", y_value_pi);
// 	
// 	if(encoder_data &= (1 << 15)){
// 		//encoder_data = (~encoder_data + 1);
// 		printf("Data negative: -%d \n\r", encoder_data);
// 	}
// 	else{
// 		printf("Data positive: %d \n\r", encoder_data);
// 	}
}

uint8_t button_check(uint8_t current){
	if(current == 0 && previous == 1){
		previous = 0;
		//printf("%s", "B");
		return 1;
		}else if(current != 0){
		previous = 1;
		//printf("%s", "C");
	}
	return 0;
}