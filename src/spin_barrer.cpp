#include <spin_barrier.h>
#include <cstring>
/************************
 * Your code here...    *
 * or wherever you like *
 ************************/
using namespace std;

int spin_barrier::counter = 0;
int * spin_barrier::go = NULL;

//extern pthread_barrier_t pb;
spin_barrier::spin_barrier(int num_threads): m_num_threads(num_threads){
}
void spin_barrier::setup(){
    go=new int[m_num_threads];
    memset(go,0,m_num_threads);
}
void spin_barrier::wait(int id){
    //pthread_barrier_wait(&pb);
    __sync_fetch_and_add(&counter, 1);
    m_counter = counter;
    m_go = go[id];
    if(m_counter+1 == m_num_threads){
        counter = 0;
        for(int i=m_num_threads-1; i>=0;i--){
            go[i] = 1-go[i];
        }
    }   
    else
        while(m_go != go[id]);
}
