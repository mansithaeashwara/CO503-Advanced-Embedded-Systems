/*
 * 	Template of producer application using FIFO
 *
 *  	DATE		: 18-08-2016
 *      AUTHOR	: Isuru Nawinne
 */


#include "FIFO_1.h"


void delay(int n);
int producer();


int main()
{
	producer();
	printf("Count: %i\n", IORD_32DIRECT(MEM_BASE, countp));
	printf("Empty: %i\n", IORD_32DIRECT(MEM_BASE, emptyp));
	printf("Full: %i\n\n", IORD_32DIRECT(MEM_BASE, fullp));
	while(1) {}

	return 0;
}


int producer()
{
	printf("Producer starting..\n");

	FIFO_1_INIT(); // Initialize the FIFO

	int j = 5;
	while(j<=500)
	{
		delay(100000);
		WRITE_FIFO_1(&j); // Write to the producer-consumer fifo
		delay(100000);

		printf("Producer sent [%i]\n",j);
		j+=10;
	}

	printf("Producer finished..\n");
	return 0;
}


void delay(int n)
{
	int i;
	for(i=n; i>0; i--)
	{
		continue;
	}
}
