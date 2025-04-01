#include <stdlib.h>     // Для использования функции abs(x)
#include <stdint.h>     // Для использования стандартных типов
#include <iostm8s207.h> // Для удобного обращения к регистрам переферии

// Пины ЖК дисплея
// Port B
#define LCD_D0  (1 << 0)
#define LCD_D1  (1 << 1)
#define LCD_D2  (1 << 2)
#define LCD_D3  (1 << 3)
#define LCD_D4  (1 << 4)
#define LCD_D5  (1 << 5)
#define LCD_D6  (1 << 6)
#define LCD_D7  (1 << 7)
// Port F
#define LCD_E1  (1 << 0)
#define LCD_E2  (1 << 3)
#define LCD_RES (1 << 4)
#define LCD_RW  (1 << 5)
#define LCD_A0  (1 << 6)
#define LCD_E   (1 << 7)

// Макросы для удобства
#define ALL_PINS 0xFF         // "1" для всех пинов порта
#define TURN_ON_COMMAND 0x3F  // Команда вкл. дисплея
#define TURN_OFF_COMMAND 0x3E // Команда выкл. дисплея

// Макросы для управления сигналавами
#define LCD_ENABLE_E()    (PF_ODR |= LCD_E)     // Включить E
#define LCD_DISABLE_E()   (PF_ODR &= ~LCD_E)    // Отключить E
#define LCD_ENABLE_E1()   (PF_ODR |= LCD_E1)    // Включить E1
#define LCD_DISABLE_E1()  (PF_ODR &= ~LCD_E1)   // Отключить E1
#define LCD_ENABLE_E2()   (PF_ODR |= LCD_E2)    // Включить E2
#define LCD_DISABLE_E2()  (PF_ODR &= ~LCD_E2)   // Отключить E2
#define LCD_RESET_ON()    (PF_ODR &= ~LCD_RES)  // Включить сброс (RESET = 0)
#define LCD_RESET_OFF()   (PF_ODR |= LCD_RES)   // Отключить сброс (RESET = 1)

// Макросы для переключения режимов
#define LCD_DATA_MODE()   (PF_ODR |= LCD_A0)  // Переключение в режим данных (A0 = 1)
#define LCD_CMD_MODE()    (PF_ODR &= ~LCD_A0) // Переключение в режим команд (A0 = 0)
#define LCD_READ_MODE()   (PF_ODR |= LCD_RW)  // Переключение в режим чтения (RW = 1)
#define LCD_WRITE_MODE()  (PF_ODR &= ~LCD_RW) // Переключение в режим записи (RW = 0)

// Макросы для выбора страницы и столбца
#define LCD_SET_PAGE(page)      (PB_ODR = (0b10111000 | ((page) & 0b00000111)))     // Выбор страницы
#define LCD_SET_COLUMN(column)  (PB_ODR = (0b01000000 | ((column) & 0b00111111)))   // Выбор столбца

#define LCD_PAGES 8       // Количество страниц (8 страниц по 8 строк)
#define LCD_COLUMNS 128   // Количество столбцов (128 столбцов)

uint8_t displayBuffer[LCD_PAGES][LCD_COLUMNS]; // Буфер для хранения данных дисплея

// Функция задержки, реализующая задержку в миллисекундах.
// Использует вложенный цикл для создания временной паузы.
// Калибровка произведена для частоты 16 МГц, погрешность менее 5%
void delay(uint32_t ms)
{
    // Перебор каждой миллисекунды
    while (ms--)
    {
        // Переменная для внутреннего счета
        volatile uint16_t i;
        // Цикл для создания задержки на одну миллисекунду
        for (i = 0; i < 127; ++i) // Откалибровано c помощью осциллографа для STM8S207 16 MHz
        {
            _asm("nop"); // Ассемблерная команда "без операции" для создания задержки
        }
    }
}

// Функция строба для ЖК дисплея. Производит импульс на линии E для фиксации данных.
void LCD_strobe(void)
{
    LCD_ENABLE_E();  // Устанавливаем линию E в высокий уровень
    delay(20);       // Необходимая задержка установлена экспериментально
    LCD_DISABLE_E(); // Сбрасываем линию E в низкий уровень, завершая импульс
}

// Функция инициализации ЖК дисплея
void LCD_init(void)
{
    // Сброс дисплея
    LCD_RESET_ON();  // Устанавливаем сигнал RESET в низкий уровень
    delay(5);        // Задержка для обеспечения корректного прохождения сигнала сброса
    LCD_RESET_OFF(); // Устанавливаем сигнал RESET обратно в высокий уровень
    delay(20);       // Дополнительная задержка после сброса

    // Инициализация управляющих сигналов
    LCD_DISABLE_E(); // Строб E в низкий уровень
    LCD_CMD_MODE();
    LCD_WRITE_MODE(); // Сигнал RW (Read/Write) в низкий уровень (режим записи)

    // Включение обоих кристаллов (E1 и E2)
    LCD_ENABLE_E1();
    LCD_ENABLE_E2();

    // Отправка команды включения дисплея
    PB_ODR = TURN_ON_COMMAND; // Устанавливаем команду на шину данных
    LCD_strobe();             // Фиксируем команду на дисплее
}

// Функция чтения байта из дисплея
uint8_t LCD_readByte(uint8_t controller)
{
    uint8_t data;
    uint8_t original_ddr = PB_DDR;
    PB_DDR = 0x00; // Настройка порта B на ввод

    LCD_READ_MODE();
    LCD_DATA_MODE();

    if (controller == 1)
    {
        LCD_ENABLE_E1();
        LCD_DISABLE_E2();
    }
    else
    {
        LCD_ENABLE_E2();
        LCD_DISABLE_E1();
    }

    PF_ODR |= LCD_E;
    delay(1);
    PF_ODR &= ~LCD_E;
    PF_ODR |= LCD_E;
    data = PB_IDR;
    PF_ODR &= ~LCD_E;

    PB_DDR = original_ddr; // Восстановление DDR порта B
    LCD_WRITE_MODE();
    LCD_CMD_MODE();
    return data;
}

// Установка пикселя напрямую
void LCD_drawPixelDirect(uint8_t x, uint8_t y)
{
    uint8_t page = y / 8;
    uint8_t bit = y % 8;
    uint8_t column, controller, data;

    if (x >= LCD_COLUMNS || y >= LCD_PAGES * 8)
        return;

    if (x < 64)
    {
        controller = 1;
        column = x;
    }
    else
    {
        controller = 2;
        column = x - 64;
    }

    // Установка адреса
    LCD_CMD_MODE();
    LCD_WRITE_MODE();

    if (controller == 1)
    {
        LCD_ENABLE_E1();
        LCD_DISABLE_E2();
    }
    else
    {
        LCD_ENABLE_E2();
        LCD_DISABLE_E1();
    }

    LCD_SET_PAGE(page);
    LCD_strobe();
    LCD_SET_COLUMN(column);
    LCD_strobe();

    // Чтение данных
    LCD_READ_MODE();
    LCD_DATA_MODE();
    data = LCD_readByte(controller);

    // Модификация данных
    data |= (1 << bit);

    // Запись данных
    LCD_CMD_MODE();
    LCD_WRITE_MODE();
    if (controller == 1)
    {
        LCD_ENABLE_E1();
        LCD_DISABLE_E2();
    }
    else
    {
        LCD_ENABLE_E2();
        LCD_DISABLE_E1();
    }

    LCD_SET_PAGE(page);
    LCD_strobe();
    LCD_SET_COLUMN(column);
    LCD_strobe();
    LCD_DATA_MODE();
    PB_ODR = data;
    LCD_strobe();

    LCD_DISABLE_E1();
    LCD_DISABLE_E2();
}

// Функция для отрисовки буквы "M" на дисплее
void LCD_drawLetterM(void)
{
    // Включение первого контроллера дисплея (E1) и отключение второго (E2)
    LCD_ENABLE_E1();
    LCD_DISABLE_E2();

    // Установка страницы (Page 0)
    LCD_CMD_MODE();  // Переключение в режим команд
    LCD_SET_PAGE(0); // Выбор страницы 0
    LCD_strobe();    // Фиксируем команду

    // Установка начального столбца (Column 0)
    LCD_SET_COLUMN(0); // Выбор столбца 0
    LCD_strobe();      // Фиксируем команду

    // Переключение в режим данных (A0 = 1)
    LCD_DATA_MODE();

    // Отрисовка буквы "M" по столбцам слева направо
    PB_ODR = 0b01111111;
    LCD_strobe();
    PB_ODR = 0b00000010;
    LCD_strobe();
    PB_ODR = 0b00000100;
    LCD_strobe();
    PB_ODR = 0b00000010;
    LCD_strobe();
    PB_ODR = 0b01111111;
    LCD_strobe();
}

// Функция для отрисовки прямоугольника 6x75 на дисплее
void LCD_drawRectangle(void)
{
    uint8_t col;

    // Первая часть: кристалл 1 (64 столбца)
    LCD_ENABLE_E1();  // Включить кристалл 1
    LCD_DISABLE_E2(); // Отключить кристалл 2

    // Установка страницы (Page 0)
    LCD_CMD_MODE();  // Переключение в режим команд
    LCD_SET_PAGE(0); // Выбор страницы 0
    LCD_strobe();    // Фиксируем команду

    // Установка начального столбца (Column 0)
    LCD_SET_COLUMN(0); // Выбор столбца 0
    LCD_strobe();      // Фиксируем команду

    // Переключение в режим данных (A0 = 1)
    LCD_DATA_MODE();

    // Отрисовка левой стороны прямоугольника
    PB_ODR = 0b01111110; // Левая сторона прямоугольника
    LCD_strobe();

    // Внутренние столбцы (63 раза, до конца кристалла)
    for (col = 1; col < 64; col++)
    {
        PB_ODR = 0b01000010; // Внутренний столбец (верх и низ)
        LCD_strobe();
    }

    // Вторая часть: кристалл 2 (оставшиеся 11 столбцов)
    LCD_ENABLE_E2();  // Включить кристалл 2
    LCD_DISABLE_E1(); // Отключить кристалл 1

    // Установка страницы (Page 0)
    LCD_CMD_MODE();  // Переключение в режим команд
    LCD_SET_PAGE(0); // Выбор страницы 0
    LCD_strobe();    // Фиксируем команду

    // Установка начального столбца (Column 0)
    LCD_SET_COLUMN(0); // Выбор столбца 0
    LCD_strobe();      // Фиксируем команду

    // Переключение в режим данных (A0 = 1)
    LCD_DATA_MODE();

    // Отрисовка оставшихся 10 внутренних столбцов
    for (col = 64; col < 74; col++)
    {
        PB_ODR = 0b01000010; // Внутренний столбец (верх и низ)
        LCD_strobe();
    }

    // Отрисовка правой стороны прямоугольника (75-й столбец)
    PB_ODR = 0b01111110; // Правая сторона прямоугольника
    LCD_strobe();
}

// Функция для отрисовки буквы "А" на дисплее
void LCD_drawLetterA(void)
{
    // Включение кристалла 1 (E1) и отключение кристалла 2 (E2)
    LCD_ENABLE_E1();
    LCD_DISABLE_E2();

    // Установка страницы (Page 1)
    LCD_CMD_MODE();  // Переключение в режим команд
    LCD_SET_PAGE(1); // Выбор страницы 1
    LCD_strobe();    // Фиксируем команду

    // Установка начального столбца (Column 0)
    LCD_SET_COLUMN(0); // Выбор столбца 0
    LCD_strobe();      // Фиксируем команду

    // Переключение в режим данных (A0 = 1)
    LCD_DATA_MODE();

    // Отрисовка буквы "А" по столбцам
    PB_ODR = 0b01111110; // Первый столбец
    LCD_strobe();
    PB_ODR = 0b00010001; // Второй столбец
    LCD_strobe();
    PB_ODR = 0b00010001; // Третий столбец
    LCD_strobe();
    PB_ODR = 0b00010001; // Четвёртый столбец
    LCD_strobe();
    PB_ODR = 0b01111110; // Пятый столбец
    LCD_strobe();
}

// Функция для отрисовки узора на дисплее
void LCD_drawPattern(void)
{
    uint8_t period, col;
    // Включение кристалла 2 (E2) и отключение кристалла 1 (E1)
    LCD_ENABLE_E2();
    LCD_DISABLE_E1();

    // Установка страницы (Page 7)
    LCD_CMD_MODE();  // Переключение в режим команд
    LCD_SET_PAGE(7); // Выбор страницы 7 (если нумерация с 0)
    LCD_strobe();    // Фиксируем команду

    // Установка начального столбца (Column 0)
    LCD_SET_COLUMN(0); // Выбор столбца 0
    LCD_strobe();      // Фиксируем команду

    // Переключение в режим данных (A0 = 1)
    LCD_DATA_MODE();

    // Отрисовка узора
    for (period = 0; period < 8; period++)
    { // 8 периодов
        for (col = 0; col < 8; col++)
        {                        // 8 столбцов в периоде
            PB_ODR = (1 << col); // Сдвигаем единицу на col битов влево
            LCD_strobe();
        }
    }
}

// Функция для отрисовки буквы "А" на заданном начальном столбце
void LCD_drawLetterAAtColumn(uint8_t startColumn)
{
    // Переключение в режим команд
    LCD_CMD_MODE();

    // Установка начального столбца
    LCD_SET_COLUMN(startColumn); // Выбор столбца
    LCD_strobe();                // Фиксируем команду

    // Переключение в режим данных
    LCD_DATA_MODE();

    // Отрисовка буквы "А" по столбцам
    PB_ODR = 0b01111110; // Первый столбец
    LCD_strobe();
    PB_ODR = 0b00010001; // Второй столбец
    LCD_strobe();
    PB_ODR = 0b00010001; // Третий столбец
    LCD_strobe();
    PB_ODR = 0b00010001; // Четвёртый столбец
    LCD_strobe();
    PB_ODR = 0b01111110; // Пятый столбец
    LCD_strobe();
}

// Функция для очистки области буквы
void LCD_clearLetterArea(uint8_t startColumn)
{
    uint8_t c;

    // Переключение в режим команд
    LCD_CMD_MODE();

    // Установка начального столбца
    LCD_SET_COLUMN(startColumn); // Выбор столбца
    LCD_strobe();                // Фиксируем команду

    // Переключение в режим данных
    LCD_DATA_MODE();

    // Очистка области буквы (5 столбцов)
    for (c = 0; c < 5; c++)
    {
        PB_ODR = 0b00000000; // Очистка столбца
        LCD_strobe();
    }
}

// Функция для очистки буфера
void LCD_clearBuffer(void)
{
    uint8_t page, column;

    for (page = 0; page < LCD_PAGES; page++)
    {
        for (column = 0; column < LCD_COLUMNS; column++)
        {
            displayBuffer[page][column] = 0; // Очистка буфера
        }
    }
}

// Функция для обновления экрана из буфера
void LCD_updateDisplay(void)
{
    uint8_t page, column;

    for (page = 0; page < LCD_PAGES; page++)
    {
        // Обновление левой половины экрана (E1, столбцы 0–63)
        LCD_ENABLE_E1();  // Включить кристалл 1
        LCD_DISABLE_E2(); // Отключить кристалл 2

        // Установка страницы
        LCD_CMD_MODE();     // Переключение в режим команд
        LCD_SET_PAGE(page); // Выбор страницы
        LCD_strobe();       // Фиксируем команду

        // Установка начального столбца (Column 0)
        LCD_SET_COLUMN(0); // Выбор столбца 0
        LCD_strobe();      // Фиксируем команду

        // Переключение в режим данных
        LCD_DATA_MODE();

        // Отправка данных для левой половины (столбцы 0–63)
        for (column = 0; column < 64; column++)
        {
            PB_ODR = displayBuffer[page][column]; // Отправляем данные из буфера
            LCD_strobe();
        }

        // Обновление правой половины экрана (E2, столбцы 64–127)
        LCD_ENABLE_E2();  // Включить кристалл 2
        LCD_DISABLE_E1(); // Отключить кристалл 1

        // Установка страницы
        LCD_CMD_MODE();     // Переключение в режим команд
        LCD_SET_PAGE(page); // Выбор страницы
        LCD_strobe();       // Фиксируем команду

        // Установка начального столбца (Column 0)
        LCD_SET_COLUMN(0); // Выбор столбца 0
        LCD_strobe();      // Фиксируем команду

        // Переключение в режим данных
        LCD_DATA_MODE();

        // Отправка данных для правой половины (столбцы 64–127)
        for (column = 64; column < LCD_COLUMNS; column++)
        {
            PB_ODR = displayBuffer[page][column]; // Отправляем данные из буфера
            LCD_strobe();
        }
    }
}

// Очищает буфер и выводит пустой буфер на дисплей
void LCD_clear(void)
{
    LCD_clearBuffer();
    LCD_updateDisplay();
}

// Функция для отрисовки пикселя в буфере
void LCD_drawPixel(uint8_t x, uint8_t y, uint8_t value)
{
    uint8_t page, bit;

    if (x >= LCD_COLUMNS || y >= LCD_PAGES * 8)
    {
        return; // Выход за пределы экрана
    }

    // Определяем страницу и бит
    page = y / 8; // Страница (каждая страница управляет 8 строками)
    bit = y % 8;  // Бит в столбце

    // Установка или сброс бита
    if (value)
    {
        displayBuffer[page][x] |= (1 << bit); // Установка бита
    }
    else
    {
        displayBuffer[page][x] &= ~(1 << bit); // Сброс бита
    }
}

// Отрисовка горизонтальной линии
void lineH(int y, int x0, int x1, uint8_t fill)
{
    int x;

    // Убедимся, что x0 <= x1
    if (x0 > x1)
    {
        int temp = x0;
        x0 = x1;
        x1 = temp;
    }

    // Отрисовка линии
    for (x = x0; x <= x1; x++)
    {
        LCD_drawPixel(x, y, fill);
    }
}

// Отрисовка вертикальной линии
void lineV(int x, int y0, int y1, uint8_t fill)
{
    int y;

    // Убедимся, что y0 <= y1
    if (y0 > y1)
    {
        int temp = y0;
        y0 = y1;
        y1 = temp;
    }

    // Отрисовка линии
    for (y = y0; y <= y1; y++)
    {
        LCD_drawPixel(x, y, fill);
    }
}

// Отрисовка линии под любым углом (алгоритм Брезенхэма)
void line(int x0, int y0, int x1, int y1, uint8_t fill)
{
    int dx, dy, sx, sy, err, e2;

    // Проверка на горизонтальную линию
    if (x0 == x1)
    {
        lineV(x0, y0, y1, fill);
        return;
    }

    // Проверка на вертикальную линию
    if (y0 == y1)
    {
        lineH(y0, x0, x1, fill);
        return;
    }

    // Вычисление разницы и направления
    dx = abs(x1 - x0);
    dy = abs(y1 - y0);
    sx = (x0 < x1) ? 1 : -1;
    sy = (y0 < y1) ? 1 : -1;
    err = dx - dy;

    // Отрисовка линии
    while (1)
    {
        LCD_drawPixel(x0, y0, fill);

        // Проверка на завершение
        if (x0 == x1 && y0 == y1)
        {
            break;
        }

        e2 = err << 1;

        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }

        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

/**
 * @brief Попиксельно отрисовывает прямоугольник напрямую, без буферизации, с задержкой между каждым пикселем.
 *
 * @param x1 абцисса левого верхнего угла прямоугольника
 * @param y1 ордината левого верхнего угла прямоугольника
 * @param x2 абцисса правого нижнего угла прямоугольника
 * @param y2 ордината правого нижнего угла прямоугольника
 * @param speed скорость отрисовки
 * 
 * @return 0 - успех, 1 - ошибка координат
 * 
 * @note отрисовка происходит попиксельно по часовой стрелке, начиная от левого верхнего угла
 * @note доп. задание - защита лабораторной работы.
 */
uint8_t defenceTask(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t speed)
{
    uint8_t x, y;

    // Проверка координат
    if (x1 > x2 || y1 > y2 || x2 >= LCD_COLUMNS || y2 >= LCD_PAGES * 8)
    {
        return 1;
    }

    // Верхняя грань
    for (x = x1; x <= x2; x++)
    {
        LCD_drawPixelDirect(x, y1);
        delay(speed);
    }

    // Правая грань
    if (y2 > y1)
    {
        for (y = y1 + 1; y <= y2; y++)
        {
            LCD_drawPixelDirect(x2, y);
            delay(speed);
        }
    }

    // Нижняя грань
    if (x2 > x1)
    {
        for (x = x2 - 1; x >= x1; x--)
        {
            LCD_drawPixelDirect(x, y2);
            delay(speed);
        }
    }

    // Левая грань
    if (y2 > y1 + 1)
    {
        for (y = y2 - 1; y > y1; y--)
        {
            LCD_drawPixelDirect(x1, y);
            delay(speed);
        }
    }

    return 0;
}

// Главная функция программы (точка входа)
void main()
{
    // Настройка портов PF и PB как выходных для управления дисплеем
    PF_DDR = ALL_PINS; // Направление порта F на вывод
    PF_CR1 = ALL_PINS; // Режим push-pull для порта F
    PF_CR2 = ALL_PINS; // Высокая скорость для порта F

    PB_DDR = ALL_PINS; // Направление порта B на вывод
    PB_CR1 = ALL_PINS; // Режим push-pull для порта B
    PB_CR2 = ALL_PINS; // Высокая скорость для порта B

    // Инициализация ЖК дисплея
    LCD_init();
    LCD_clear();
    defenceTask(3, 3, 9, 9, 50);
    defenceTask(12, 15, 32, 45, 0);
    defenceTask(23, 2, 120, 40, 20);
    defenceTask(117, 33, 125, 50, 15);
}