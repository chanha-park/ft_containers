#include <iostream>
#include <string>

namespace example {

template <typename T>
void
swap(T& a, T& b) {
  const T tmp(a);
  a = b;
  b = tmp;
}

}  // namespace example

template <typename T>
struct A {
  T arr[100];
  int idx;

  A(void) : idx(0) {
  }

  void
  push(T val) {
    arr[idx++] = val;
  }

  T
  pop(void) {
    return (arr[--idx]);
  }
};

int
main(void) {
  {
    int a = 3;
    int b = 4;

    example::swap(a, b);

    std::cout << a << std::endl;
    std::cout << b << std::endl;
  }
  {
    std::string a = "hello";
    std::string b = "world";

    example::swap(a, b);

    std::cout << a << std::endl;
    std::cout << b << std::endl;
  }
  {
    A<int> int_stack;
    A<double> double_stack;

    int_stack.push(3);
    std::cout << int_stack.pop() << std::endl;
    double_stack.push(3.2);
    std::cout << double_stack.pop() << std::endl;
  }
  return (0);
}
