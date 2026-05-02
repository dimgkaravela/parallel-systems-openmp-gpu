//DIMITRA CHRISTINA GKARAVELA AM:5051
#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

/* 
 * Retrieves and prints information for every installed NVIDIA
 * GPU device
 */
void cuinfo_print_devinfo()
{
    int num_devs, i;
    int driverVer, runtimeVer;
    cudaDeviceProp dev_prop;

	/* poses siskeves */
    cudaGetDeviceCount(&num_devs);
	if (num_devs == 0)
	{
		printf("No CUDA devices found.\n");
		return;
	}

    /* version driver & runtime (same for all) */
    cudaDriverGetVersion(&driverVer);
    cudaRuntimeGetVersion(&runtimeVer);
    printf("CUDA Driver Version:   %d.%d\n",
           driverVer / 1000, (driverVer % 1000) / 10);
    printf("CUDA Runtime Version:  %d.%d\n\n",
           runtimeVer / 1000, (runtimeVer % 1000) / 10);


	/* Retrieve and pretty-print all the necessary information */
    for (int i = 0; i < num_devs; ++i)
    {
        cudaGetDeviceProperties(&dev_prop, i);

        printf("Device %d: %s\n", i, dev_prop.name);
        printf("  Compute capability:         %d.%d\n",
               dev_prop.major, dev_prop.minor);
        printf("  Multiprocessors (SMs):      %d\n",
               dev_prop.multiProcessorCount);
        printf("  Global memory:              %.2f MB\n",
               dev_prop.totalGlobalMem / (1024.0 * 1024));
        printf("  Constant memory:            %.2f KB\n",
               dev_prop.totalConstMem / 1024.0);
        printf("  Shared memory per block:    %.2f KB\n",
               dev_prop.sharedMemPerBlock / 1024.0);

        printf("\n");
    }
}

int main()
{
    cuinfo_print_devinfo();
    return 0;
}
