/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestVector.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:06:47 by chanhpar          #+#    #+#             */
/*   Updated: 2023/01/15 01:42:23 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_TEST_VECTOR_HPP
#define FT_CONTAINERS_TEST_VECTOR_HPP

#include "test_macro.hpp"

template <typename T>
void
test_vector(void) {
	NAMESPACE::vector<T> vec;
}

#endif  // FT_CONTAINERS_TEST_VECTOR_HPP
