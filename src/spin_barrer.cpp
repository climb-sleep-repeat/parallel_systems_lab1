#include <spin_barrier.h>

/************************
 * Your code here...    *
 * or wherever you like *
 ************************/
uint spin_barrier::counter = 0;
pthread_mutex_t spin_barrier::mutex = PTHREAD_MUTEX_INITIALIZER;
spin_barrier::spin_barrier(int num_threads): m_num_threads(num_threads){
}
void spin_barrier::wait(int id){

    pthread_mutex_lock(&mutex);
    counter++;
    pthread_mutex_unlock(&mutex);
    while(counter<m_num_threads*id);
}
