#include <stdint.h>
#include <iostm8s207.h>
#define ALL_PINS 0xFF
#define LCD_E (1 << 7)

void delay(uint32_t ms)
{
    while (ms--)
    {
        volatile uint16_t i;
        for (i = 0; i < 127; ++i) // Откалибровано c помощью осциллографа для STM8S207 16 MHz, погрешность менее 5%
        {
            _asm("nop"); // Ассемблерная команда "ничего не делать"
        }
    }
}

void strob(void) // функция строба
{
    PF_ODR |= LCD_E;  // линия Е = 1
    delay(1);         // добавляем задержку для надежности
    PF_ODR &= ~LCD_E; // линия Е = 0, сброс строба
}

main()
{
    PF_DDR = ALL_PINS;
    PF_CR1 = ALL_PINS;
    PF_CR2 = ALL_PINS;

    PB_DDR = ALL_PINS;
    PB_CR1 = ALL_PINS;
    PB_CR2 = ALL_PINS;
    while (1)
    {
        strob();
    }
}
