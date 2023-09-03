#include <spin_barrier.h>
#include <cstring>
#include <pthread.h>
/************************
 * Your code here...    *
 * or wherever you like *
 ************************/
using namespace std;

volatile atomic<int> spin_barrier::counter{};
volatile int spin_barrier::go = 0;

spin_barrier::spin_barrier(int num_threads): m_num_threads(num_threads){
}

void spin_barrier::wait(int id){
    m_counter = counter++;
    m_go = go;
    cout << m_counter << " " << counter << endl;
    if(m_counter+1 >= m_num_threads){
        counter = 0;
        go = 1-go;
    }   
    else
        while(m_go == go);
}
