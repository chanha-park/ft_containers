/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 09:49:23 by chanhpar          #+#    #+#             */
/*   Updated: 2022/10/08 14:32:06 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_TYPE_TRAITS_HPP
#define FT_CONTAINERS_TYPE_TRAITS_HPP

namespace ft {

// enable_if {{{

template <bool, typename T = void>
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
    return value;
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

// is_integral {{{

// is_integral_internal {{{

template <typename _Tp>
struct is_integral_internal : public false_type {};

template <>
struct is_integral_internal<bool> : public true_type {};

template <>
struct is_integral_internal<char> : public true_type {};

template <>
struct is_integral_internal<signed char> : public true_type {};

template <>
struct is_integral_internal<unsigned char> : public true_type {};

template <>
struct is_integral_internal<wchar_t> : public true_type {};

template <>
struct is_integral_internal<short> : public true_type {};

template <>
struct is_integral_internal<unsigned short> : public true_type {};

template <>
struct is_integral_internal<int> : public true_type {};

template <>
struct is_integral_internal<unsigned int> : public true_type {};

template <>
struct is_integral_internal<long> : public true_type {};

template <>
struct is_integral_internal<unsigned long> : public true_type {};

template <>
struct is_integral_internal<long long> : public true_type {};

template <>
struct is_integral_internal<unsigned long long> : public true_type {};

// is_integral_internal }}}

template <typename Tp>
struct is_integral :
    public ft::is_integral_internal<typename ft::remove_cv<Tp>::type> {};

// is_integral }}}

}  // namespace ft

#endif  // FT_CONTAINERS_TYPE_TRAITS_HPP
