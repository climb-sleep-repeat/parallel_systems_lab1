#include "prefix_sum.h"
#include "helpers.h"
#include <math.h>
#include <pthread.h>
#include <cstring>
extern pthread_barrier_t pb;
using namespace std;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

void* compute_prefix_sum(void *a)
{
    prefix_sum_args_t *args = (prefix_sum_args_t *)a;
    spin_barrier sb(args->n_threads);
    int size = args->n_vals/args->n_threads;
    int start = args->t_id*size;
    int end = start+size;

    if(start > 0)
        args->output_vals[start] = args->input_vals[start] + args->input_vals[start-1];
    else
        args->output_vals[start] = args->input_vals[start];
    for (int i = start+1;i<end;i++){
        args->output_vals[i]= args->op(args->input_vals[i-1],args->input_vals[i], args->n_loops);
    }
    static int output_vals =0 ;
 
    for(int stride = 2; stride<args->n_vals; stride<<=1){
        sb.wait();
        size = (args->n_vals-stride)/args->n_threads;
        start = stride + args->t_id*size;
        end = start + size;
        int num_loops = args->n_loops;
        for(int j = start; j<end; j++){
            //pthread_mutex_lock(mutex1)
            output_vals = args->op(1,2, num_loops);
        }
    }
    return (void *)&output_vals;
}
