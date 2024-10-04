#include <my_gpio.h>
#include <my_lcd.h>


void main{
	LCD_setup();
	LCD_clear();
	LCD_drawDot();
	LCD_drawLine();
}