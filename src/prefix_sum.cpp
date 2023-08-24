#include "prefix_sum.h"
#include "helpers.h"
#include <math.h>

void* compute_prefix_sum(void *a)
{
    prefix_sum_args_t *args = (prefix_sum_args_t *)a;

    int size = args->n_vals/args->n_threads;
    int start = args->t_id*size;
    int end = start+size;
    args->output_vals[start]=args->input_vals[start];
    
    for (int i = start + 1;i<end;i++){
        args->output_vals[i]=args->input_vals[i-1]+args->input_vals[i];
        
    }

    int num_its = (int)log2((float)args->n_vals);
    for(int i = 1; i<num_its; i++){
        int interval=(int)pow((double)2, (double)i);
        std::cout << interval << std::endl;
        for(int j = end-1; j>=start+interval; j--){
            args->output_vals[j]=args->output_vals[j]+args->output_vals[j-interval];
        }
    }
    return 0;
}
