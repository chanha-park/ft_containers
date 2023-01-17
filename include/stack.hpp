/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 19:09:39 by chanhpar          #+#    #+#             */
/*   Updated: 2023/01/14 22:48:04 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_STACK_HPP
#define FT_CONTAINERS_STACK_HPP

#include "vector.hpp"

namespace ft {

// forward declarations {{{

template <typename T, typename Container = ft::vector<T> >
class stack;

template <typename T, typename Container>
bool
operator==(const stack<T, Container>& x, const stack<T, Container>& y);

template <typename T, typename Container>
bool
operator<(const stack<T, Container>& x, const stack<T, Container>& y);

// forward declarations }}}

template <typename T, typename Container>
class stack {
 public:
  typedef Container container_type;
  typedef typename Container::value_type value_type;
  typedef typename Container::size_type size_type;
  typedef typename Container::reference reference;
  typedef typename Container::const_reference const_reference;

 private:
 protected:
  container_type c;

 public:
  explicit stack(const container_type& cntr = container_type()) : c(cntr) {
  }

  stack&
  operator=(const stack& other) {
    c = other.c;
    return (*this);
  }

  bool
  empty(void) const {
    return (c.empty());
  }

  size_type
  size(void) const {
    return (c.size());
  }

  reference
  top(void) {
    return (c.back());
  }

  const_reference
  top(void) const {
    return (c.back());
  }

  void
  push(const value_type& x) {
    c.push_back(x);
  }

  void
  pop(void) {
    c.pop_back();
  }

  template <typename T_, typename Container_>
  friend bool
  operator==(const stack<T_, Container_>& x, const stack<T_, Container_>& y);

  template <typename T_, typename Container_>
  friend bool
  operator<(const stack<T_, Container_>& x, const stack<T_, Container_>& y);
};  // class stack

// relational operator {{{

template <typename T, typename Container>
bool
operator==(const stack<T, Container>& x, const stack<T, Container>& y) {
  return (x.c == y.c);
}

template <typename T, typename Container>
bool
operator<(const stack<T, Container>& x, const stack<T, Container>& y) {
  return (x.c < y.c);
}

template <typename T, typename Container>
bool
operator!=(const stack<T, Container>& x, const stack<T, Container>& y) {
  return (!(x == y));
}

template <typename T, typename Container>
bool
operator>(const stack<T, Container>& x, const stack<T, Container>& y) {
  return (y < x);
}

template <typename T, typename Container>
bool
operator<=(const stack<T, Container>& x, const stack<T, Container>& y) {
  return (!(y < x));
}

template <typename T, typename Container>
bool
operator>=(const stack<T, Container>& x, const stack<T, Container>& y) {
  return (!(x < y));
}

// relational operator }}}

}  // namespace ft

#endif  // FT_CONTAINERS_STACK_HPP
