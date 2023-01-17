/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 19:09:39 by chanhpar          #+#    #+#             */
/*   Updated: 2023/01/17 19:31:09 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_STACK_HPP
#define FT_CONTAINERS_STACK_HPP

#include "vector.hpp"

namespace ft {

template <typename T, typename Container = ft::vector<T> >
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
    this->c = other.c;
    return (*this);
  }

  bool
  empty(void) const {
    return (this->c.empty());
  }

  size_type
  size(void) const {
    return (this->c.size());
  }

  reference
  top(void) {
    return (this->c.back());
  }

  const_reference
  top(void) const {
    return (this->c.back());
  }

  void
  push(const value_type& x) {
    this->c.push_back(x);
  }

  void
  pop(void) {
    this->c.pop_back();
  }

  bool
  operator==(const stack<T, Container>& other) const {
    return (this->c == other.c);
  }

  bool
  operator<(const stack<T, Container>& other) const {
    return (this->c < other.c);
  }

  bool
  operator!=(const stack<T, Container>& other) const {
    return (!(*this == other));
  }

  bool
  operator>(const stack<T, Container>& other) const {
    return (other < *this);
  }

  bool
  operator<=(const stack<T, Container>& other) const {
    return (!(other < *this));
  }

  bool
  operator>=(const stack<T, Container>& other) const {
    return (!(*this < other));
  }

};  // class stack

}  // namespace ft

#endif  // FT_CONTAINERS_STACK_HPP
