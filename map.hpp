/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 19:09:39 by chanhpar          #+#    #+#             */
/*   Updated: 2022/12/16 19:56:38 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_MAP_HPP

namespace ft {

template <typename Key,
          typename T,
          typename Compare = std::less<Key>,
          typename Allocator = std::allocator<ft::pair<const Key, T> > >
class map {
 private:
 protected:
 public:
};

}  // namespace ft

#endif  // FT_CONTAINERS_MAP_HPP
