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
  return (0);
}
