/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree__.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:07:57 by chanhpar          #+#    #+#             */
/*   Updated: 2022/12/28 18:02:18 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_TREE_HPP
#define FT_CONTAINERS_TREE_HPP

#include <memory>
#include "iterator.hpp"
#include "memory.hpp"
#include "utility.hpp"

namespace ft {

template <typename Key,
          typename Value,
          typename Compare,
          typename Allocator = std::allocator<Value> >
class rb_tree__ {
 private:
  // XXX consider virtual?
  struct rb_tree_node_base__ {
    // struct rb_tree_node_base__ {{{

    rb_tree_node_base__* parent;
    rb_tree_node_base__* left;
    rb_tree_node_base__* right;
    bool isRed;

    rb_tree_node_base__*
    find_next_node__(void) const {
      rb_tree_node_base__* curr = this;
      if (curr->right) {
        curr = curr->right;
        while (curr->left)
          curr = curr->left;
      } else {
        while (curr == curr->parent->right)
          curr = curr->parent;
        if (curr->parent != curr->right)
          curr = curr->parent;
      }
      return (curr);
    }

    rb_tree_node_base__*
    find_prev_node__(void) const {
      rb_tree_node_base__* curr = this;
      if (isRed && curr->parent->parent == curr) {
        curr = curr->right;
      } else if (curr->left) {
        curr = curr->left;
        while (curr->right)
          curr = curr->right;

      } else {
        while (curr == curr->parent->left)
          curr = curr->parent;
        curr = curr->parent;
      }
      return (curr);
    }

    virtual ~rb_tree_node_base__(void) {
    }

    // struct rb_tree_node_base__ }}}
  };

 public:
  typedef Key key_type;
  typedef Value value_type;
  typedef Compare key_compare;
  typedef ptrdiff_t difference_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type& reference;
  typedef const value_type& const_reference;

 private:
  template <typename T>
  struct rb_tree_node_value__ : public rb_tree_node_base__ {
    T val;
  };

  typedef rb_tree_node_base__ base_node__;
  typedef rb_tree_node_value__<value_type> value_node__;

  template <typename T>
  struct rb_tree_iterator__ {
    typedef ft::bidirectional_iterator_tag iterator_category;
    base_node__* node__;

    rb_tree_iterator__(void) {
    }

    rb_tree_iterator__(rb_tree_node_value__<T>* x) :
        node__(static_cast<base_node__*>(x)) {
    }

    rb_tree_iterator__(const rb_tree_iterator__& it) : node__(it.node__) {
    }

    reference
    operator*() const {
      return (dynamic_cast<rb_tree_node_value__<T>*>(node__)->val);
    }

    pointer
    operator->() const {
      return (ft::addressof(operator*()));
    }
  };

  typedef rb_tree_iterator__<value_type> iterator;
  typedef rb_tree_iterator__<const value_type> const_iterator;

  struct rb_tree_alloc_base__ {};

  struct rb_tree_node__ : public rb_tree_alloc_base__ {};

 protected:
 public:
  rb_tree_node_base__ dummy1;
  rb_tree_node_value__<value_type> dummy2;
  iterator dummy3;
  rb_tree_alloc_base__ dummy4;
  rb_tree_node__ dummy5;

};  // class rb_tree__

}  // namespace ft

#endif  // FT_CONTAINERS_TREE_HPP
