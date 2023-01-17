#include <iostream>

// Substitution Failure Is Not An Error

namespace example {

// enable_if {{{

template <bool, typename T>
struct enable_if {};

template <typename T>
struct enable_if<true, T> {
  typedef T type;
};

// enable_if }}}

// helper class: integral_constant, true_type, false_type {{{

template <typename T, T v>
struct integral_constant {
  static const T value = v;
  typedef T value_type;
  typedef integral_constant type;

  operator value_type() const throw() {
    return (value);
  }
};

typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

// helper class: integral_constant, true_type, false_type }}}

// is_same {{{

template <typename T, typename U>
struct is_same : example::false_type {};

template <typename T>
struct is_same<T, T> : example::true_type {};

// is_same }}}

}  // namespace example

template <typename T>
class A {
  T val;
};

template <typename T>
class B : public A<T> {};

template <typename T>
class C : public B<T> {};

template <typename T>
typename example::enable_if<example::is_same<A<int>, T>::value, void>::type
print(T k) {
  (void)k;
  std::cout << "Same with A<int>" << std::endl;
}

template <typename T>
typename example::enable_if<example::is_same<B<int>, T>::value, void>::type
print(T k) {
  (void)k;
  std::cout << "Same with B<int>" << std::endl;
}

template <typename T>
typename example::enable_if<example::is_same<C<int>, T>::value, void>::type
print(T k) {
  (void)k;
  std::cout << "Same with C<int>" << std::endl;
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
