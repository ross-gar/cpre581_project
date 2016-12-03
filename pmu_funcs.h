/*
MCR: Move to coprocessor from ARM register
MRC: Move to ARM register from coprocessor

Instruction format:
MCR/MRC coproc, #op1, src/dest, CRn, CRm, #op2
CRn and CRm are coprocessor registers
*/

// Define event codes for the ARM A7 architecture
#define MEM_READ			0x06 // Counts number of data read instructions accepted by the Load Store Unit
#define MEM_WRITE			0x07 // Counts number of data write instructions accepted by the Load Store Unit
#define IMM_BRANCH		0x0D // Immediate branch architecturally executed (taken or not taken). 
#define BRANCH_MISPRED	0x10 // Branch mispredicted/not predicted. Counts the number of mispredicted or not-predicted branches executed. 
#define CYCLE_COUNTER		0x11
#define DATA_CACHE_EVICT	0x15 // Data cache eviction
#define L2_ACCESS			0x16 // Level 2 data cache access
#define L2_REFILL			0x17 // Level 2 data cache refill

void init_counters ()
{
	// Enable all counters by writing a 1 to the LSB of performance monitor control register
	asm volatile("MCR p15, #0, %0, C9, C12, #0 \n\t" : : "r"(0x41072001));
	// Write to count enable set register
	asm volatile("MCR p15, #0, %0, C9, C12, #1 \n\t" : : "r"(0x8000000f));
}

void reset_counters ()
{
	// Reset all counters by writing a 1 to bit 1 of performance monitor control register
	asm volatile("MCR p15, #0, %0, C9, C12, #0 \n\t" : : "r"(0x41072003));
	// Clear reset bit
	asm volatile("MCR p15, #0, %0, C9, C12, #0 \n\t" : : "r"(0x41072001));
}

unsigned int read_counter(unsigned int idx)
{
	unsigned int result;
	// Write to select counter
	asm volatile("MCR p15, #0, %0, C9, C12, #5 \n\t" : : "r"(idx));
	// Read counter
	asm volatile("MRC p15,  #0, %0, c9, c13, #2 \n\t" : "=r"(result));
	return result; 
}

void set_event(unsigned int idx, unsigned int event)
{
	// Write to select counter
	asm volatile("MCR p15, #0, %0, C9, C12, #5 \n\t" : : "r"(idx));
	// Write desired event
	asm volatile("MCR p15, #0, %0, C9, C13, #1 \n\t" : : "r"(event));
}
