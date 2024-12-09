/** @file delay.h
 *  @brief Функция для создания задержек
 */

#ifndef DELAY_H
#define DELAY_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief Задержка на указанное количество миллисекунд
     *
     * @param ms Количество миллисекунд задержки
     */
    void delay_ms(uint32_t ms);

    /**
     * @brief Задержка на указанное количество миллисекунд
     *
     * @param ms Количество миллисекунд задержки
     */
    void delay_us(uint8_t us);

#ifdef __cplusplus
}
#endif

#endif // DELAY_H
