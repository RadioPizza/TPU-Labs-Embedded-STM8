// my_lcd v1
#ifndef MY_LCD_H
#define MY_LCD_H

//LCD pins					PORT, PIN
#define LCD_D0				'B', 0
#define LCD_D1				'B', 1
#define LCD_D2				'B', 2
#define LCD_D3				'B', 3
#define LCD_D4				'B', 4
#define LCD_D5				'B', 5
#define LCD_D6				'B', 6
#define LCD_D7				'B', 7

#define LCD_E1				'F', 0
#define LCD_E2				'F', 3
#define LCD_RES				'F', 4
#define LCD_RW				'F', 5
#define LCD_A0				'F', 6
#define LCD_E					'F', 7

void LCD_Setup(void);

#endif // MY_LCD_H
