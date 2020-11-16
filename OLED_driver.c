#include "OLED_driver.h"
#include "fonts.h"
#include "joystick_driver.h"

uint8_t oled_array[8][100];


void oled_write_command(char c)
{
	volatile char *ext_ram = (char *) 0x1000;
	ext_ram[0] = c;
}
void oled_write_data(char c)
{
	volatile char *ext_ram = (char *) 0x1200;
	ext_ram[0] = c;
}


void oled_init(){
	oled_write_command(0xae); //display off
	oled_write_command(0xa1); //segment remap
	oled_write_command(0xda); //common pads hardware: alternative
	oled_write_command(0x12);
	oled_write_command(0xc8); //common output scan direction:com63-com0
	oled_write_command(0xa8); //multiplex ration mode:63
	oled_write_command(0x3f);
	oled_write_command(0xd5); //display divide ratio/osc. freq. mode
	oled_write_command(0x80);
	oled_write_command(0x81); //contrast control
	oled_write_command(0x50);
	oled_write_command(0xd9); //set pre-charge period
	oled_write_command(0x21);
	oled_write_command(0x20); //set memory addressing mode
	oled_write_command(0x02);                                    //page addressing mode
	oled_write_command(0xdb); //VCOM deselect level mode
	oled_write_command(0x30);
	oled_write_command(0xad); //master configuration
	oled_write_command(0x00);
	oled_write_command(0xa4); //out follows RAM content
	oled_write_command(0xa6); //set normal display
	oled_write_command(0xaf); //display on
}

void go_to_line(uint8_t line){
	oled_write_command(0xB0 + line%8);
}

void go_to_column(uint8_t column){
	
	oled_write_command(0x00 + (column%16));
	oled_write_command(0x10 + (column/16));
}

void oled_start_write_at(amap* atmelMap, uint8_t page, uint8_t lowerCol, uint8_t upperCol){
	atmelMap->OLED_CMD[1] = 0xB1;
	atmelMap->OLED_CMD[1] = 0x00;
	atmelMap->OLED_CMD[1] = 0x10;
}
void oled_write(amap* atmelMap){
	atmelMap->OLED_DATA[1] = 0x0F;
}

void clear_oled(){
	for(int i = 0; i < 8 ; i++){
		go_to_line(i);
		
		go_to_column(0);
		for(int j = 0; j < 128; j++){
			
			oled_write_data(0x00);
		}
	}
}

void clear_oled_new(){
	for(int i = 0; i < 8 ; i++){
		go_to_line(i);
		
		go_to_column(0);
		for(int j = 0; j < 128; j++){
			
			oled_write_data(0x00);
		}
	}
}

void oled_write_string(uint8_t startline, char* c, uint8_t n){
	go_to_line(startline);
	
	for (int i=0; i < strlen(c); i++) {
		if(i%((int)128/n) == 0){
			go_to_line(startline+i/((int)128/n));
		}
		oled_write_char_using_font(c[i],n);
		
	}
	go_to_column(0);
}

void oled_write_string_inverted(uint8_t startline, char* c, uint8_t n){
	go_to_line(startline);
	
	for (int i=0; i < strlen(c); i++) {
		if(i%((int)128/n) == 0){
			go_to_line(startline+i/((int)128/n));
		}
		oled_write_inverted_char_using_font(c[i],n);
		
	}
	go_to_column(0);
}

void oled_write_char_using_font(char c, uint8_t n){
	uint8_t character = c-32;
	
	if(n==8){
		for (int i=0; i < n; i++) {
			oled_write_data(pgm_read_word(&font8[character][i]));
		}
	}else if(n == 5){
		for (int i=0; i < n; i++) {
			oled_write_data(pgm_read_word(&font5[character][i]));
		}
	}else if(n == 4){
		for (int i=0; i < n; i++) {
			oled_write_data(pgm_read_word(&font4[character][i]));
		}
	}
	
}

void oled_write_inverted_char_using_font(char c, uint8_t n){
	uint8_t character = c-32;
	
	if(n==8){
		for (int i=0; i < n; i++) {
			oled_write_data(~pgm_read_word(&font8[character][i]));
		}
		}else if(n == 5){
		for (int i=0; i < n; i++) {
			oled_write_data(~pgm_read_word(&font5[character][i]));
		}
		}else if(n == 4){
		for (int i=0; i < n; i++) {
			oled_write_data(~pgm_read_word(&font4[character][i]));
		}
	}
	
}

void oled_write_char8(char c){
	uint8_t character = c-32;
	
	for (int i=0; i < 8; i++) {
		oled_write_data(pgm_read_byte(&(font8[character][i])));
	}
	
}

//warning: array must have percieved height and width divisible by 8
void character_printer(uint8_t arr[], int width, int height, uint8_t x_offset, uint8_t y_offset, uint8_t inverted){
		for (int line = 0; line < height/8; line++){
			int offset = line*width*8;
			for (int col = 0; col < width; col++){
				unsigned char c = 0b00000000;
				for (int i = 0; i < 8; i++){
					c |= (pgm_read_byte(&(arr[i*width + col + offset])) << i);
				}
				go_to_line(line + y_offset);
				go_to_column(col + x_offset);
				if(inverted){
					oled_write_data(~c);
				}
				else{
					oled_write_data(c);
				}
			}
		}
}



void oled_drawing(uint8_t l_slider, uint8_t r_slider, uint8_t write){
	char byteToWrite;
	if(r_slider > 63){
		r_slider = 63;
	}
	go_to_line(7-(r_slider/8));
	go_to_column(l_slider);
	
	byteToWrite = oled_array[7-(r_slider/8)][l_slider] | (1<<(7-(r_slider%8)));
	oled_array[7-(r_slider/8)][l_slider] = byteToWrite;
	if(!write){
		oled_write_data(0b00000000);
		oled_array[7-(r_slider/8)][l_slider] = 0b00000000;
	}else{
		oled_write_data(byteToWrite);
	}
	
}

void oled_drawing_sram(char * sram, uint8_t l_slider, uint8_t r_slider, uint8_t write){
	char byteToWrite;
	if(r_slider > 63){
		r_slider = 63;
	}
	go_to_line(7-(r_slider/8));
	go_to_column(l_slider);
	
	byteToWrite = sram[1000+(7-(r_slider/8))*l_slider+l_slider] | (1<<(7-(r_slider%8)));
	sram[1000+(7-(r_slider/8))*l_slider+l_slider] = byteToWrite;
	if(!write){
		oled_write_data(0b00000000);
		sram[1000+(7-(r_slider/8))*l_slider+l_slider] = 0b00000000;
		}else{
		oled_write_data(byteToWrite);
	}
	
}

void draw_sram(){
	volatile char * sram = (char *) 0x1800;
	uint8_t toggle = 0b00000000;
	while(!PIND & (1<< PIND4)){
		if(PIND & (1<< PIND5)){
			clear_oled();
			reset_oled_array_sram(sram);
		}
		if(button_check(PINB & (1<< PINB1)))
		{
			toggle = ~toggle;
		}
		printf("Program running %d \r\n", 2);
		update_adc_values();
		oled_drawing_sram(sram, get_slidervals().l_val, get_slidervals().r_val, toggle);
	}
	return;
}
void draw(){
	uint8_t toggle = 0b00000000;
	while(!PIND & (1<< PIND4)){
		if(PIND & (1<< PIND5)){
			clear_oled();
			reset_oled_array();
		}
		if(button_check(PINB & (1<< PINB1)))
		{
			toggle = ~toggle;
		}
		printf("Program running %d \r\n", 2);
		update_adc_values();
		oled_drawing(get_slidervals().l_val, get_slidervals().r_val, toggle);
	}
	return;
}

void reset_oled_array(){
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 100; j++){
			oled_array[i][j] = 0b00000000;
		}
	}
}
void reset_oled_array_sram(char * sram){
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 100; j++){
			sram[1000+i*j+j] = 0b00000000;
		}
	}
}