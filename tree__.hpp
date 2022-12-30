/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree__.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:07:57 by chanhpar          #+#    #+#             */
/*   Updated: 2022/12/30 17:49:45 by chanhpar         ###   ########.fr       */
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
          typename KeyFromValue,
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

  typedef std::ptrdiff_t difference_type;
  typedef std::size_t size_type;

  typedef value_type* pointer;
  typedef value_type& reference;
  typedef const value_type* const_pointer;
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

    // iterate_node {{{2

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

    // iterate_node }}}

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

    rb_tree_iterator__<value_type>&
    operator++(void) {
      iter_next_node__();
      return (*this);
    }

    rb_tree_iterator__<value_type>
    operator++(int) {
      rb_tree_iterator__<value_type> tmp__(*this);
      iter_next_node__();
      return (tmp__);
    }

    rb_tree_iterator__<value_type>&
    operator--(void) {
      iter_prev_node__();
      return (*this);
    }

    rb_tree_iterator__<value_type>
    operator--(int) {
      rb_tree_iterator__<value_type> tmp__(*this);
      iter_prev_node__();
      return (tmp__);
    }

    bool
    operator==(const rb_tree_iterator__<const value_type>& other) const {
      return (this->node__ == other.node__);
    }

    // XXX
    // bool
    // operator==(const rb_tree_iterator__<value_type>& other) const {
    //   return (this->node__ == other.node__);
    // }

    bool
    operator!=(const rb_tree_iterator__<const value_type>& other) const {
      return (this->node__ != other.node__);
    }

    // bool
    // operator!=(const rb_tree_iterator__<value_type>& other) const {
    //   return (this->node__ != other.node__);
    // }

    // class rb_tree_iterator__ }}}
  };

  class rb_tree_alloc_base__ {
    // class rb_tree_alloc_base__ {{{
   public:
    typedef typename Allocator::template rebind<Value>::other allocator_type;

    allocator_type
    get_allocator(void) const {
      return (node_allocator);
    }

    rb_tree_alloc_base__(const allocator_type& a) :
        node_allocator(a), header(NULL) {
    }

   protected:
    typename Allocator::template rebind<value_node__>::other node_allocator;
    value_node__* header;

    value_node__*
    get_node__(void) {
      return (node_allocator.allocate(1));
    }

    void
    put_node__(value_node__* ptr) {
      node_allocator.deallocate(ptr, 1);
    }

    // class rb_tree_alloc_base__ }}}
  };

  struct rb_tree_node__ : public rb_tree_alloc_base__ {
    // struct rb_tree_node__ {{{
    typedef rb_tree_alloc_base__ Base__;
    typedef typename Base__::allocator_type allocator_type;

    rb_tree_node__(const allocator_type& a) : Base__(a) {
      this->header = this->get_node__();
    }

    ~rb_tree_node__(void) {
      this->put_node__(this->header);
    }

    // struct rb_tree_node__ }}}
  };

 private:
  rb_tree_node__ Base__;
  size_type node_count__;
  key_compare comp__;

 public:
  typedef typename rb_tree_node__::allocator_type allocator_type;

  typedef rb_tree_iterator__<value_type> iterator;
  typedef rb_tree_iterator__<const value_type> const_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

 public:
  allocator_type
  get_allocator(void) const {
    return (Base__.get_allocator());
  }

 private:
  // create, clone, destroy node {{{

  value_node__*
  create_node__(const value_type& x) {
    value_node__* tmp__ = Base__.get_node__();
    try {
      Base__.get_allocator().allocate(ft::addressof(tmp__->val), x);
    } catch (...) {
      Base__.put_node__(tmp__);
      throw;
    }
    return (tmp__);
  }

  value_node__*
  clone_node__(value_node__* other) {
    value_node__* tmp__ = this->create_node__(other->val);
    tmp__->isRed = other->isRed;
    tmp__->left = NULL;
    tmp__->right = NULL;
    tmp__->parent = NULL;
    return (tmp__);
  }

  void
  destroy_node__(value_node__* ptr) {
    Base__.get_allocator().destroy(ft::addressof(ptr->val));
    Base__.put_node__(ptr);
  }

  // create, clone, destroy node }}}

  value_node__*&
  get_root__(void) const {
    return (dynamic_cast<value_node__*&>(Base__.header->parent));
  }

  value_node__*&
  get_leftmost__(void) const {
    return (dynamic_cast<value_node__*&>(Base__.header->left));
  }

  value_node__*&
  get_rightmost__(void) const {
    return (dynamic_cast<value_node__*&>(Base__.header->right));
  }

  // static getter for value_node__* type {{{

  static value_node__*&
  get_left(value_node__* x) {
    return (dynamic_cast<value_node__*&>(x->left));
  }

  static value_node__*&
  get_right(value_node__* x) {
    return (dynamic_cast<value_node__*&>(x->right));
  }

  static value_node__*&
  get_parent(value_node__* x) {
    return (dynamic_cast<value_node__*&>(x->parent));
  }

  static reference
  get_value(value_node__* x) {
    return (x->val);
  }

  static const key_type&
  get_key(value_node__* x) {
    return (KeyFromValue()(get_value(x)));
  }

  static bool&
  is_red(value_node__* x) {
    return (x->isRed);
  }

  // static getter for value_node__* type }}}

  // static getter for base_node__* type {{{

  static value_node__*&
  get_left(base_node__* x) {
    return (dynamic_cast<value_node__*&>(x->left));
  }

  static value_node__*&
  get_right(base_node__* x) {
    return (dynamic_cast<value_node__*&>(x->right));
  }

  static value_node__*&
  get_parent(base_node__* x) {
    return (dynamic_cast<value_node__*&>(x->parent));
  }

  static reference
  get_value(base_node__* x) {
    return (dynamic_cast<value_node__*>(x)->val);
  }

  static const key_type&
  get_key(base_node__* x) {
    return (KeyFromValue()(get_value(dynamic_cast<value_node__*>(x))));
  }

  static bool&
  is_red(base_node__* x) {
    return (x->isRed);
  }

  // static getter for base_node__* type }}}

  // XXX
  void
  empty_initialize(void) {
  }

 public:
  // XXX have to implement constructors
  rb_tree__(void) : Base__(allocator_type()), node_count__(0), comp__() {
    empty_initialize();
  }

  // XXX remove when done;
 public:
  rb_tree_base_node__ dummy1;
  rb_tree_value_node__<value_type> dummy2;
  iterator dummy3;
  const_iterator cdummy3;
  reverse_iterator rdummy3;
  const_reverse_iterator crdummy3;
  rb_tree_alloc_base__ dummy4(Allocator());
  rb_tree_node__ dummy5(Allocator());

};  // class rb_tree__

}  // namespace ft

#endif  // FT_CONTAINERS_TREE_HPP
