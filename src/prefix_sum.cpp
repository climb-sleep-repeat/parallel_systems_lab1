#include "prefix_sum.h"
#include "helpers.h"
#include <math.h>
#include <pthread.h>
#include <cstring>

using namespace std;
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
 
    for(int stride = 2; stride<args->n_vals; stride<<=1){
        //wait until everyone is here then copy the ouput back to the input
        sb.wait(args->t_id);
        // pthread_barrier_wait(&pb);
        memcpy(&args->input_vals[start], &args->output_vals[start], (end-start)*sizeof(int));
        sb.wait(args->t_id);
        // pthread_barrier_wait(&pb);
        //recalculate the size/start/end for the current interation
        size = (args->n_vals-stride)/args->n_threads;
        start = stride + args->t_id*size;
        end = start + size;
        //if there's a remainder, tack it on to the end of the last thread
        if(args->t_id==(args->n_threads-1))
            end+=((args->n_vals-stride)%args->n_threads);
        //cout << "start: " << start << " size: " << size << " stride: " << stride << " end: " << end << endl;
        for(int j = start; j<end; j++){
            args->output_vals[j]=args->op(args->input_vals[j], args->input_vals[j-stride], args->n_loops);
            //args->output_vals[j]=args->input_vals[j] + args->input_vals[j-stride];
        }
    }
    return 0;
}
