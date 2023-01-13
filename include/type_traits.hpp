/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 09:49:23 by chanhpar          #+#    #+#             */
/*   Updated: 2022/12/27 20:16:38 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_TYPE_TRAITS_HPP
#define FT_CONTAINERS_TYPE_TRAITS_HPP

#include <cstddef>

namespace ft {

// enable_if {{{

template <bool, typename T = void>
struct enable_if {};

template <typename T>
struct enable_if<true, T> {
  typedef T type;
};

// enable_if }}}

// conditional {{{

template <bool b, typename If, typename Else>
struct conditional {
  typedef If type;
};

template <typename If, typename Else>
struct conditional<false, If, Else> {
  typedef Else type;
};

// conditional }}}

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

// remove_const, volatile, cv {{{

template <typename T>
struct remove_const {
  typedef T type;
};

template <typename T>
struct remove_const<const T> {
  typedef T type;
};

template <typename T>
struct remove_volatile {
  typedef T type;
};

template <typename T>
struct remove_volatile<volatile T> {
  typedef T type;
};

template <typename T>
struct remove_cv {
  typedef typename ft::remove_volatile<typename ft::remove_const<T>::type>::type
      type;
};

// remove_const, volatile, cv }}}

// is_void {{{

template <typename T>
struct is_void_internal : public ft::false_type {};

template <>
struct is_void_internal<void> : public ft::true_type {};

template <typename T>
struct is_void :
    public ft::is_void_internal<typename ft::remove_cv<T>::type> {};

// is_void }}}

// is_integral {{{

// is_integral_internal {{{

template <typename T>
struct is_integral_internal : public ft::false_type {};

template <>
struct is_integral_internal<bool> : public ft::true_type {};

template <>
struct is_integral_internal<char> : public ft::true_type {};

template <>
struct is_integral_internal<signed char> : public ft::true_type {};

template <>
struct is_integral_internal<unsigned char> : public ft::true_type {};

template <>
struct is_integral_internal<wchar_t> : public ft::true_type {};

template <>
struct is_integral_internal<short> : public ft::true_type {};

template <>
struct is_integral_internal<unsigned short> : public ft::true_type {};

template <>
struct is_integral_internal<int> : public ft::true_type {};

template <>
struct is_integral_internal<unsigned int> : public ft::true_type {};

template <>
struct is_integral_internal<long> : public ft::true_type {};

template <>
struct is_integral_internal<unsigned long> : public ft::true_type {};

// template <>
// struct is_integral_internal<long long> : public ft::true_type {};

// template <>
// struct is_integral_internal<unsigned long long> : public ft::true_type {};

// is_integral_internal }}}

template <typename T>
struct is_integral :
    public ft::is_integral_internal<typename ft::remove_cv<T>::type> {};

// is_integral }}}

// is_floating_point {{{

template <typename T>
struct is_floating_point_internal : public ft::false_type {};

template <>
struct is_floating_point_internal<float> : public ft::true_type {};

template <>
struct is_floating_point_internal<double> : public ft::true_type {};

template <>
struct is_floating_point_internal<long double> : public ft::true_type {};

template <typename T>
struct is_floating_point :
    public ft::is_floating_point_internal<typename ft::remove_cv<T>::type> {};

// is_floating_point }}}

// is_arithmetic {{{

template <typename T>
struct is_arithmetic :
    public ft::integral_constant<bool,
                                 ft::is_integral<T>::value
                                     || ft::is_floating_point<T>::value> {};

// is_arithmetic }}}

// is_pointer {{{

template <typename T>
struct is_pointer_internal : public ft::false_type {};

template <typename T>
struct is_pointer_internal<T*> : public ft::true_type {};

template <typename T>
struct is_pointer :
    public ft::is_pointer_internal<typename ft::remove_cv<T>::type> {};

// is_pointer }}}

// is_reference {{{

template <typename T>
struct is_reference : public ft::false_type {};

template <typename T>
struct is_reference<T&> : public ft::true_type {};

// is_reference }}}

// is_array {{{

template <typename T>
struct is_array : public ft::false_type {};

template <typename T>
struct is_array<T[]> : public ft::true_type {};

template <typename T, size_t N>
struct is_array<T[N]> : public ft::true_type {};

// is_array }}}

// has_trivial_destructor {{{

template <typename T>
struct has_trivial_destructor :
    public ft::integral_constant<bool,
                                 ft::is_arithmetic<T>::value
                                     || ft::is_pointer<T>::value> {};

// has_trivial_destructor }}}

// is_same {{{

template <typename T, typename U>
struct is_same : ft::false_type {};

template <typename T>
struct is_same<T, T> : ft::true_type {};

// is_same }}}

}  // namespace ft

#endif  // FT_CONTAINERS_TYPE_TRAITS_HPP
