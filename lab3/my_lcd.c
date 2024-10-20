#include <my_lcd.h>

void LCD_setup(void){
    *(DATA_PORT + 2) = 0xFF;    // DDR = output
    *(CONTROL_PORT + 2) = 0xFF; // DDR = output
    *CONTROL_PORT &= ~LCD_RES;  // RESET - 0
    delay10Microseconds(1);     // delay 10 us
    *CONTROL_PORT |= LCD_RES;   // RESET - 1
    delay10Microseconds(2);     // delay 20 us
    *CONTROL_PORT &= 0b11100000;    // E, A0, R/W - 0
    *CONTROL_PORT |= 0b00001001;    // E1, E2 - 1
    *DATA_PORT = LCD_ON;        // turn on LCD command
    LCD_strobe();
}

void LCD_strobe(void){
    *CONTROL_PORT |= LCD_E;
    delay10Microseconds(1);
    *CONTROL_PORT &= ~LCD_E;
    delay10Microseconds(1);
}

void LCD_setPage(int chip, int page){
    unsigned char command;
    // Validate page number
    page &= 0x07;

    // Construct command
    command = 0b10111000 | page;

    // Set control lines for command write
    *CONTROL_PORT &= ~LCD_A0;
    *CONTROL_PORT &= ~LCD_RW;

    // Select the appropriate chip
    if (chip == 1) {
        *CONTROL_PORT |= LCD_E1;
        *CONTROL_PORT &= ~LCD_E2;
    } else if (chip == 2) {
        *CONTROL_PORT &= ~LCD_E1;
        *CONTROL_PORT |= LCD_E2;
    }

    *DATA_PORT = command;
    LCD_strobe();
    *CONTROL_PORT &= ~(LCD_E1 | LCD_E2);
}
