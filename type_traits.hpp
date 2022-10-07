/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 09:49:23 by chanhpar          #+#    #+#             */
/*   Updated: 2022/10/07 10:12:18 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_TYPE_TRAITS_HPP
#define FT_CONTAINERS_TYPE_TRAITS_HPP

// enable_if {{{

template <bool, typename T = void>
struct enable_if {};

template <typename T>
struct enable_if<true, T> {
  typedef T type;
};

// enable_if }}}

template <class T, T v>
struct integral_constant {
  static const T value = v;
  typedef T value_type;
  typedef integral_constant type;

  operator value_type() const throw() {
    return value;
  }
};

typedef integral_constant<bool, (true)> true_type;
typedef integral_constant<bool, (false)> false_type;

// is_integral {{{

template <class _Tp>
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

#ifndef _LIBCPP_NO_HAS_CHAR8_T
template <>
struct is_integral_internal<char8_t> : public true_type {};
#endif

#ifndef _LIBCPP_HAS_NO_UNICODE_CHARS
template <>
struct is_integral_internal<char16_t> : public true_type {};

template <>
struct is_integral_internal<char32_t> : public true_type {};
#endif  // _LIBCPP_HAS_NO_UNICODE_CHARS

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

#ifndef _LIBCPP_HAS_NO_INT128
template <>
struct is_integral_internal<__int128_t> : public true_type {};

template <>
struct is_integral_internal<__uint128_t> : public true_type {};
#endif  //_LIBCPP_HAS_NO_INT128

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_integral :
    public is_integral_internal<typename remove_cv<_Tp>::type> {};

// is_integral }}}

#endif  // FT_CONTAINERS_TYPE_TRAITS_HPP
