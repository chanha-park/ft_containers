#include <iostream>
#include <vector>
#include "vector.hpp"

int _ratio = 1000;

template <typename T>
std::vector<int> resize_test(std::vector<T> vector) {
  std::vector<int> v;
  vector.assign(9900 * _ratio, 1);
  vector.resize(5000 * _ratio);
  vector.reserve(5000 * _ratio);
  v.push_back(vector.size());
  v.push_back(vector.capacity());
  vector.resize(7000 * _ratio);
  v.push_back(vector.size());
  v.push_back(vector.capacity());
  vector.resize(15300 * _ratio, T());
  v.push_back(vector.size());
  v.push_back(vector.capacity());
  v.push_back(vector[65]);
  return v;
}

template <typename T>
std::vector<int> resize_test(ft::vector<T> vector) {
  std::vector<int> v;
  vector.assign(9900 * _ratio, 1);
  vector.resize(5000 * _ratio);
  vector.reserve(5000 * _ratio);
  v.push_back(vector.size());
  v.push_back(vector.capacity());
  vector.resize(7000 * _ratio);
  v.push_back(vector.size());
  v.push_back(vector.capacity());
  vector.resize(15300 * _ratio, T());
  v.push_back(vector.size());
  v.push_back(vector.capacity());
  v.push_back(vector[65]);
  return v;
}

template <class T>
int run_vector_unit_test(std::string test_name,
                         std::vector<int>(func1)(std::vector<T>),
                         std::vector<int>(func2)(ft::vector<T>)) {
  int result;
  // int leaks;
  // time_t t1;
  // time_t t2;
  (void)test_name;
  std::vector<int> res1;
  std::vector<int> res2;
  std::vector<int> vector;
  ft::vector<int> my_vector;

  res1 = func1(vector);
  res2 = func2(my_vector);
  if (res1 == res2) {
    std::cout << "OK" << std::endl;
    result = 0;
  } else {
    std::cout << "FAIL" << std::endl;
    result = 1;
  }
  // leaks = leaks_test(getpid());
  std::cout << std::endl;

  return !(!result);
}

int main() {
  exit(run_vector_unit_test<int>("resize()", resize_test, resize_test));
}
