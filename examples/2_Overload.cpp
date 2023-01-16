#include <iostream>

template <typename T>
class A {
  T val;
};

template <typename T>
class B : public A<T> {};

template <typename T>
class C : public B<T> {};

// Deduction using upcasting
template <typename T>
void
print(A<T>) {
  std::cout << "print A" << std::endl;
}

template <typename T>
void
print(B<T>) {
  std::cout << "print B" << std::endl;
}

template <typename T>
void
print(C<T>) {
  std::cout << "print C" << std::endl;
}

int
main(void) {
  A<int> a;
  B<int> b;
  C<int> c;
  print(a);
  print(b);
  print(c);
  return (0);
}
