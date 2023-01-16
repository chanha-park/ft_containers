/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:36:11 by chanhpar          #+#    #+#             */
/*   Updated: 2023/01/16 17:40:17 by chanhpar         ###   ########.fr       */
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
  test_vector<T>();
  test_stack<T>();
  test_map<T>();
  test_set<T>();
  test_others<T>();
}

#endif  // FT_CONTAINERS_TEST_HPP
