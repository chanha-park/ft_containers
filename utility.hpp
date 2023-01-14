/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 19:20:01 by chanhpar          #+#    #+#             */
/*   Updated: 2023/01/14 22:39:57 by chanhpar         ###   ########.fr       */
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

template <typename Arg, typename Result>
struct unary_function {
  typedef Arg argument_type;
  typedef Result result_type;
};

template <typename Arg1, typename Arg2, typename Result>
struct binary_function {
  typedef Arg1 first_argument_type;
  typedef Arg2 second_argument_type;
  typedef Result result_type;
};

namespace detail {

// struct for functor {{{

template <typename T>
struct functor_identity__ : public ft::unary_function<T, T> {
  T&
  operator()(T& x) const {
    return (x);
  }

  const T&
  operator()(const T& x) const {
    return (x);
  }
};

template <typename Pair>
struct functor_first__ :
    public ft::unary_function<Pair, typename Pair::first_type> {
  typename Pair::first_type&
  operator()(Pair& x) const {
    return (x.first);
  }

  const typename Pair::first_type&
  operator()(const Pair& x) const {
    return (x.first);
  }
};

template <typename Pair>
struct functor_second__ :
    public ft::unary_function<Pair, typename Pair::second_type> {
  typename Pair::second_type&
  operator()(Pair& x) const {
    return (x.second);
  }

  const typename Pair::second_type&
  operator()(const Pair& x) const {
    return (x.second);
  }
};

// struct for functor }}}

}  // namespace detail

}  // namespace ft

#endif  // FT_CONTAINERS_UTILITY_HPP
