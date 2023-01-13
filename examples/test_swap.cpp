#include <sys/time.h>
#include <iostream>
#include <vector>
#include "vector.hpp"

#define SIZE 100000000

time_t timer() {
  struct timeval start = {};
  gettimeofday(&start, nullptr);
  time_t msecs_time = (start.tv_sec * 1000) + (start.tv_usec / 1000);
  return msecs_time;
}

time_t start;
time_t end;

int main(void) {
  std::vector<int> v1(3, SIZE);
  std::vector<int> tmp1(4, SIZE / 2);
  ft::vector<int> v2(3, SIZE);
  ft::vector<int> tmp2(4, SIZE / 2);

  start = timer();
  for (int i = 0; i < SIZE; ++i) {
    v1.swap(tmp1);
  }
  end = timer();
  std::cout << end - start << std::endl;

  start = timer();
  for (int i = 0; i < SIZE; ++i) {
    v2.swap(tmp2);
  }
  end = timer();
  std::cout << end - start << std::endl;
  if (v1.size() == v2.size())
    return (0);
  else
    return (1);
}
