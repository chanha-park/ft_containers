#include <sys/time.h>
#include <iostream>
#include <vector>
#include "vector.hpp"

int _ratio = 1000;

time_t
timer() {
  struct timeval start = {};
  gettimeofday(&start, NULL);
  time_t msecs_time = (start.tv_sec * 1000) + (start.tv_usec / 1000);
  return (msecs_time);
}

long g_start1;
long g_end1;
long g_start2;
long g_end2;

template <typename T>
void
erase_test(std::vector<T>& v) {
  for (int i = 0; i < 9900 * _ratio; ++i)
    v.push_back(i);

  g_start1 = timer();
  for (int i = 0; i < _ratio; ++i)
    v.erase(v.begin() + 8 * _ratio);
  g_end1 = timer();
  std::cout << "std: " << g_end1 - g_start1 << "ms" << std::endl;
}

template <typename T>
void
erase_test(ft::vector<T>& v) {
  for (int i = 0; i < 9900 * _ratio; ++i)
    v.push_back(i);

  g_start2 = timer();
  for (int i = 0; i < _ratio; ++i)
    v.erase(v.begin() + 8 * _ratio);
  g_end2 = timer();
  std::cout << "ft: " << g_end2 - g_start2 << "ms" << std::endl;
}

int
main(void) {
  ft::vector<int> v1;
  std::vector<int> v2;
  erase_test<int>(v1);
  erase_test<int>(v2);
  return (0);
}
