#include <spin_barrier.h>
/************************
 * Your code here...    *
 * or wherever you like *
 ************************/
using namespace std;

int spin_barrier::counter = 0;
int spin_barrier::go = 0;

//extern pthread_barrier_t pb;
spin_barrier::spin_barrier(int num_threads): m_num_threads(num_threads){
}
void spin_barrier::wait(){
    //pthread_barrier_wait(&pb);
    __sync_fetch_and_add(&counter, 1);
    m_counter = counter;
    m_go = go;
    if(m_counter+1 == m_num_threads){
        counter = 0;
        go = 1-go;
    }
    else
        while(m_go != go);
}
