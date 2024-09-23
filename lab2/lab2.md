3.

```C
#include <iostm8s207.h>
main()
{
 PA_DDR = 0x06;
 PA_CR1 = 0x06;
 PA_CR2 = 0x00;
 PA_ODR = 0x02;
 while (1);
}
```

5. Первый светодиод горит, второй нет
6.
8.

```C
#include <iostm8s207.h>
main()
{
 int i;
 PA_DDR = 0x06;
 PA_CR1 = 0x06;
 PA_CR2 = 0x00;
  while (1)
 {
  for (i=0; i<10000; i++);
  PA_ODR = 0x02;
  for (i=0; i<10000; i++);
  PA_ODR &= 0x00;
 };
}
```

9. Вариант 1

```C
#include <iostm8s207.h>
main()
{
 int i;
 PA_DDR = 0x06;
 PA_CR1 = 0x06;
 PA_CR2 = 0x00;
  while (1)
 {
  for (i=0; i<100; i++);
  PA_ODR = 0x02;
  for (i=0; i<100; i++);
  PA_ODR &= 0x00;
 };
}
```

11.

```C
#include <iostm8s207.h>
main()
{
 char i;
 PA_DDR = 0x06;
 PA_CR1 = 0x06;
 PA_CR2 = 0x00;
  while (1)
 {
  for (i=0; i<100; i++);
  PA_ODR = 0x02;
  for (i=0; i<100; i++);
  PA_ODR &= 0x00;
 };
}
```

13. Сделал в самом начале - получил 7 Гц
15.

```
#include <iostm8s207.h>
main()
{
 int i;
 PA_DDR = 0x06;
 PA_CR1 = 0x06;
 PA_CR2 = 0x00;
 while (1){
  for (i=0; i<20000; i++);
  PA_ODR = 0x02;
  for (i=0; i<20000; i++);
  PA_ODR &= 0x00;
 };
} // 3,5 Гц
```

16. Скрин task16.png
17.

```C
#include <iostm8s207.h>
main()
{
 int i;
 PA_DDR = 0x06;
 PA_CR1 = 0x06;
 PA_CR2 = 0x00;
 while (1){
  for (i=0; i<40000; i++);
  PA_ODR = 0x02;
  for (i=0; i<40000; i++);
  PA_ODR &= 0x00;
 };
} // не мигает, т.к. первый цикл for бесконечный (переполнение i)
```

18. да, действительно ошибка
19.

```C
#include <iostm8s207.h>
main()
{
 long int i;
 PA_DDR = 0x06;
 PA_CR1 = 0x06;
 PA_CR2 = 0x00;
 while (1){
  for (i=0; i<40000; i++);
  PA_ODR = 0x02;
  for (i=0; i<40000; i++);
  PA_ODR &= 0x00;
 };
} // мигает с периодом около 1,5 сек
```

20.

```C
#include <iostm8s207.h>
main()
{
 long int i;
 PA_DDR = 0x06;
 PA_CR1 = 0x06;
 PA_CR2 = 0x00;
 while (1){
 for (i=0; i<499; i++){};
 PA_ODR = 0x02;
 for (i=0; i<1; i++){};
 PA_ODR &= 0x00;
 };
}
```

21. светодиод светится очень тускло как и ожидалось
22. светодио светится чуть ярче, т.к. ...
23.
24.

```C
#include <iostm8s207.h>

void delay(void){
 unsigned long int i;
 for (i=0; i<500; i++);
}

main()
{
 PA_DDR = 0x06;
 PA_CR1 = 0x06;
 PA_CR2 = 0x00;
 while (1){
 delay();
 PA_ODR = 0x02;
 delay();
 PA_ODR &= 0x00;
 };
}
```

25. светодиод очень быстро моргает (28 Гц)
26.

```C
void delay(int a){
 unsigned long int i;
 for (i=0; i<a; i++);
}
```

27. Яркое

```C
#include <iostm8s207.h>

void delay(int a){
 unsigned long int i;
 for (i=0; i<a; i++);
}

main()
{
 PA_DDR = 0x06;
 PA_CR1 = 0x06;
 PA_CR2 = 0x00;
 while (1){
 delay(50);
 PA_ODR = 0x02;
 delay(500);
 PA_ODR &= 0x00;
 };
}
```

Тусклое

```C
#include <iostm8s207.h>

void delay(int a){
 unsigned long int i;
 for (i=0; i<a; i++);
}

main()
{
 PA_DDR = 0x06;
 PA_CR1 = 0x06;
 PA_CR2 = 0x00;
 while (1){
 delay(500);
 PA_ODR = 0x02;
 delay(50);
 PA_ODR &= 0x00;
 };
}
```

28.

```C
#include <iostm8s207.h>

void delay(int a){
 unsigned long int i;
 for (i=0; i<a; i++);
}

main()
{
 PA_DDR = 0x06;
 PA_CR1 = 0x06;
 PA_CR2 = 0x00;
 PA_ODR = 0x00; // интересно, какое значение будет иметь регистр ODR если ничего не записывать в него в программе?
 while (1){
 delay(500);
 PA_ODR ^= 0x02; // побитовый XOR: 0 xor 2 = 2   
 delay(50);
 PA_ODR ^= 0x02; // побитовый XOR: 2 xor 2 = 0  
 };
}
```

29.

```C
#include <iostm8s207.h>

void delay(int a){
 unsigned long int i;
 for (i=0; i<a; i++);
}

main()
{
 PA_DDR = 0x06;
 PA_CR1 = 0x06;
 PA_CR2 = 0x00;
 PA_ODR = 0x00;
 while (1){
 delay(500);
 PA_ODR = ~PA_ODR; // в таком случае включатся сразу все линии порта А
 delay(50);
 PA_ODR = ~PA_ODR; // а здесь выключатся сразу все
}
```

# Остановился на 30

30.
