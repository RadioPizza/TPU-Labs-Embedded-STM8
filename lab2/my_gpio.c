#include <iostm8s207.h>

void delay(unsigned int ms)
{
    unsigned long count;
    while (ms > 0)
    {
        count = 16000; // Эмпирически настроенные значения для задержки примерно 1 мс
        while (count > 0)
        {
            count--;
        }
        ms--;
    }
}

void pinMode(char port, int pin, int mode)
{
    volatile unsigned char *DDR;
    volatile unsigned char *CR1;

    switch (port)
    {
    case 'A':
        DDR = &PA_DDR;
        CR1 = &PA_CR1;
        break;
    case 'B':
        DDR = &PB_DDR;
        CR1 = &PB_CR1;
        break;
    default:
        return; // Неподдерживаемый порт
    }

    if (mode == 1)
    { // 1 для OUTPUT
        *DDR |= (1 << pin);
        *CR1 |= (1 << pin);
    }
    else
    { // 0 для INPUT
        *DDR &= ~(1 << pin);
        *CR1 &= ~(1 << pin);
    }
}

void digitalWrite(char port, int pin, int value)
{
    volatile unsigned char *ODR;

    switch (port)
    {
    case 'A':
        ODR = &PA_ODR;
        break;
    case 'B':
        ODR = &PB_ODR;
        break;
    default:
        return; // Неподдерживаемый порт
    }

    if (value == 1)
    { // HIGH
        *ODR |= (1 << pin);
    }
    else
    { // LOW
        *ODR &= ~(1 << pin);
    }
}

void PWM(char port, int pin, int duty) {

};