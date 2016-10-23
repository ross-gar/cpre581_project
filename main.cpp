#include <iostream>

/*
Coprocessor 15
opcode1 0
destination is x,
c9 and c13 are coprocessor registers
opcode2 0
*/
unsigned int access_value (void)
{
	unsigned int x = 0;
	asm("MCR p15,  #0, %0, c9, c13, #0" : "=r" (x));
	return x;
}

int main ()
{
	unsigned int x = 0;
	x = access_value();
	std::cout<<"Returned value: "<< x<<std::endl;
	return 0;  
}
