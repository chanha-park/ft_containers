/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_macro.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 01:39:56 by chanhpar          #+#    #+#             */
/*   Updated: 2023/01/16 17:21:06 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_TEST_MACRO_HPP
#define FT_CONTAINERS_TEST_MACRO_HPP

#ifndef FT
#  define NAMESPACE std
#  define Error_MSG "STD ERROR"
#  include <map>
#  include <set>
#  include <stack>
#  include <vector>
#else
#  define NAMESPACE ft
#  define Error_MSG "FT ERROR"
#  include "map.hpp"
#  include "set.hpp"
#  include "stack.hpp"
#  include "vector.hpp"
#endif

#include <stdlib.h>
#include <iostream>

#include "type_traits.hpp"
#include "utility.hpp"

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096

struct Buffer {
  int idx;
  char buff[BUFFER_SIZE];
};

// #define COUNT (MAX_RAM / (int)sizeof(Buffer))
#define COUNT 100000

namespace test {

template <typename T>
struct is_pair : public ft::false_type {};

template <typename T, typename U>
struct is_pair<NAMESPACE::pair<T, U> > : public ft::true_type {};

template <typename T>
typename ft::enable_if<!test::is_pair<typename T::value_type>::value,
                       void>::type
print(const T& con) {
  std::cout << con.size() << std::endl;
  for (typename T::const_iterator it = con.begin(); it != con.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}

template <typename T>
typename ft::enable_if<test::is_pair<typename T::value_type>::value, void>::type
print(const T& con) {
  std::cout << con.size() << std::endl;
  for (typename T::const_iterator it = con.begin(); it != con.end(); ++it) {
    std::cout << it->first << " " << it->second << " ";
  }
  std::cout << std::endl;
}

}  // namespace test

#endif  // FT_CONTAINERS_TEST_MACRO_HPP
