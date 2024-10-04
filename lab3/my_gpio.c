// my_gpio v2
#include <my_gpio.h>

#define INPUT		0
#define OUTPUT	1

void delay(unsigned int ms)
{
    unsigned long count;
    while (ms > 0)
    {
        count = 50;
        while (count > 0)
        {
            count--;
        }
        ms--;
    }
}

void delay10Microseconds(unsigned int us) {
    while (us > 0) {
        _asm("nop");
        us--;
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
    case 'C':
        DDR = &PC_DDR;
        CR1 = &PC_CR1;
        break;
    case 'D':
        DDR = &PD_DDR;
        CR1 = &PD_CR1;
        break;
    case 'E':
        DDR = &PE_DDR;
        CR1 = &PE_CR1;
        break;
    case 'F':
        DDR = &PF_DDR;
        CR1 = &PF_CR1;
        break;
    case 'G':
        DDR = &PG_DDR;
        CR1 = &PG_CR1;
        break;
    case 'H':
        DDR = &PH_DDR;
        CR1 = &PH_CR1;
        break;
    case 'I':
        DDR = &PI_DDR;
        CR1 = &PI_CR1;
        break;
    default:
        return;
    }

    if (mode == 1)
    {
        *DDR |= (1 << pin);
        *CR1 |= (1 << pin);
    }
    else
    {
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
    case 'C':
        ODR = &PC_ODR;
        break;
    case 'D':
        ODR = &PD_ODR;
        break;
    case 'E':
        ODR = &PE_ODR;
        break;
    case 'F':
        ODR = &PF_ODR;
        break;
    case 'G':
        ODR = &PG_ODR;
        break;
    case 'H':
        ODR = &PG_ODR;
        break;
    case 'I':
        ODR = &PG_ODR;
        break;
    default:
        return;
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