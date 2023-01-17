#include <iostream>

namespace example {

static const unsigned int mod = 1009;

template <unsigned int N>
struct Num {
  static const unsigned int value = N;
};

template <unsigned int A, unsigned int B>
struct Add {
  static const unsigned int value = Add<A - 1, B + 1>::value;
};

template <unsigned int B>
struct Add<0, B> {
  static const unsigned int value = Num<B>::value;
};

template <unsigned int N>
struct Fibo {
  static const unsigned int value
      = (Fibo<N - 1>::value + Fibo<N - 2>::value) % mod;
};

template <>
struct Fibo<1> {
  static const unsigned int value = 1;
};

template <>
struct Fibo<0> {
  static const unsigned int value = 0;
};

template <unsigned int N>
struct Facto {
  static const unsigned int value = (N * Facto<N - 1>::value) % mod;
};

template <>
struct Facto<0> {
  static const unsigned int value = 1;
};

}  // namespace example

int
main(void) {
  std::cout << example::Num<100>::value << std::endl;
  std::cout << example::Add<200, 300>::value << std::endl;
  std::cout << example::Fibo<10>::value << std::endl;
  std::cout << example::Fibo<100>::value << std::endl;
  std::cout << example::Facto<100>::value << std::endl;
  return (0);
}
