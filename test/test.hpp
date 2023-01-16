/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:36:11 by chanhpar          #+#    #+#             */
/*   Updated: 2023/01/16 18:44:02 by chanhpar         ###   ########.fr       */
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
  std::cerr << "=====Test Vector=====" << std::endl;
  test_vector<T>();
  std::cerr << "=====Test Stack=====" << std::endl;
  test_stack<T>();
  std::cerr << "=====Test Map=====" << std::endl;
  test_map<T>();
  std::cerr << "=====Test Set=====" << std::endl;
  test_set<T>();
  std::cerr << "=====Test Other=====" << std::endl;
  test_others<T>();
}

#endif  // FT_CONTAINERS_TEST_HPP
