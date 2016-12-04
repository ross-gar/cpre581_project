// This is a simple version of the loop initialization program meant for use with the Perf tool
int main ()
{
	// Initialize variables
	unsigned int array_length = 100;
	unsigned int data_array [array_length];

	// Write array
	for (int i = 0;  i < array_length; i++) {
		data_array[i] = i + 3;
	} 

	return 0;
}
