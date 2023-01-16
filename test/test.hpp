/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:36:11 by chanhpar          #+#    #+#             */
/*   Updated: 2023/01/16 22:31:17 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_TEST_HPP
#define FT_CONTAINERS_TEST_HPP

#include "test_map.hpp"
#include "test_set.hpp"
#include "test_stack.hpp"
#include "test_vector.hpp"

template <typename T>
void
test_others(void) {
}

template <typename T>
void
TEST(void) {
  std::cout << "=====Test Vector=====" << std::endl;
  test_vector<T>();
  std::cout << "=====Test Stack=====" << std::endl;
  test_stack<T>();
  std::cout << "=====Test Map=====" << std::endl;
  test_map<T>();
  std::cout << "=====Test Set=====" << std::endl;
  test_set<T>();
  std::cout << "=====Test Other=====" << std::endl;
  test_others<T>();
}

#endif  // FT_CONTAINERS_TEST_HPP
