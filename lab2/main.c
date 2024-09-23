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