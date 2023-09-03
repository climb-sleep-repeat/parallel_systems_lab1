#ifndef _SPIN_BARRIER_H
#define _SPIN_BARRIER_H

#include <pthread.h>
#include <iostream>
#include <helpers.h>
#include <atomic>
using namespace std;

class spin_barrier {
public:
  spin_barrier(int num_threads);
  void wait(int id);
  void setup();
private:  
  int m_num_threads;
  int m_counter;
  int m_go;
  static int counter;
  static int * go;

};



#endif
