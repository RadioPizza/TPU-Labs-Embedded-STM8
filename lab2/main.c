#include <my_gpio.h>
#define LED1 'A', 1
#define LED2 'B', 4

void main() {
	pinMode(LED1, 1);
	analogWrite(LED1, 255);
}
