#include <iostream>
#include "type_traits.hpp"

template <typename T>
typename ft::enable_if<ft::is_integral<T>::value, void>::type ft_is_integral(
    T& t) {
  std::cout << "this is integral " << t << std::endl;
}

template <typename T>
typename ft::enable_if<!ft::is_integral<T>::value, void>::type ft_is_integral(
    T& t) {
  (void)t;
  std::cout << "this is non-integral " << std::endl;
}

// template <typename T>
// typename ft::enable_if<std::is_floating_point<T>::value, void>::type
// do_stuff(
//     T& t) {
//   std::cout << "do_stuff float " << t << std::endl;
// }

// template <typename T>
// typename ft::enable_if<std::is_class<T>::value, void>::type do_stuff(T& t) {
//   (void)t;
//   std::cout << "do_stuff else " << std::endl;
// }

class A {
 private:
 public:
};

struct B {};

int main(void) {
  int a = 3;
  float b = 2.3;
  A aa;

  ft_is_integral(a);
  ft_is_integral(b);
  ft_is_integral(aa);

  if (ft::is_integral<int>::value)
    std::cout << "int is integral" << std::endl;
  else
    std::cout << "int is not integral" << std::endl;
  return (0);
}
