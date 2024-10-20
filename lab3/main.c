#include <my_gpio.h>
#include <my_lcd.h>

void main(){
	LCD_setup();
	*CONTROL_PORT &= ~LCD_E2; // E2 = 0
	*DATA_PORT = 0b10111010; // set page 2
}
