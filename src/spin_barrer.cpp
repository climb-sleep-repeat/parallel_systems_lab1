#include <spin_barrier.h>
#include <cstring>
#include <pthread.h>

/************************
 * Your code here...    *
 * or wherever you like *
 ************************/
using namespace std;

atomic<int> spin_barrier::counter{};
sem_t spin_barrier::arrival_sem;
sem_t spin_barrier::departure_sem;

void spin_barrier::setup(){
    sem_init(&arrival_sem, 0, 1);
    sem_init(&departure_sem, 0, 0);
}
void spin_barrier::wait(int id){
    sem_wait(&arrival_sem);
    if(++counter < m_num_threads){
        sem_post(&arrival_sem);
    } else {
        sem_post(&departure_sem);
    }
    sem_wait(&departure_sem);
    if(--counter > 0){
        sem_post(&departure_sem);
    }else{
        sem_post(&arrival_sem);
    }
}
    /// m_counter = counter++;
    // m_go = go;
    // if(m_counter+1 >= m_num_threads){
    //     counter = 0;
    //     go = 1-go;
    // }   
    // else
    //     while(m_go == go);
//}
