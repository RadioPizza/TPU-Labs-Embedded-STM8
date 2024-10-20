// my_lcd.h v1
#ifndef MY_LCD_H
#define MY_LCD_H
#include <my_gpio.h>
#include <string.h>

// LCD
#define DATA_PORT &PB_ODR
#define CONTROL_PORT &PF_ODR

// LCD pins
#define LCD_D0  0b00000001  // 0
#define LCD_D1  0b00000010  // 1
#define LCD_D2  0b00000100  // 2
#define LCD_D3  0b00001000  // 3
#define LCD_D4  0b00010000  // 4
#define LCD_D5  0b00100000  // 5
#define LCD_D6  0b01000000  // 6
#define LCD_D7  0b10000000  // 7

#define LCD_E1  0b00000001  // 0
#define LCD_E2  0b00001000  // 3
#define LCD_RES 0b00010000  // 4
#define LCD_RW  0b00100000  // 5
#define LCD_A0  0b01000000  // 6
#define LCD_E   0b10000000  // 7

#define LCD_ON  0b00111111 // turn on lcd
#define LCD_OFF 0b00111110 // turn off lcd

void LCD_setup(void);
void LCD_strobe(void);

#endif // MY_LCD_H
