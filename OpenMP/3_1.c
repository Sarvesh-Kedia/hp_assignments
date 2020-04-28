// parallel version of serial code
// updated so as to prevent false sharing


#include<stdio.h>
#include<omp.h>
#define NUM_THREADS 4
#define PAD 8           // assume 64 byte l1 cache line size

static long num_steps = 100000;
double step;

int main(){
    int i, nthreads;
    double pi, sum[NUM_THREADS][PAD];           // there is a chnge here as well

    step = 1.0/(double)num_steps;

    omp_set_num_threads(NUM_THREADS);

    double start = omp_get_wtime();

    #pragma omp parallel
    {
        int i, id, nthrds;
        double x;
        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();
        if(id==0){
            nthreads = nthrds;          // to store the actual number of threads we have been given and store it in a shared variable
        }
        for(i=id, sum[id][0]=0.0; i<num_steps; i=i+nthrds){
            x = (i+0.5)*step;
            sum[id][0] += 4.0/(1.0+x*x);
        }
    }


    for(i=0, pi=0.0; i<nthreads; ++i){
        pi += sum[i][0]*step;
    }

    double end = omp_get_wtime();

    double total_time = end - start;

    printf("pi: %lf\n", pi);
    printf("execution time: %lf\n", total_time);
}

// but this padding thing wont work on all machine. so how to fix that? how do we know hardware of the machine?