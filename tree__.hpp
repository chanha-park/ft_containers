/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree__.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:07:57 by chanhpar          #+#    #+#             */
/*   Updated: 2022/12/23 02:54:58 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_TREE_HPP
#define FT_CONTAINERS_TREE_HPP

#include <memory>
#include "utility.hpp"

namespace ft {

template <typename Key,
          typename T,
          typename Compare,
          typename Allocator = std::allocator<T> >
class rb_tree__ {
 public:
  typedef Key key_type;
  typedef T mapped_type;
  typedef typename ft::pair<const key_type, mapped_type> value_type;
  typedef Compare key_compare;

 private:
  struct rb_tree_node_base__ {
    rb_tree_node_base__* parent;
    rb_tree_node_base__* left;
    rb_tree_node_base__* right;
    bool isRed;
  };

  struct rb_tree_node_value__ : public rb_tree_node_base__ {
    value_type val;
  };

  struct rb_tree_alloc_base__ {};

  struct rb_tree_node__ : public rb_tree_alloc_base__ {};

 protected:
 public:
};

}  // namespace ft

#endif
