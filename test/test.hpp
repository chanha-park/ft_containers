/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:36:11 by chanhpar          #+#    #+#             */
/*   Updated: 2023/01/17 21:49:23 by chanhpar         ###   ########.fr       */
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
TEST(void) {
  std::cout << "=====Test Vector=====" << std::endl;
  try {
    test_vector<T>();
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }
  std::cout << "=====Test Stack=====" << std::endl;
  try {
    test_stack<T>();
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }
  std::cout << "=====Test Map=====" << std::endl;
  try {
    test_map<T>();
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }
  std::cout << "=====Test Set=====" << std::endl;
  try {
    test_set<T>();
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }
}

template <>
void
TEST<int>(void) {
  std::cout << "=====Test Vector=====" << std::endl;
  test_vector<int>();
  std::cout << "=====Test Stack=====" << std::endl;
  test_stack<int>();
  std::cout << "=====Test Map=====" << std::endl;
  test_map<int>();
  std::cout << "=====Test Set=====" << std::endl;
  test_set<int>();
}

#endif  // FT_CONTAINERS_TEST_HPP
