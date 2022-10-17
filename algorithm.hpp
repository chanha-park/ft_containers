/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:38:22 by chanhpar          #+#    #+#             */
/*   Updated: 2022/10/17 18:39:59 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_ALGORITHM_HPP
#define FT_CONTAINERS_ALGORITHM_HPP

#include "iterator.hpp"
#include "type_traits.hpp"

namespace ft {

// struct pair : WIP {{{

template <class T1, class T2>
struct pair {
  typedef T1 first_type;
  typedef T2 second_type;

  T1 first;
  T2 second;

  pair(const pair&) = default;
  pair(pair&&) = default;
  explicit(see - below) constexpr pair();
  explicit(see - below) pair(const T1& x, const T2& y);  // constexpr in C++14
  template <class U, class V>
  explicit(see - below) pair(U&& x, V&& y);  // constexpr in C++14
  template <class U, class V>
  explicit(see - below) pair(const pair<U, V>& p);  // constexpr in C++14
  template <class U, class V>
  explicit(see - below) pair(pair<U, V>&& p);  // constexpr in C++14
  template <class... Args1, class... Args2>
  pair(piecewise_construct_t,
       tuple<Args1...> first_args,
       tuple<Args2...> second_args);

  template <class U, class V>
  pair& operator=(const pair<U, V>& p);
  pair& operator=(pair&& p) noexcept(is_nothrow_move_assignable<T1>::value&&
                                         is_nothrow_move_assignable<T2>::value);
  template <class U, class V>
  pair& operator=(pair<U, V>&& p);

  void swap(pair& p) noexcept(
      is_nothrow_swappable_v<T1>&& is_nothrow_swappable_v<T2>);
};

// struct pair : WIP }}}

// mismatch, equal, lexicographical_compare {{{

template <typename InputIter1, typename InputIter2, typename BinaryPred>
ft::pair<InputIter1, InputIter2> mismatch(InputIter1 first1,
                                          InputIter1 last1,
                                          InputIter2 first2,
                                          BinaryPred pred) {
  while (first1 != last1 && pred(*first1, *first2)) {
    ++first1;
    ++first2;
  }
  return (ft::pair<InputIter1, InputIter2>(first1, first2));
}

template <typename InputIter1, typename InputIter2>
ft::pair<InputIter1, InputIter2> mismatch(InputIter1 first1,
                                          InputIter1 last1,
                                          InputIter2 first2) {
  while (first1 != last1 && (*first1 == *first2)) {
    ++first1;
    ++first2;
  }
  return (ft::pair<InputIter1, InputIter2>(first1, first2));
}

template <typename InputIter1, typename InputIter2, typename BinaryPred>
bool equal(InputIter1 first1,
           InputIter1 last1,
           InputIter2 first2,
           BinaryPred pred) {
  for (; first1 != last1; ++first1, ++first2)
    if (!pred(*first1, *first2))
      return (false);
  return (true);
}

template <typename InputIter1, typename InputIter2>
bool equal(InputIter1 first1, InputIter1 last1, InputIter2 first2) {
  for (; first1 != last1; ++first1, ++first2)
    if (!(*first1 == *first2))
      return (false);
  return (true);
}

template <typename InputIter1, typename InputIter2, typename Compare>
bool lexicographical_compare(InputIter1 first1,
                             InputIter1 last1,
                             InputIter2 first2,
                             InputIter2 last2,
                             Compare comp) {
  for (; first2 != last2; ++first1, ++first2) {
    if (first1 == last1 || comp(*first1, *first2))
      return (true);
    if (comp(*first2, *first1))
      return (false);
  }
  return (false);
}

template <typename InputIter1, typename InputIter2>
bool lexicographical_compare(InputIter1 first1,
                             InputIter1 last1,
                             InputIter2 first2,
                             InputIter2 last2) {
  for (; first2 != last2; ++first1, ++first2) {
    if (first1 == last1 || *first1 < *first2)
      return (true);
    if (*first2 < *first1)
      return (false);
  }
  return (false);
}

// mismatch, equal, lexicographical_compare }}}

}  // namespace ft

#endif  // FT_CONTAINERS_ALGORITHM_HPP
