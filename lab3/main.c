#include "iostm8s207.h"
#include "delay.h"

// Макрос для определения бита PD6
#define PD6_PIN (1 << 6)

/**
 * @brief Инициализация порта D
 *
 * Настраивает PD6 как выход в режиме push-pull и устанавливает низкий уровень.
 */
void portD_init(void)
{
    PD_DDR |= PD6_PIN;    ///< Устанавливаем PD6 как выход
    PD_CR1 |= PD6_PIN;    ///< Настраиваем PD6 в режим push-pull
    PD_ODR &= ~PD6_PIN;   ///< Устанавливаем PD6 в низкое состояние
}

void main(void)
{
    portD_init(); ///< Инициализация порта D

    while (1)
    {
        PD_ODR ^= PD6_PIN; ///< Инвертируем состояние PD6
        delay_5us(1000);
    }
}
