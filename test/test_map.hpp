/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:06:47 by chanhpar          #+#    #+#             */
/*   Updated: 2023/01/16 17:50:47 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_TEST_MAP_HPP
#define FT_CONTAINERS_TEST_MAP_HPP

#include "test_common.hpp"

template <typename T>
void
test_map(void) {
  NAMESPACE::map<T, NormalClass<T> > m1;
  {
    // constructor
    NAMESPACE::map<T, NormalClass<T> > m2(m1.begin(), m1.end());
    NAMESPACE::map<T, NormalClass<T> > m3;

    // insert(val), const_reverse_iterator, rbegin, rend
    for (typename NAMESPACE::map<T, NormalClass<T> >::const_reverse_iterator it
         = m3.rbegin();
         it != m3.rend();
         ++it) {
      m1.insert(*it);
    }

    // operator=
    m1 = m3;

    // insert(pos, val), erase(pos), begin, end
    for (typename NAMESPACE::map<T, NormalClass<T> >::const_iterator it
         = m1.begin();
         it != m1.end();
         ++it) {
      int a = rand();
      int b = rand();
      m2.insert(m2.end(), NAMESPACE::make_pair(T(a), NormalClass<T>(T(b))));
      m3.erase(m3.begin());
    }

    // swap
    m1.swap(m2);
    NAMESPACE::swap(m2, m3);

    test::print(m1);
    test::print(m2);
    test::print(m3);
  }
  {
    // constructor
    NAMESPACE::map<T, NormalClass<T> > m2(m1.begin(), m1.end());
    NAMESPACE::map<T, NormalClass<T> > m3;

    test::print(m2);
    test::print(m3);

    // at
    try {
      for (int i = 10; i > -5; --i) {
        std::cout << m1.at(std::size_t(i));
      }
    } catch (std::out_of_range& e) {
      std::cout << "out_of_range exception" << std::endl;
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

    test::print(m1);
    test::print(m2);
    test::print(m3);
	test::tree_verify(m3);

    // relational operator
    std::cout << (m1 == m3) << (m3 == m3) << (m1 < m2);
  }
}

#endif  // FT_CONTAINERS_TEST_MAP_HPP
