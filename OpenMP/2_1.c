#include<stdio.h>
#include<omp.h>
#define THREAD_NO 4
static long num_steps = 100000;

double step;

int main(){

    omp_set_num_threads(THREAD_NO);

    double no_of_threads = omp_get_num_threads();
    double pi;
    double sum = 0.0, isum[THREAD_NO] = {0.0};

    step = 1.0/(double)num_steps;

    double breakup = num_steps/no_of_threads;

    double start = omp_get_wtime();

    #pragma omp parallel
    {
        int ID = omp_get_thread_num();      //private variable
        double x;

        for(int i=ID*breakup; i<(ID+1)*breakup; i++){
            x = (i+0.5)*step;
            isum[ID] = isum[ID]+4.0/(1.0+x*x);
        }
    }
        
  
    sum = isum[0] + isum[1] + isum[2] + isum[3];
    pi = step * sum;

    double end = omp_get_wtime();

    double total_time = end - start;

    printf("pi: %lf\n", pi);
    printf("execution time: %lf\n", total_time);

}
