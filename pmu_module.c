#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int __init enable_pmu (void)
{
	printk(KERN_INFO "Enabling user access of PMU registers\n");
	// Set "user enable register"
	asm("MCR p15, 0, %0, C9, C14, 0 \n\t" : : "r"(1));
	// Disable counter overflow interrupt
	asm("MCR p15, 0, %0, C9, C14, 2 \n\t" : : "r"(0x8000000f));
	printk(KERN_INFO "User access of PMU registers enabled\n");
	return 0;
}

static void __exit disable_pmu (void)
{
	printk(KERN_INFO "Disabling user access of PMU registers\n");
	// Disable "user enable register"
	asm("MCR p15, 0, %0, C9, C14, 0 \n\t" : : "r"(0));
	printk(KERN_INFO "User access of PMU registers disabled\n");
}

module_init(enable_pmu);
module_exit(disable_pmu);
