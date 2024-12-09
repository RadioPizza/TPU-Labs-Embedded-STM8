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

void LCD_selectChip(int chip){
    if (chip == 1) {
        *CONTROL_PORT |= LCD_E1;  // E1 = 1
        *CONTROL_PORT &= ~LCD_E2; // E2 = 0
    } else if (chip == 2) {
        *CONTROL_PORT &= ~LCD_E1; // E1 = 0
        *CONTROL_PORT |= LCD_E2;  // E2 = 1
    } else if (chip > 2) {
        *CONTROL_PORT |= LCD_E1;  // E1 = 1
        *CONTROL_PORT |= LCD_E2;  // E2 = 1
    }
}

void LCD_setPage(int page){
    unsigned char command;
    // Validate page number
    page &= 0x07; // Mask to 3 bits (0-7)
    // Construct command
    command = 0b10111000 | page;
    // Set control lines for command write
    *CONTROL_PORT &= ~LCD_A0;  // A0 = 0 for command
    *CONTROL_PORT &= ~LCD_RW;  // R/W = 0 for write
    // Write command
    *DATA_PORT = command;
    LCD_strobe();
}

void LCD_setAddress(int address){
    unsigned char command;
    address &= 0x3F;  // Mask to 6 bits
    command = 0b01000000 | address;
    *CONTROL_PORT &= ~LCD_A0;
    *CONTROL_PORT &= ~LCD_RW;
    *DATA_PORT = command;
    LCD_strobe();
}

void LCD_writeData(unsigned char data){
    // Set control lines for data write
    *CONTROL_PORT |= LCD_A0;   // A0 = 1 for data
    *CONTROL_PORT &= ~LCD_RW;  // R/W = 0 for write
    // Write data to data port
    *DATA_PORT = data;
    // Strobe the LCD
    LCD_strobe();
}

void LCD_drawLetterM(){
    unsigned char letterM_data[5] = {0x7F, 0x02, 0x04, 0x02, 0x7F};
    int i;
    LCD_selectChip(1);
    LCD_setPage(2);
    LCD_setAddress(4);
    for(i = 0; i < 5; i++){
        // Write each column of the letter
        LCD_writeData(letterM_data[i]);
    }
}
/*
void LCD_drawChar(unsigned char page, unsigned char address, unsigned char *bitmap, unsigned char width){
    int i;
    if(address < 64){
        LCD_selectChip(1);
    } else {
        LCD_selectChip(2);
        address -= 64;
    }
    LCD_setPage(page);
    LCD_setAddress(address);
    for(i = 0; i < width; i++){
        LCD_writeData(bitmap[i]);
    }
}

void LCD_drawRectangle(){
    int i;
    LCD_selectChip(2);
    LCD_setPage(4);
    LCD_setAddress(25);
    LCD_writeData(0x7E);
    for(i = 0; i < 18; i++){
        LCD_writeData(0x42);
    }
    LCD_writeData(0x7E);
}

void LCD_drawLetterA(){
    unsigned char letterM_data[5] = {0xF8, 0x16, 0x11, 0x16, 0xF8};
    int i;
    LCD_selectChip(1);
    LCD_setPage(2);
    LCD_setAddress(4);
    for(i = 0; i < 5; i++){
        // Write each column of the letter
        LCD_writeData(letterM_data[i]);
    }
}

void LCD_task20{
    unsigned chat picture_data[7] = {0x, 0x, 0x, 0x, 0x, 0x, 0x, 0x};
    LCD_selectChip(2);
    LCD_setPage(8);
    LCD_setAddress(0);
    for(i = 0; i < 7, i++){
        LCD_writeData(picture_data[i]);
    }


}
*/