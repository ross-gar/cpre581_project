# cpre581_project
This project tested on linux kernel version 4.4.21-v7+

Make to generate pmu_module.ko kernel module

Use taskset to force kernel to load kernel module on core 0 of quad core processor:
sudo taskset -c 0 insmod pmu_module.ko

Also use taskset to force test programs to use core 0 so that the PMU registers are enabled:
sudo taskset -c0 ./testProg
