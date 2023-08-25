#pragma once

#include <stdlib.h>
#include <pthread.h>
#include <spin_barrier.h>
#include <iostream>

void* compute_prefix_sum(void* a);
void* compute_prefix_sum2(void *a);
