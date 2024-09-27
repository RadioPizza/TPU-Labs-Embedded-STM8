#include <my_gpio.h>
#include <iostm8s207.h>
#define LED1 'A', 1
#define LED2 'A', 2


void main() {
	const int T = 700;
	int i;
	int t_1 = 0;
	int t_2 = 0;
	pinMode(LED1, 1);
	pinMode(LED2, 1);
	while (1){
		for (i = 0; i < T; i++){
			if (i < t_1)
				PA_ODR |= 0b00000010;
			else
				PA_ODR &= 0b11111101;
			if (i < t_2)
				PA_ODR |= 0b00000100;
			else
				PA_ODR &= 0b11111011;	
		}
		t_1+=1;
		t_2+=2;
		if (t_1 == T)
			t_1 = 0;
		if (t_2 == T)
			t_2 = 0;
	}
}