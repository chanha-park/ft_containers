/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:36:11 by chanhpar          #+#    #+#             */
/*   Updated: 2023/01/13 17:06:22 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_TEST_HPP
#define FT_CONTAINERS_TEST_HPP

#include <iostream>
#include "TestClass.hpp"
#include "TestVector.hpp"
#include "TestStack.hpp"
#include "TestMap.hpp"
#include "TestSet.hpp"

void
TEST_VECTOR(void) {
  TEST_VECTOR_TYPE<int>();
  TEST_VECTOR_TYPE<std::string>();
  TEST_VECTOR_TYPE<NormalClass>();
  TEST_VECTOR_TYPE<NoDefaultCtor>();
  try {
    TEST_VECTOR_TYPE<AssignException>();
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }
  try {
    TEST_VECTOR_TYPE<CopyException>();
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }
  // TEST_VECTOR_OTHER();
}

void
TEST_STACK(void) {
  TEST_STACK_TYPE<int>();
  TEST_STACK_TYPE<std::string>();
  TEST_STACK_TYPE<NormalClass>();
  TEST_STACK_TYPE<NoDefaultCtor>();
  TEST_STACK_TYPE<AssignException>();
  TEST_STACK_TYPE<CopyException>();
  // TEST_STACK_OTHER();
}

void
TEST_MAP(void) {
  TEST_MAP_TYPE<int>();
  TEST_MAP_TYPE<std::string>();
  TEST_MAP_TYPE<NormalClass>();
  TEST_MAP_TYPE<NoDefaultCtor>();
  TEST_MAP_TYPE<AssignException>();
  TEST_MAP_TYPE<CopyException>();
  // TEST_MAP_OTHER();
}

void
TEST_SET(void) {
  TEST_SET_TYPE<int>();
  TEST_SET_TYPE<std::string>();
  TEST_SET_TYPE<NormalClass>();
  TEST_SET_TYPE<NoDefaultCtor>();
  TEST_SET_TYPE<AssignException>();
  TEST_SET_TYPE<CopyException>();
  // TEST_SET_OTHER();
}

void
TEST_OTHERS(void) {
}

#endif  // FT_CONTAINERS_TEST_HPP
