#include <iostm8s207.h>
int a,b;
char c;
main()
{
	PA_DDR = 0x02;
	PA_CR1 = 0x02;
	PA_CR2 = 0x02;
	PA_ODR = 0x02;
	a = 100;
	b = a + 1000;
	c = 0x0F;
	while (1);
}