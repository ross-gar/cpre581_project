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
	//asm("MCR p15, #0, %0, C9, C12, #1 \n\t" : : "r"(1));
	unsigned int x = 0;
	asm("MRC p15,  #0, %0, c9, c12, #0 \n\t" : "=r" (x)); // Performance monitor control register
	//asm("MRC p15,  #0, %0, c9, c13, #0 \n\t" : "=r" (x));
	std::cout<<std::hex<<"Returned value: 0x"<< x<<std::endl;
	return 0;
}
