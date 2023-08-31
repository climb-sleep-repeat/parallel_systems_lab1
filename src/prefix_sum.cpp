#include "prefix_sum.h"
#include "helpers.h"
#include <math.h>
#include <pthread.h>
using namespace std;

void* compute_prefix_sum(void *a)
{
    prefix_sum_args_t *args = (prefix_sum_args_t *)a;
    spin_barrier sb(args->n_threads);
    int size = args->n_vals/args->n_threads;
    int start = args->t_id*size;
    int end = start+size;
    args->output_vals[start]=args->input_vals[start];
    for (int i = start + 1;i<end;i++){
        args->output_vals[i]=args->input_vals[i-1]+args->input_vals[i];
        args->input_vals[i-1]=args->output_vals[i-1];
    }
    args->input_vals[end-1]=args->output_vals[end-1];
    sb.wait(0);
    int num_its = (int)log2((float)args->n_vals);
    for(int i = 1; i<num_its; i++){
        int interval=(int)pow((double)2, (double)i);
        // TODO: make sure this calculation works for 62/60/etc
        size = (args->n_vals-interval)/args->n_threads;
        if(args->t_id == args->n_threads-1)
            size += (args->n_vals-interval)%args->n_threads;
        end = start+size;
        for(int j = start; j<end; j++){
            args->output_vals[j+interval]=args->input_vals[j]+args->input_vals[j+interval];
        }
        sb.wait(2*(i-1)+1);
        memcpy(&args->input_vals[start+interval], &args->output_vals[start+interval], size*sizeof(int));
        sb.wait(2*(i-1)+2);
    }
    return 0;
}
