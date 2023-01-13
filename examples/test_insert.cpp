#include <sys/time.h>
#include <iostream>
#include <string>
#include <vector>
#include "vector.hpp"

#define NUM 10000

long
getTime(void) {
  static struct timeval now;
  gettimeofday(&now, NULL);
  return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

long timeStart, timeEnd;

int
main(void) {
  ft::vector<std::string> v1(NUM, "foo");
  std::vector<std::string> v2(NUM, "foo");

  timeStart = getTime();
  v1.insert(v1.begin() + 1, NUM, "bar");
  for (int i = 0; i < NUM; ++i)
    v1.insert(v1.begin() + NUM, "bar");
  timeEnd = getTime();
  std::cout << "ft: " << timeEnd - timeStart << "ms" << std::endl;

  timeStart = getTime();
  v2.insert(v2.begin() + 1, NUM, "bar");
  for (int i = 0; i < NUM; ++i)
    v2.insert(v2.begin() + NUM, "bar");
  timeEnd = getTime();
  std::cout << "std: " << timeEnd - timeStart << "ms" << std::endl;

  std::vector<std::string> result1(v1.begin(), v1.end());
  std::vector<std::string> result2(v2.begin(), v2.end());

  if (result1 == result2)
    std::cout << "SAME" << std::endl;
  else
    std::cout << "DIFF" << std::endl;
  return (0);
}
