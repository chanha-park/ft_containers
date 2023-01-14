/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_macro.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 01:39:56 by chanhpar          #+#    #+#             */
/*   Updated: 2023/01/15 01:43:45 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_TEST_MACRO_HPP
#define FT_CONTAINERS_TEST_MACRO_HPP

#ifndef FT
#  define NAMESPACE std
#  include <map>
#  include <set>
#  include <stack>
#  include <vector>
#else
#  define NAMESPACE ft
#  include "map.hpp"
#  include "set.hpp"
#  include "stack.hpp"
#  include "vector.hpp"
#endif

#endif  // FT_CONTAINERS_TEST_MACRO_HPP
