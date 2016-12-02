#include <iostream>
#include "pmu_funcs.h"

int main ()
{
	// Initialize variables
	unsigned int result = 0;
	unsigned int array_length = 100;
	unsigned int data_array [array_length];

	// Setup counters
	init_counters();
	reset_counters();
	set_event(0, BRANCH_MISPRED);

	// Perform work
	// Intialize array
	for (int i = 0;  i <=array_length; i++) {
		data_array[i] = i + 3;
	} 

	// Perform some arbitrary operation on the odd elements of the array
	// Smart way
	/*for (int i = 1;  i <=array_length; i = i + 2) {
		data_array[i] = i + 3;
	}*/

	// Kind of dumb way
	/*for (int i = 0;  i <=array_length; i++) {
		// Check for odd	
		if (i % 2 == 1) {
			data_array[i] = i + 3;
		}
	} */

	// Read counter result
	result = read_counter(0);
	std::cout<<std::dec<<"Branch mispredictions: "<<result<<std::endl;
	return 0;
}
