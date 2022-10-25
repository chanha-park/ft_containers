#include <iostream>
#include "vector.hpp"

void f(void) {
  ft::vector<int> v;

  for (int i = 0; i < 10; i++) {
    v.push_back(2 * i);
  }

  std::cout << v.size() << std::endl;
  std::cout << v.capacity() << std::endl;

  std::cout << "================" << std::endl;

  // for (ft::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
  //   std::cout << "i: " << (v.end() - it) << " " << *it << std::endl;
  //   std::cout << "i: " << (it - v.begin()) << " " << *it << std::endl;
  // }

  // for (ft::vector<int>::reverse_iterator it = v.rbegin(); it != v.rend();
  //      ++it) {
  //   std::cout << "i: " << (v.rend() - it) << " " << *it << std::endl;
  //   std::cout << "i: " << (it - v.rbegin()) << " " << *it << std::endl;
  // }

  // compile error

  for (ft::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
    std::cout << "i: " << (v.end() - it) << " " << *it << std::endl;
    std::cout << "i: " << (it - v.begin()) << " " << *it << std::endl;
  }

  for (ft::vector<int>::const_reverse_iterator it = v.rbegin(); it != v.rend();
       ++it) {
    std::cout << "i: " << (v.rend() - it) << " " << *it << std::endl;
    std::cout << "i: " << (it - v.rbegin()) << " " << *it << std::endl;
  }
}

int main(void) {
  f();
  return (0);
}
