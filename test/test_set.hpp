/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_set.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:06:47 by chanhpar          #+#    #+#             */
/*   Updated: 2023/01/16 22:46:18 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_TEST_SET_HPP
#define FT_CONTAINERS_TEST_SET_HPP

#include "test_common.hpp"

template <typename T>
void
test_set(void) {
  NAMESPACE::set<T> s1;
  {
    // constructor
    NAMESPACE::set<T> s2(s1.begin(), s1.end());
    NAMESPACE::set<T> s3;

    for (int i = 0; i < 1000; ++i) {
      s3.insert(T(rand()));
    }

    // insert(val), const_reverse_iterator, rbegin, rend
    for (typename NAMESPACE::set<T>::const_reverse_iterator it = s3.rbegin();
         it != s3.rend();
         ++it) {
      s1.insert(*it);
    }

    // operator=
    s2 = s3;

    // insert(pos, val), erase(pos), begin, end
    for (typename NAMESPACE::set<T>::const_iterator it = s1.begin();
         it != s1.end();
         ++it) {
      s2.insert(s2.end(), T(rand()));
      s3.erase(s3.begin());
    }

    // swap
    s1.swap(s2);
    NAMESPACE::swap(s2, s3);

    test::print(s1);
    test::print(s2);
    test::print(s3);
    test::tree_verify(s1);
    test::tree_verify(s2);
    test::tree_verify(s3);
  }
  {
    // constructor
    NAMESPACE::set<T> s2(s1.begin(), s1.end());
    NAMESPACE::set<T> s3;

    test::print(s2);
    test::print(s3);
    test::tree_verify(s1);
    test::tree_verify(s2);
    test::tree_verify(s3);

    // empty, erase
    while (!s1.empty())
      s1.erase(s1.begin());

    // swap
    NAMESPACE::swap(s1, s3);

    // clear, resize
    s1.clear();

    // equal_range
    for (int i = 0; i < 100; ++i) {
      NAMESPACE::pair<typename NAMESPACE::set<T>::iterator,
                      typename NAMESPACE::set<T>::iterator>
          p = s2.equal_range(T(rand()));
      for (typename NAMESPACE::set<T>::const_iterator it = p.first;
           it != p.second;
           ++it) {
        std::cout << *it << std::endl;
      }
    }

    // lower_bound
    for (int i = 0; i < 100; ++i) {
      typename NAMESPACE::set<T>::iterator p = s2.lower_bound(T(rand()));
      if (p == s2.end())
        std::cout << "NoElem" << std::endl;
      else
        std::cout << *p << std::endl;
    }

    // upper_bound
    for (int i = 0; i < 100; ++i) {
      typename NAMESPACE::set<T>::iterator p = s2.upper_bound(T(rand()));
      if (p == s2.end())
        std::cout << "NoElem" << std::endl;
      else
        std::cout << *p << std::endl;
    }

    test::print(s1);
    test::print(s2);
    test::print(s3);
    test::tree_verify(s1);
    test::tree_verify(s2);
    test::tree_verify(s3);

    // relational operator
    std::cout << (s1 == s3) << (s3 == s3) << (s1 < s2) << std::endl;
  }
}

#endif  // FT_CONTAINERS_TEST_SET_HPP
