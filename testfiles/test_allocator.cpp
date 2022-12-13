#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

struct A {
  int* val;

  A(void) : val(new int) {
    std::cout << "A ctor" << std::endl;
  }

  ~A(void) {
    std::cout << "A dtor" << std::endl;
    delete val;
  }
};

template <typename T>
void
printType(void) {
  std::cout << "Other type" << std::endl;
}

template <>
void
printType<int>(void) {
  std::cout << "type: int" << std::endl;
}

template <>
void
printType<std::string>(void) {
  std::cout << "type: std string" << std::endl;
}

template <>
void
printType<A>(void) {
  std::cout << "type: custom class A" << std::endl;
}

template <>
void
printType<std::vector<std::string> >(void) {
  std::cout << "type: vector of std string" << std::endl;
}

template <typename T>
void
fn(T* p) {
  printType<T>();
  (*p).~T();
}

template <typename T>
void
f(void) {
  std::allocator<T> alloc;
  T* a = new T;
  alloc.destroy(a);
  // fn(a);
  alloc.deallocate(a, 1);
  // delete a;
}

int
main(void) {
  f<int>();
  f<std::string>();
  f<std::vector<std::string> >();
  f<A>();
  system("leaks $PPID");
  return (0);
}
