/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree__.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:07:57 by chanhpar          #+#    #+#             */
/*   Updated: 2022/12/29 13:58:03 by chanhpar         ###   ########.fr       */
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
  struct rb_tree_base_node__ {
    // struct rb_tree_base_node__ {{{

    rb_tree_base_node__* parent;
    rb_tree_base_node__* left;
    rb_tree_base_node__* right;
    bool isRed;

    virtual ~rb_tree_base_node__(void) {
    }

    // struct rb_tree_base_node__ }}}
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
  struct rb_tree_value_node__ : public rb_tree_base_node__ {
    T val;
  };

  typedef rb_tree_base_node__ base_node__;
  typedef rb_tree_value_node__<value_type> value_node__;

  template <typename T>
  class rb_tree_iterator__ {
    // class rb_tree_iterator__ {{{

   public:
    typedef ptrdiff_t difference_type;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef ft::bidirectional_iterator_tag iterator_category;

   private:
    base_node__* node__;

    void
    iter_next_node__(void) {
      if (node__->right) {
        node__ = node__->right;
        while (node__->left)
          node__ = node__->left;
      } else {
        while (node__ == node__->parent->right)
          node__ = node__->parent;
        if (node__->parent != node__->right)
          node__ = node__->parent;
      }
    }

    void
    iter_prev_node__(void) {
      if (node__->isRed && node__->parent->parent == node__) {
        node__ = node__->right;
      } else if (node__->left) {
        node__ = node__->left;
        while (node__->right)
          node__ = node__->right;

      } else {
        while (node__ == node__->parent->left)
          node__ = node__->parent;
        node__ = node__->parent;
      }
    }

   public:
    rb_tree_iterator__(void) {
    }

    rb_tree_iterator__(value_node__* x) : node__(static_cast<base_node__*>(x)) {
    }

    rb_tree_iterator__(const rb_tree_iterator__& it) : node__(it.node__) {
    }

    reference
    operator*() const {
      return (dynamic_cast<value_node__*>(node__)->val);
    }

    pointer
    operator->() const {
      return (ft::addressof(operator*()));
    }

    rb_tree_iterator__<T>&
    operator++(void) {
      iter_next_node__();
      return (*this);
    }

    rb_tree_iterator__<T>
    operator++(int) {
      rb_tree_iterator__<T> tmp__(*this);
      iter_next_node__();
      return (tmp__);
    }

    rb_tree_iterator__<T>&
    operator--(void) {
      iter_prev_node__();
      return (*this);
    }

    rb_tree_iterator__<T>
    operator--(int) {
      rb_tree_iterator__<T> tmp__(*this);
      iter_prev_node__();
      return (tmp__);
    }

    // class rb_tree_iterator__ }}}
  };

  struct rb_tree_alloc_base__ {};

  struct rb_tree_node__ : public rb_tree_alloc_base__ {};

 protected:
 public:
  typedef rb_tree_iterator__<value_type> iterator;
  typedef rb_tree_iterator__<const value_type> const_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

  // XXX remove when done;
  rb_tree_base_node__ dummy1;
  rb_tree_value_node__<value_type> dummy2;
  iterator dummy3;
  const_iterator cdummy3;
  reverse_iterator rdummy3;
  const_reverse_iterator crdummy3;
  rb_tree_alloc_base__ dummy4;
  rb_tree_node__ dummy5;

};  // class rb_tree__

}  // namespace ft

#endif  // FT_CONTAINERS_TREE_HPP
