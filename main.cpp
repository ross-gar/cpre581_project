#include <iostream>

/*
MCR: Move to coprocessor from ARM register
MRC: Move to ARM register from coprocessor

Instruction format:
MCR/MRC coproc, #op1, src/dest, CRn, CRm, #op2
CRn and CRm are coprocessor registers
*/

int main ()
{

	unsigned int x = 0;
	// Enable all counters by writing a 1 to the LSB of performance monitor control register
	asm volatile("MCR p15, #0, %0, C9, C12, #0 \n\t" : : "r"(0x41072001));
	// Write to count enable set register
	asm volatile("MCR p15, #0, %0, C9, C12, #1 \n\t" : : "r"(0x8000000f));

	// Write to event type selection register
	asm volatile("MCR p15, #0, %0, C9, C13, #1 \n\t" : : "r"(0x00000007));
	asm volatile("MRC p15,  #0, %0, c9, c13, #1 \n\t" : "=r" (x)); 
	std::cout<<std::hex<<"Event type 1: 0x"<< x<<std::endl;
	// Write to select counter
	asm volatile("MCR p15, #0, %0, C9, C12, #5 \n\t" : : "r"(0x00000001));
	asm volatile("MRC p15,  #0, %0, c9, c13, #1 \n\t" : "=r" (x)); 
	std::cout<<std::hex<<"Event type 2: 0x"<< x<<std::endl;

	/*	
	asm volatile("MRC p15,  #0, %0, c9, c12, #0 \n\t" : "=r" (x)); // Performance monitor control register
	std::cout<<std::hex<<"PMCR Check: 0x"<< x<<std::endl;
	asm volatile("MRC p15,  #0, %0, c9, c13, #0 \n\t" : "=r" (x));  //Cycle count register
	std::cout<<std::hex<<"Cycle Count Register: 0x"<< x<<std::endl;
	asm volatile("MRC p15,  #0, %0, c9, c13, #2 \n\t" : "=r" (x)); 
	std::cout<<std::hex<<"Mystery Value: 0x"<< x<<std::endl;
	*/
	return 0;
}
