/*
 * 	FIFO queue for shared memory communication between niosII processors
 *
 *  	DATE		: 18-08-2016
 *      AUTHOR	: Isuru Nawinne
*
*	Structure of the FIFO:
*	___________________________________________________________________________
*	| 	full	| 	empty	| 	count		|	|	|	|	|	|	|	|	|
*	| 	?	| 	?		| 	?		|	|	|	|	|	|	|	|	|
*	___________________________________________________________________________
*/


#include "FIFO_1.h"


void WRITE_FIFO_1(int *buffer)
{
	printf("Writing....\n");

	printf("Count: %i\n", IORD_32DIRECT(MEM_BASE, countp));
	printf("Empty: %i\n", IORD_32DIRECT(MEM_BASE, emptyp));
	printf("Full: %i\n", IORD_32DIRECT(MEM_BASE, fullp));
	printf("Write Value: %d\n\n", *buffer);
//	printf("Counterp: %d\n", countp);
//	printf("Emptyp: %d\n", emptyp);
//	printf("Fullp: %d\n\n", fullp);

	// Wait if the fifo is full
	while(IORD_32DIRECT(MEM_BASE,fullp));

	// Write the data to FIFO
	IOWR_32DIRECT(MEM_BASE, writep, *buffer);

	// Update the write pointer
	// Wrap around the write pointer if it is at the last index
	// even if writep is at the end of the FIFO, the queue might not be full
	if (writep == STARTP + UNIT_SIZE * CAPACITY)
		writep = STARTP;
	else writep += UNIT_SIZE;

	// Update "count" in shared mem
	IOWR_32DIRECT(MEM_BASE, countp, IORD_32DIRECT(MEM_BASE,countp)+1);

	// Update the "full?" and "empty?" flags accordingly

	IOWR_32DIRECT(MEM_BASE, emptyp, 0x0000); // Not Empty since we are writing an entry
	IOWR_32DIRECT(MEM_BASE, fullp, (CAPACITY == IORD_32DIRECT(MEM_BASE, countp)));
	// Set the full flag if FIFO is now full
	// Reset the empty flag if FIFO now has 1 enrty



}

//Initialization
void FIFO_1_INIT()
{
	writep = STARTP; // Initially the FIFO is empty, so start writing at the first slot
	readp  = STARTP;
	fullp   = 0; // SET THIS OFFSET (If there are previous FIFOs in shared memory, use Prev Fifo's STARTP + Prev Fifo's size)
	emptyp   = fullp + UNIT_SIZE;
	countp  = emptyp + UNIT_SIZE;

	// Assigning values for the flags.
	IOWR_32DIRECT(MEM_BASE, fullp, 0x0000);
	IOWR_32DIRECT(MEM_BASE, emptyp, 0x0001); // The fifo is empty at the start
	IOWR_32DIRECT(MEM_BASE, countp, 0x0000); // The fifo is empty at the start
}
