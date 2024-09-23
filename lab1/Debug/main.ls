   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.12.9 - 19 Apr 2023
   3                     ; Generator (Limited) V4.5.6 - 18 Jul 2023
2820                     ; 4 main()
2820                     ; 5 {
2822                     	switch	.text
2823  0000               _main:
2827                     ; 6 	PA_DDR = 0x02;
2829  0000 35025002      	mov	_PA_DDR,#2
2830                     ; 7 	PA_CR1 = 0x02;
2832  0004 35025003      	mov	_PA_CR1,#2
2833                     ; 8 	PA_CR2 = 0x02;
2835  0008 35025004      	mov	_PA_CR2,#2
2836                     ; 9 	PA_ODR = 0x02;
2838  000c 35025000      	mov	_PA_ODR,#2
2839                     ; 10 	a = 100;
2841  0010 ae0064        	ldw	x,#100
2842  0013 bf03          	ldw	_a,x
2843                     ; 11 	b = a + 1000;
2845  0015 ae044c        	ldw	x,#1100
2846  0018 bf01          	ldw	_b,x
2847                     ; 12 	c = 0x0F;
2849  001a 350f0000      	mov	_c,#15
2850  001e               L1002:
2851                     ; 13 	while (1);
2853  001e 20fe          	jra	L1002
2895                     	xdef	_main
2896                     	switch	.ubsct
2897  0000               _c:
2898  0000 00            	ds.b	1
2899                     	xdef	_c
2900  0001               _b:
2901  0001 0000          	ds.b	2
2902                     	xdef	_b
2903  0003               _a:
2904  0003 0000          	ds.b	2
2905                     	xdef	_a
2925                     	end
