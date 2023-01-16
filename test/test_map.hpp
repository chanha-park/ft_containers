/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:06:47 by chanhpar          #+#    #+#             */
/*   Updated: 2023/01/16 21:14:36 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_TEST_MAP_HPP
#define FT_CONTAINERS_TEST_MAP_HPP

#include "test_common.hpp"

template <typename T>
void
test_map(void) {
  NAMESPACE::map<T, int> m1;
  {
    // constructor
    NAMESPACE::map<T, int> m2(m1.begin(), m1.end());
    NAMESPACE::map<T, int> m3;

    for (int i = 0; i < 1000; ++i) {
      m3[T(i)] = rand();
    }

    // insert(val), const_reverse_iterator, rbegin, rend
    for (typename NAMESPACE::map<T, int>::const_reverse_iterator it
         = m3.rbegin();
         it != m3.rend();
         ++it) {
      m1.insert(*it);
    }

    // operator=
    m2 = m3;

    // insert(pos, val), erase(pos), begin, end
    for (typename NAMESPACE::map<T, int>::const_iterator it = m1.begin();
         it != m1.end();
         ++it) {
      int a = rand();
      int b = rand();
      m2.insert(m2.end(), NAMESPACE::make_pair(T(a), b));
      m3.erase(m3.begin());
    }

    // swap
    m1.swap(m2);
    NAMESPACE::swap(m2, m3);

    test::print(m1);
    test::print(m2);
    test::print(m3);
    test::tree_verify(m1);
    test::tree_verify(m2);
    test::tree_verify(m3);
  }
  {
    // constructor
    NAMESPACE::map<T, int> m2(m1.begin(), m1.end());
    NAMESPACE::map<T, int> m3;

    test::print(m2);
    test::print(m3);
    test::tree_verify(m1);
    test::tree_verify(m2);
    test::tree_verify(m3);

    // at
    try {
      for (int i = 10; i > -5; --i) {
        std::cout << m1.at(std::size_t(i));
      }
    } catch (std::out_of_range& e) {
      std::cout << "out_of_range exception" << std::endl;
    }

    // []
    for (int i = 0; i < 100; ++i) {
      m1[T(rand() % 10)] = i;
      std::cout << m1.count(T(i));
      if (m1.find(T(rand() % 2000)) == m1.end())
        std::cout << "Found";
      else
        std::cout << "NoElem";
    }

    // max_size
    std::cout << m1.max_size();

    // empty, erase
    while (!m1.empty())
      m1.erase(m1.begin());

    // swap
    NAMESPACE::swap(m1, m3);

    // clear, resize
    m1.clear();

    // equal_range
    for (int i = 0; i < 100; ++i) {
      NAMESPACE::pair<typename NAMESPACE::map<T, int>::iterator,
                      typename NAMESPACE::map<T, int>::iterator>
          p = m2.equal_range(T(rand()));
      for (typename NAMESPACE::map<T, int>::const_iterator it = p.first;
           it != p.second;
           ++it) {
        std::cout << it->first << it->second;
      }
    }

    // lower_bound
    for (int i = 0; i < 100; ++i) {
      typename NAMESPACE::map<T, int>::iterator p = m2.lower_bound(T(rand()));
      if (p == m2.end())
        std::cout << "NoElem";
      else
        std::cout << p->first << p->second;
    }

    // upper_bound
    for (int i = 0; i < 100; ++i) {
      typename NAMESPACE::map<T, int>::iterator p = m2.upper_bound(T(rand()));
      if (p == m2.end())
        std::cout << "NoElem";
      else
        std::cout << p->first << p->second;
    }

    test::print(m1);
    test::print(m2);
    test::print(m3);
    test::tree_verify(m1);
    test::tree_verify(m2);
    test::tree_verify(m3);

    // relational operator
    std::cout << (m1 == m3) << (m3 == m3) << (m1 < m2);
  }
}

#endif  // FT_CONTAINERS_TEST_MAP_HPP
