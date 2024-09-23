// my_gpio.h
#ifndef MY_GPIO_H
#define MY_GPIO_H

void delay(unsigned int ms);
void pinMode(char port, int pin, int mode);
void digitalWrite(char port, int pin, int value);
void PWM(char port, int pin, int duty);

#endif // MY_GPIO_H
