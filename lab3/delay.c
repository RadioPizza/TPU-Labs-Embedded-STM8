/** @file delay.c
 *  @brief Реализация функции задержки на указанный промежуток времени.
 */

#include "delay.h"

void delay_ms(uint32_t ms)
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

void delay_5us(uint8_t us)
{
    while (us--)
    {
        volatile uint8_t i;
        for (i = 0; i < 5; ++i) // Откалибровано c помощью осциллографа для STM8S207 16 MHz, погрешность менее 5%
        {
            _asm("nop"); // Ассемблерная команда "ничего не делать"
        }
    }
}