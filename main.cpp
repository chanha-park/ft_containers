#include <iostream>
#include <vector>
#include "vector.hpp"

void f(void) {
  std::vector<int> orig;
  ft::vector<int> v;

  for (int i = 0; i < 100; i++) {
    orig.push_back(2 * i);
  }

  v.insert(v.begin(), orig.begin(), orig.end());
  std::cout << v.size() << std::endl;
  std::cout << v.capacity() << std::endl;

  std::cout << "================" << std::endl;

  // compile error
  for (ft::vector<int>::const_reverse_iterator it = v.rbegin(); it != v.rend();
       ++it) {
    std::cout << "i: " << (it - v.rbegin()) << " " << *it << std::endl;
  }
}

int main(void) {
  f();
  return (0);
}
