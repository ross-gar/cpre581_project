#include <iostream>
#include "pmu_funcs.h"

int main ()
{
	// Initialize variables
	unsigned int result = 0, temp = 0;
	unsigned int matrix_dim = 100;
	unsigned int matrix_a [matrix_dim][matrix_dim];
	unsigned int matrix_b [matrix_dim][matrix_dim];
	unsigned int matrix_c [matrix_dim][matrix_dim];

	// Intialize matrices with some data
	for (int i = 0;  i <= matrix_dim; i++) {
		for (int j = 0; j <= matrix_dim; j++) {
			matrix_a[i][j] = i + 3 + j*2;
			matrix_b[i][j] = i + 7 + j*3;
			matrix_c [i][j] = 0;
		}
	} 

	// Setup counters
	init_counters();
	reset_counters();
	set_event(0,  L2_REFILL);

	// Normal matrix multiplication
	for (int i = 0;  i <= matrix_dim; i++) {
		for (int j = 0; j <= matrix_dim; j++) {
			temp = 0;
			for (int k = 0; k <= matrix_dim; k++) {
				temp = temp + matrix_a [i][k] * matrix_b [k][j];			
			}
			matrix_c [i][j] = temp;
		}	
	}

	// Read counter result
	result = read_counter(0);
	std::cout<<std::dec<<"Counter 0: "<<result<<std::endl;
	return 0;
}
