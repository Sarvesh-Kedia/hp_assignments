#include<stdio.h>
#include<omp.h>

static long num_steps = 100000;

double step;

int main(){
    int i;
    double x, pi, sum = 0.0;

    step = 1.0/(double)num_steps;


    double start = omp_get_wtime();

    #pragma omp prallel
    {   
        double x;
        #pragma omp for reduction (+, sum)
            for(i=0; i<(int)num_steps; i++){
                x = (i+0.5)*step;
                sum = sum+4.0/(1.0+x*x);
            }   
    }
    

    pi = step * sum;

    double end = omp_get_wtime();

    double total_time = end - start;

    printf("pi: %lf\n", pi);
    printf("execution time: %lf\n", total_time);
}