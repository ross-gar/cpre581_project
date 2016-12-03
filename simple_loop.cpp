#include <iostream>
#include "pmu_funcs.h"

int main ()
{
	// Initialize variables
	unsigned int branch_miss = 0, cycle_count = 0;
	unsigned int array_length = 100;
	unsigned int data_array [array_length];

	// Setup counters
	init_counters();
	reset_counters();
	set_event(0, BRANCH_MISPRED);
	set_event(1, CYCLE_COUNTER);

	// Perform work
	// Intialize array
	for (int i = 0;  i <=array_length; i++) {
		data_array[i] = i + 3;
	} 

	branch_miss = read_counter(0);
	cycle_count = read_counter(1);
	std::cout<<"Array init       branch misses: "<<branch_miss<<"\tcycle count: "<<cycle_count<<std::endl;
	reset_counters();

	// Perform some arbitrary operation on the odd elements of the array
	// Simple way
	for (int i = 0;  i <=array_length; i++) {
		// Check for odd	
		if (i % 2 == 1) {
			data_array[i] = i + 3;
		}
	} 

	branch_miss = read_counter(0);
	cycle_count = read_counter(1);
	std::cout<<"Simple operation branch misses: "<<branch_miss<<"\tcycle count: "<<cycle_count<<std::endl;
	reset_counters();

	// Smart way
	for (int i = 1;  i <=array_length; i = i + 2) {
		data_array[i] = i + 3;
	}

	branch_miss = read_counter(0);
	cycle_count = read_counter(1);
	std::cout<<std::dec<<"Smart operation  branch misses: "<<branch_miss<<"\tcycle count: "<<cycle_count<<std::endl;
	reset_counters();

	return 0;
}
