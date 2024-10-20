#include <my_gpio.h>
#include <my_lcd.h>

void main(){
	// Bitmap data for letter "М"
	unsigned char letterM_data[5] = {0x7F, 0x02, 0x04, 0x02, 0x7F};

	LCD_setup();
	// LCD_drawLetterM;
	// Draw letter "М" at page 2, address 4
	LCD_drawChar(2, 4, letterM_data, 5);
	LCD_drawRectangle();
	
}
