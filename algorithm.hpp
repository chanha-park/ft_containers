/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:38:22 by chanhpar          #+#    #+#             */
/*   Updated: 2022/10/18 12:24:21 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_ALGORITHM_HPP
#define FT_CONTAINERS_ALGORITHM_HPP

#include "iterator.hpp"
#include "type_traits.hpp"

namespace ft {

// struct pair : WIP {{{

template <typename T1, typename T2>
struct pair {
  typedef T1 first_type;
  typedef T2 second_type;

  T1 first;
  T2 second;

  pair(void) : first(), second() {
  }

  pair(const pair& p) : first(p.first), second(p.second) {
  }

  template <typename U, typename V>
  pair(const pair<U, V>& p) : first(p.first), second(p.second) {
  }

  pair(const T1& x, const T2& y) : first(x), second(y) {
  }

  pair& operator=(const pair& p) {
    first = p.first;
    second = p.second;
    return (*this);
  }
};

// struct pair : WIP }}}

// pair: relational opeartors {{{

template <typename T1, typename T2>
bool operator==(const ft::pair<T1, T2>& x, const ft::pair<T1, T2>& y) {
  return (x.first == y.first && x.second == y.second);
}

template <typename T1, typename T2>
bool operator<(const ft::pair<T1, T2>& x, const ft::pair<T1, T2>& y) {
  return (x.first < y.first || (!(y.first < x.first) && x.second < y.second));
}

template <typename T1, typename T2>
bool operator!=(const ft::pair<T1, T2>& x, const ft::pair<T1, T2>& y) {
  return (!(x == y));
}

template <typename T1, typename T2>
bool operator>(const ft::pair<T1, T2>& x, const ft::pair<T1, T2>& y) {
  return (y < x);
}

template <typename T1, typename T2>
bool operator<=(const ft::pair<T1, T2>& x, const ft::pair<T1, T2>& y) {
  return (!(y < x));
}

template <typename T1, typename T2>
bool operator>=(const ft::pair<T1, T2>& x, const ft::pair<T1, T2>& y) {
  return (!(x < y));
}

// pair: relational opeartors }}}

// make_pair {{{

template <typename T1, typename T2>
ft::pair<T1, T2> make_pair(T1 x, T2 y) {
  return (ft::pair<T1, T2>(x, y));
}

// make_pair }}}

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
