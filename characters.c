#include "characters.h"

//warning: array must have percieved height and width divisible by 8
void character_printer(int arr[], int width, int height){
    for (int totalChars = 0; totalChars < width*height/8; totalChars++){
            for (int line = 0; line < height/8; line++){
                for (int col = 0; col < width; col++){
                    unsigned char c = 0b00000000;
                    for (int i = 0; i < 8; i++){
                        c |= (arr[i*width + col] << (7-i));
                    }
                    go_to_line(atmelMap, line);
                    go_to_column(atmelMap, col);
                    oled_write_data(c);
                }
            }
    }
}