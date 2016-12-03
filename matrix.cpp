#include <iostream>
#include "pmu_funcs.h"

int main ()
{
	// Initialize variables
	unsigned int l2_refill = 0, l2_access = 0, cycle_count = 0, temp = 0;
	unsigned int block_size = 4;
	unsigned int matrix_dim = 128;
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
	set_event(1, CYCLE_COUNTER);
	set_event(2, L2_ACCESS);

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
	l2_refill = read_counter(0);
	cycle_count = read_counter(1);
	l2_access = read_counter(2);
	std::cout<<std::dec<<"Standard L2 refill: "<<l2_refill<<"\tL2 access: "<<l2_access<<"\tCycle count: "<<cycle_count<<std::endl;
	reset_counters();

	// Blocking matrix multiplication
	for (int jj = 0; jj <= matrix_dim; jj = jj + block_size) {
		for (int kk = 0; kk <= matrix_dim; kk = kk + block_size) {
			for (int i = 0; i <= matrix_dim; i++) {
				for (int j = jj; j <= std::min(jj+block_size, matrix_dim); j++) {
					temp = 0;
					for (int k = kk; k <= std::min(kk+block_size, matrix_dim); k++) {
						temp = temp + matrix_a [i][k] * matrix_b [k][j];
					}
					matrix_c [i][j] = matrix_c [i][j] + temp;
				}			
			}
		}
	}

	// Read counter result
	l2_refill = read_counter(0);
	cycle_count = read_counter(1);
	l2_access = read_counter(2);
	std::cout<<std::dec<<"Block    L2 refill: "<<l2_refill<<" \tL2 access: "<<l2_access<<"\tCycle count: "<<cycle_count<<std::endl;
	reset_counters();

	return 0;
}
