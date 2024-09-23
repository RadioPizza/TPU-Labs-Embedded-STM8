#include "my_gpio.h"

int main() {
    pinMode('A', 1, 1);  // Настроить PA1 как выход
    pinMode('A', 2, 1);  // Настроить PA2 как выход
    
    while (1) {
        digitalWrite('A', 1, 1);  // Включить PA1
        digitalWrite('A', 2, 1);  // Включить PA2
        delay(500);               // Задержка 500 мс
        digitalWrite('A', 1, 0);  // Выключить PA1
        digitalWrite('A', 2, 0);  // Выключить PA2
        delay(500);               // Задержка 500 мс
    }
}
