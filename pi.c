/*

This program will numerically compute the integral of

            4/(1+x*x) 
            
from 0 to 1.  The value of this integral is pi -- which 
is great since it gives us an easy way to check the answer.

The is the original sequential program.  It uses the timer
from the OpenMP runtime library

History: Written by Tim Mattson, 11/99.

*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
double step;
int main(int argc, char *argv[])
{
    //printf("argc: %i\n", argc);
    long num_steps;
    if (argc == 2) {
        num_steps = atol(argv[1]);
    }
    else {
        //printf("I need an input parameter\n");
        return 1;
    }
    //printf("NUM STEPS: %ld\n", num_steps);
    double x, pi, sum = 0.0;
    double start_time, run_time;

    step = 1.0/(double) num_steps;


    start_time = omp_get_wtime();

    #pragma omp parallel for num_threads(8)
    for (int i=1;i<= num_steps; i++){
        x = (i-0.5)*step;
        sum = sum + 4.0/(1.0+x*x);
        //printf("T: %i, x: %4.2f, sum: %4.2f\n", omp_get_thread_num(), x, sum);
    }

    //printf("sum: %4.2f\n", sum);
    pi = step * sum;
    run_time = omp_get_wtime() - start_time;
    printf("%ld steps: pi is %1.20f in %lf seconds\n ",num_steps,pi,run_time);
}    
