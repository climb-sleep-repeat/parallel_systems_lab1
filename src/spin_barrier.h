#ifndef _SPIN_BARRIER_H
#define _SPIN_BARRIER_H

#include <pthread.h>
#include <iostream>
#include <helpers.h>
#include <atomic>
#include <semaphore.h>

using namespace std;

class spin_barrier {
public:
  spin_barrier(int num_threads) : m_num_threads(num_threads){}
  void wait(int id);
  static void setup();
private:  
  int m_num_threads;
  static atomic<int> counter;
  static sem_t arrival_sem;
  static sem_t departure_sem;
};



#endif
