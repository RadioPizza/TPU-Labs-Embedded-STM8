#include <my_lcd.h>

void LCD_setup(void){
		*(DATA_PORT + 2) = 0xFF;       // DDR = output
    *(CONTROL_PORT + 2) = 0xFF;    // DDR = output
    *CONTROL_PORT &= ~LCD_RES;   // RESET - 0
    delay10Microseconds(1);      // delay 10 us
    *CONTROL_PORT |= LCD_RES;    // RESET - 1
    delay10Microseconds(2);     // delay 20 us
    *CONTROL_PORT &= 0b11100000; // E, A0, R/W - 0
    *CONTROL_PORT |= 0b00001001; // E1, E2 - 1
    *DATA_PORT = LCD_ON;         // turn on LCD command
    LCD_strobe();
}

void LCD_strobe(void){
    *CONTROL_PORT |= LCD_E;
    delay10Microseconds(1);
    *CONTROL_PORT &= ~LCD_E;
}