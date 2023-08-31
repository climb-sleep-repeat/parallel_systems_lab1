#ifndef _SPIN_BARRIER_H
#define _SPIN_BARRIER_H

#include <pthread.h>
#include <iostream>
#include <helpers.h>

class spin_barrier {
public:
  spin_barrier(int num_threads);
  void wait(int id);
private:  
  int m_num_threads;
  static pthread_mutex_t mutex;
  static u_int counter;
};



#endif
