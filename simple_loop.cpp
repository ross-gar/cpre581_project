#include <iostream>
#include "pmu_funcs.h"

int main ()
{
	// Initialize variables
	unsigned int branch_miss = 0, cycle_count = 0;
	unsigned int branch_miss_sum = 0, cycle_count_sum = 0;
	unsigned int array_length = 100;
	unsigned int num_runs = 25;
	unsigned int data_array [array_length];

	std::cout<<"All tests run "<<num_runs<<" times and results averaged"<<std::endl;

	// Setup counters
	init_counters();
	set_event(0, BRANCH_MISPRED);
	set_event(1, CYCLE_COUNTER);

	/* 
	-----------------------------------------------------------------------------------
	Array initialization test
	-----------------------------------------------------------------------------------
	*/

	// Perform 10 test runs
	for (int run = 0; run <num_runs; run ++) {
		reset_counters();
		// Write array
		for (int i = 0;  i < array_length; i++) {
			data_array[i] = i + 3;
		} 
	
	// Read counter results
	branch_miss = read_counter(0);
	cycle_count = read_counter(1);
	// Accumulate counter results
	branch_miss_sum += branch_miss;
	cycle_count_sum += cycle_count;
	}

	// Average run counts
	branch_miss_sum = branch_miss_sum/num_runs;
	cycle_count_sum = cycle_count_sum/num_runs;
	// Output results
	std::cout<<"Array init       branch misses: "<<branch_miss_sum<<"\tcycle count: "<<cycle_count_sum<<std::endl;
	// Clear results
	branch_miss_sum = 0;
	cycle_count_sum = 0;

	/* 
	-----------------------------------------------------------------------------------
	Simple odd element loop test
	-----------------------------------------------------------------------------------
	*/

	// Perform 10 test runs
	for (int run = 0; run <num_runs; run ++) {
		reset_counters();
		// Simple way
		for (int i = 0;  i < array_length; i++) {
			// Check for odd	
			if (i % 2 == 1) {
				data_array[i] = i + 3;
			}
		} 

	// Read counter results
	branch_miss = read_counter(0);
	cycle_count = read_counter(1);
	// Accumulate counter results
	branch_miss_sum += branch_miss;
	cycle_count_sum += cycle_count;
	}

	// Average run counts
	branch_miss_sum = branch_miss_sum/num_runs;
	cycle_count_sum = cycle_count_sum/num_runs;
	// Output results
	std::cout<<"Simple operation branch misses: "<<branch_miss_sum<<"\tcycle count: "<<cycle_count_sum<<std::endl;
	// Clear results
	branch_miss_sum = 0;
	cycle_count_sum = 0;

	/* 
	-----------------------------------------------------------------------------------
	Smart odd element loop test
	-----------------------------------------------------------------------------------
	*/

	// Perform 10 test runs
	for (int run = 0; run <num_runs; run ++) {
		reset_counters();
		// Smart way
		for (int i = 1;  i < array_length; i = i + 2) {
			data_array[i] = i + 3;
		}

	// Read counter results
	branch_miss = read_counter(0);
	cycle_count = read_counter(1);
	// Accumulate counter results
	branch_miss_sum += branch_miss;
	cycle_count_sum += cycle_count;
	}

	// Average run counts
	branch_miss_sum = branch_miss_sum/num_runs;
	cycle_count_sum = cycle_count_sum/num_runs;
	// Output results
	std::cout<<std::dec<<"Smart operation  branch misses: "<<branch_miss_sum<<"\tcycle count: "<<cycle_count_sum<<std::endl;

	return 0;
}
