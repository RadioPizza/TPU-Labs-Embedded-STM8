#include <my_gpio.h>
#define LED1 'A', 1
#define LED2 'B', 4


void main() {
	pinMode(LED1, 1);
	pinMode(LED2, 1);
	const int period = 4096;
	while (1){
		for (int i = 0; i <= 510; i++) {
			delay(16);
			int brightness1 = i;
			int brightness2 = i / 2;
			int highTime1 = (period * brightness1) / 255;
			int highTime2 = (period * brightness2) / 255;
			for (int j = 0; j <= 100; j++) {
				if (brightness1 >= brightness2){
					digitalWrite(LED1, 1);
					digitalWrite(LED2, 1);
					delay10Microseconds(highTime2);
					digitalWrite(LED2, 0);
					delay10Microseconds(highTime1 - highTime2);
					digitalWrite(LED1, 0);
					delay10Microseconds(period - highTime1);
				} else {
					digitalWrite(LED2, 1);
					digitalWrite(LED1, 1);
					delay10Microseconds(highTime1);
					digitalWrite(LED1, 0);
					delay10Microseconds(highTime2 - highTime1);
					digitalWrite(LED2, 0);
					delay10Microseconds(period - highTime2);
				}
			}
		}
	}
}
