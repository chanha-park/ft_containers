/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:06:47 by chanhpar          #+#    #+#             */
/*   Updated: 2023/01/16 17:40:43 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_TEST_VECTOR_HPP
#define FT_CONTAINERS_TEST_VECTOR_HPP

#include "test_common.hpp"

template <typename T>
void
test_vector(void) {
  NAMESPACE::vector<T> vec1;
  {
    // constructor
    NAMESPACE::vector<T> vec2(vec1.begin(), vec1.end());
    NAMESPACE::vector<T> vec3(std::size_t(COUNT) / 128, T(rand()));

    // push_back, const_reverse_iterator, rbegin, rend
    for (typename NAMESPACE::vector<T>::const_reverse_iterator it
         = vec3.rbegin();
         it != vec3.rend();
         ++it) {
      vec1.push_back(*it);
    }

    // operator=
    vec1 = vec3;

    // insert(pos, val), erase(pos), begin, end
    for (typename NAMESPACE::vector<T>::const_iterator it = vec1.begin();
         it != vec1.end();
         ++it) {
      vec2.insert(vec2.end(), T(rand()));
      vec3.erase(vec3.begin());
    }

    // swap
    vec1.swap(vec2);
    NAMESPACE::swap(vec2, vec3);

    test::print(vec1);
    test::print(vec2);
    test::print(vec3);
  }
  {
    // constructor
    NAMESPACE::vector<T> vec2(vec1.begin(), vec1.end());
    NAMESPACE::vector<T> vec3;

    // assign
    vec3.assign(vec2.rbegin(), vec2.rend());
    vec2.assign(std::size_t(COUNT) / 128, T(rand()));

    test::print(vec2);
    test::print(vec3);

    // at
    try {
      for (int i = 10; i > -5; --i) {
        std::cout << vec1.at(std::size_t(i));
      }
    } catch (std::out_of_range& e) {
      std::cout << "out_of_range exception" << std::endl;
    }

    // front, back
    std::cout << vec3.front() << vec3.back();
    vec2.front() = T(rand());

    // max_size
    std::cout << vec1.max_size();

    // empty, pop_back
    while (!vec1.empty())
      vec1.pop_back();

    // swap
    NAMESPACE::swap(vec1, vec3);

    // size, capacity
    if (vec1.size() < vec1.capacity())
      std::cout << Error_MSG << std::endl;

    // clear, resize
    vec1.clear();
    vec1.resize(std::size_t(rand() % 10 + 20), T(rand()));

    test::print(vec1);
    test::print(vec2);
    test::print(vec3);

    // relational operator
    std::cout << (vec1 == vec3) << (vec3 == vec3) << (vec1 < vec2);
  }
}

#endif  // FT_CONTAINERS_TEST_VECTOR_HPP
