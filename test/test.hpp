/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:36:11 by chanhpar          #+#    #+#             */
/*   Updated: 2023/01/14 16:47:34 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_TEST_HPP
#define FT_CONTAINERS_TEST_HPP

#include <iostream>
#include "TestClass.hpp"
#include "TestMap.hpp"
#include "TestSet.hpp"
#include "TestStack.hpp"
#include "TestVector.hpp"

template <typename T>
void
TEST_OTHERS(void) {
}

template <typename T>
void
TEST(void) {
  TEST_VECTOR<T>();
  TEST_STACK<T>();
  TEST_MAP<T>();
  TEST_SET<T>();
  TEST_OTHERS<T>();
}

#endif  // FT_CONTAINERS_TEST_HPP
