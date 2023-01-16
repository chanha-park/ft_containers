/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stack.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:06:47 by chanhpar          #+#    #+#             */
/*   Updated: 2023/01/16 23:03:56 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_TEST_STACK_HPP
#define FT_CONTAINERS_TEST_STACK_HPP

#include "test_common.hpp"

template <typename T>
void
test_stack(void) {
  NAMESPACE::vector<T> vec;
  NAMESPACE::stack<T, NAMESPACE::vector<T> > st1;

  for (int i = 0; i < 1000; ++i) {
    vec.insert(vec.begin() + (vec.end() - vec.begin()) / 2, i, T(rand()));
  }
  NAMESPACE::stack<T, NAMESPACE::vector<T> > st2(vec);

  st1 = st2;

  while (!st2.empty()) {
    std::cout << st2.top();
    std::cout << st2.size();
    st2.pop();
  }

  while (!st1.empty()) {
    st2.push(st1.top());
    std::cout << st2.top();
    st1.pop();
  }
}

#endif  // FT_CONTAINERS_TEST_STACK_HPP
