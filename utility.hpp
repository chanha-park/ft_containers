/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 19:20:01 by chanhpar          #+#    #+#             */
/*   Updated: 2022/12/16 19:20:40 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_UTILITY_HPP
#define FT_CONTAINERS_UTILITY_HPP

namespace ft {

// struct pair {{{

template <typename T1, typename T2>
struct pair {
  typedef T1 first_type;
  typedef T2 second_type;

  T1 first;
  T2 second;

  pair(void) : first(), second() {
  }

  template <typename U, typename V>
  pair(const pair<U, V>& p) : first(p.first), second(p.second) {
  }

  pair(const T1& x, const T2& y) : first(x), second(y) {
  }

  pair&
  operator=(const pair& p) {
    first = p.first;
    second = p.second;
    return (*this);
  }
};

// struct pair }}}

// make_pair {{{

template <typename T1, typename T2>
ft::pair<T1, T2>
make_pair(T1 x, T2 y) {
  return (ft::pair<T1, T2>(x, y));
}

// make_pair }}}

}  // namespace ft

#endif  // FT_CONTAINERS_UTILITY_HPP
