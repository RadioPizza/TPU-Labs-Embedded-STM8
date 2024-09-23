#include <my_gpio.h>
#include <iostm8s207.h>

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

const int PWM_FREQ = 1000; // Hz
const int PWM_PERIOD_MICROS = 1000000 / PWM_FREQ;

void analogWrite(char port, int pin, int dutyCycle) {
		unsigned int onTimeMicros = (dutyCycle * PWM_PERIOD_MICROS) / 255;
    unsigned int offTimeMicros = PWM_PERIOD_MICROS - onTimeMicros;
    volatile unsigned char* ODR;
    switch (port) {
        case 'A': ODR = &PA_ODR; break;
        case 'B': ODR = &PB_ODR; break;
        default: return;
    }
    while (1) {
        *ODR |= (1 << pin);
        delay10Microseconds(onTimeMicros/10);
        
        *ODR &= ~(1 << pin);
        delay10Microseconds(offTimeMicros/10);
    }
}

