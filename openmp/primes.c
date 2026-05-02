//DIMITRA CHRISTINA GKARAVELA AM:5051
#include <stdio.h>
#include <omp.h>

#define UPTO 10000000

long int count,      /* number of primes */
         lastprime;  /* the last prime found */


void serial_primes(long int n) {
	long int i, num, divisor, quotient, remainder;

	if (n < 2) return;
	count = 1;                         /* 2 is the first prime */
	lastprime = 2;

	for (i = 0; i < (n-1)/2; ++i) {    /* For every odd number */
		num = 2*i + 3;
		divisor = 1;
		do 
		{
			divisor += 2;                  /* Divide by the next odd */
			quotient  = num / divisor;  
			remainder = num % divisor;  
		} while (remainder && divisor <= quotient);  /* Don't go past sqrt */

		if (remainder || divisor == num) /* num is prime */
		{
			count++;
			lastprime = num;
		}
	}
}


void openmp_primes(long int n) {
	long int i, num, divisor, quotient, remainder;
	long int local_count = 0;
    long int local_lastprime = 2;

	if (n < 2) return;
    count = 1;       		 /* 2 is the first prime */
    lastprime = 2;

	#pragma omp parallel for private(num, divisor, quotient, remainder) reduction(+: count) reduction(max:lastprime) schedule(guided,5)

	for (i = 0; i < (n-1)/2; ++i) {    /* For every odd number */
		num = 2*i + 3;
		divisor = 1;
		do 
		{
			divisor += 2;                  /* Divide by the next odd */
			quotient  = num / divisor;  
			remainder = num % divisor;  
		} while (remainder && divisor <= quotient);  /* Don't go past sqrt */

		if (remainder || divisor == num) /* num is prime */
		{
			count++;
            lastprime = num;
		}
	}
}


int main()
{
	double start, end, serial_time, openmp_time;
	printf("Serial and parallel prime number calculations:\n");
	
	/* Time the following to compare performance 
	 */
	start = omp_get_wtime();
	serial_primes(UPTO);        /* time it */
	end = omp_get_wtime();
    serial_time = end - start;
	printf("[serial] count = %ld, lastprime = %ld (time = %.6f sec)\n", count, lastprime, serial_time);
    


	start = omp_get_wtime();
	openmp_primes(UPTO);        /* time it */
	end = omp_get_wtime();
    openmp_time = end - start;
	printf("[openmp] count = %ld, lastprime = %ld (time = %.6f sec)\n", count, lastprime, openmp_time);
    
	return 0;
}