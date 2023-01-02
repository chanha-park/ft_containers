/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree__.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:07:57 by chanhpar          #+#    #+#             */
/*   Updated: 2023/01/02 17:50:15 by chanhpar         ###   ########.fr       */
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
  class rb_tree_base_node__ {
   public:
    // class rb_tree_base_node__ {{{
    rb_tree_base_node__* parent;
    rb_tree_base_node__* left;
    rb_tree_base_node__* right;
    bool isRed;

    static rb_tree_base_node__*
    local_leftmost__(rb_tree_base_node__* x) {
      while (x->left)
        x = x->left;
      return (x);
    }

    static rb_tree_base_node__*
    local_rightmost__(rb_tree_base_node__* x) {
      while (x->right)
        x = x->right;
      return (x);
    }

    // class rb_tree_base_node__ }}}
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
  class rb_tree_value_node__ : public rb_tree_base_node__ {
   public:
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
      return (static_cast<value_node__*>(node__)->val);
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

   protected:
    typename Allocator::template rebind<value_node__>::other node_allocator;

   public:
    allocator_type
    get_allocator(void) const {
      return (node_allocator);
    }

    rb_tree_alloc_base__(const allocator_type& a) :
        node_allocator(a), header(NULL) {
    }

    value_node__* header;

   protected:
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

  class rb_tree_node__ : public rb_tree_alloc_base__ {
    // class rb_tree_node__ {{{
   public:
    typedef rb_tree_alloc_base__ Base__;
    typedef typename Base__::allocator_type allocator_type;

    rb_tree_node__(const allocator_type& a) : Base__(a) {
      this->header = this->get_node__();
    }

    ~rb_tree_node__(void) {
      this->put_node__(this->header);
    }

    // class rb_tree_node__ }}}
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
    return (this->Base__.get_allocator());
  }

 private:
  // create, clone, destroy node {{{

  value_node__*
  create_node__(const value_type& x) {
    value_node__* tmp__ = this->Base__.get_node__();
    try {
      this->Base__.get_allocator().allocate(ft::addressof(tmp__->val), x);
    } catch (...) {
      this->Base__.put_node__(tmp__);
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
    tmp__->parent = NULL;  // XXX maybe unnecessary?
    return (tmp__);
  }

  void
  destroy_node__(value_node__* ptr) {
    this->Base__.get_allocator().destroy(ft::addressof(ptr->val));
    this->Base__.put_node__(ptr);
  }

  // create, clone, destroy node }}}

  // getter, setter for root, leftmost, rightmost {{{

  value_node__*
  get_root__(void) const {
    return (static_cast<value_node__*>(this->Base__.header->parent));
  }

  value_node__*
  get_leftmost__(void) const {
    return (static_cast<value_node__*>(this->Base__.header->left));
  }

  value_node__*
  get_rightmost__(void) const {
    return (static_cast<value_node__*>(this->Base__.header->right));
  }

  void
  set_root__(value_node__* other) {
    this->Base__.header->parent = static_cast<base_node__*>(other);
  }

  void
  set_leftmost__(value_node__* other) {
    this->Base__.header->left = static_cast<base_node__*>(other);
  }

  void
  set_rightmost__(value_node__* other) {
    this->Base__.header->right = static_cast<base_node__*>(other);
  }

  // getter, setter for root, leftmost, rightmost }}}

  // static getter for value_node__* type {{{

  static value_node__*&
  get_left__(value_node__* x) {
    return (static_cast<value_node__*&>(x->left));
  }

  static value_node__*&
  get_right__(value_node__* x) {
    return (static_cast<value_node__*&>(x->right));
  }

  static value_node__*&
  get_parent__(value_node__* x) {
    return (static_cast<value_node__*&>(x->parent));
  }

  static reference
  get_value__(value_node__* x) {
    return (x->val);
  }

  static const key_type&
  get_key__(value_node__* x) {
    return (KeyFromValue()(get_value(x)));
  }

  static bool&
  is_red__(value_node__* x) {
    return (x->isRed);
  }

  // static getter for value_node__* type }}}

  // static getter for base_node__* type {{{

  static value_node__*&
  get_left__(base_node__* x) {
    return (static_cast<value_node__*&>(x->left));
  }

  static value_node__*&
  get_right__(base_node__* x) {
    return (static_cast<value_node__*&>(x->right));
  }

  static value_node__*&
  get_parent__(base_node__* x) {
    return (static_cast<value_node__*&>(x->parent));
  }

  static reference
  get_value__(base_node__* x) {
    return (static_cast<value_node__*>(x)->val);
  }

  static const key_type&
  get_key__(base_node__* x) {
    return (KeyFromValue()(get_value(static_cast<value_node__*>(x))));
  }

  static bool&
  is_red__(base_node__* x) {
    return (x->isRed);
  }

  // static getter for base_node__* type }}}

  static value_node__*
  local_leftmost__(value_node__* x) {
    return (static_cast<value_node__*>(base_node__::local_leftmost__(x)));
  }

  static value_node__*
  local_rightmost__(value_node__* x) {
    return (static_cast<value_node__*>(base_node__::local_rightmost__(x)));
  }

  // XXX
  iterator
  _M_insert(base_node__* x, base_node__* y, const value_type& v);

  // XXX
  value_node__*
  _M_copy(value_node__* x, value_node__* p);

  // XXX
  void
  _M_erase(value_node__* x);

  // XXX
  void
  empty_initialize(void) {
    this->is_red__(this->Base__.header) = true;
    this->set_root__(NULL);
    this->set_leftmost__(this->Base__.header);
    this->set_rightmost__(this->Base__.header);
  }

 public:
  // ctor, operator=, dtor {{{

  rb_tree__(void) : Base__(allocator_type()), node_count__(0), comp__() {
    this->empty_initialize();
  }

  rb_tree__(const key_compare& comp) :
      Base__(allocator_type()), node_count__(0), comp__(comp) {
    this->empty_initialize();
  }

  rb_tree__(const key_compare& comp, const allocator_type& a) :
      Base__(a), node_count__(0), comp__(comp) {
    this->empty_initialize();
  }

  rb_tree__(
      const rb_tree__<Key, Value, KeyFromValue, Compare, Allocator>& other) :
      Base__(other.get_allocator()),
      node_count__(other.node_count__),
      comp__(other.comp__) {
    if (other.get_root__() == NULL)
      this->empty_initialize();
    else {
      this->is_red(this->Base__.header) = true;
      this->set_root__(_M_copy(other.get_root__(), this->Base__.header));
      this->set_leftmost__(this->local_leftmost(this->get_root__()));
      this->set_rightmost__(this->local_rightmost(this->get_root__()));
    }
  }

  rb_tree__<Key, Value, KeyFromValue, Compare, Allocator>&
  operator=(
      const rb_tree__<Key, Value, KeyFromValue, Compare, Allocator>& other) {
    if (this != &other) {
      this->clear();
      this->comp__ = other.comp__;

      if (other.get_root__() == 0) {
        this->set_root__(NULL);
        this->set_leftmost__(this->Base__.header);
        this->set_rightmost__(this->Base__.header);
        this->node_count__ = 0;

      } else {
        this->set_root__(_M_copy(other.get_root__(), this->Base__.header));
        this->set_leftmost__(this->local_leftmost(this->get_root__()));
        this->set_rightmost__(this->local_rightmost(this->get_root__()));
        this->node_count__ = other.node_count__;
      }
    }
    return (*this);
  }

  ~rb_tree__(void) {
    this->clear();
  }

  // ctor, operator=, dtor }}}

  // erase, clear {{{

  void
  erase(iterator pos) {
    (void)pos;
  }

  // size_type
  // erase(const key_type& x) {
  // }

  // void
  // erase(iterator first, iterator last) {
  // }

  // void
  // erase(const key_type* first, const key_type* last) {
  // }

  void
  clear(void) {
    if (this->node_count__ != 0) {
      this->erase(this->get_root__());
      this->set_leftmost__(this->Base__.header);
      this->set_root__(NULL);
      this->set_rightmost__(this->Base__.header);
      this->node_count__ = 0;
    }
  }

  // erase, clear }}}

  // // accessors {{{

  // key_compare
  // get_key_compare(void) const {
  //   return (this->comp__);
  // }

  // iterator
  // begin(void) {
  //   return (this->get_leftmost__());
  // }

  // const_iterator
  // begin(void) const {
  //   return _M_leftmost();
  // }

  // iterator
  // end(void) {
  //   return _M_header;
  // }

  // const_iterator
  // end(void) const {
  //   return _M_header;
  // }

  // reverse_iterator
  // rbegin(void) {
  //   return reverse_iterator(end());
  // }

  // const_reverse_iterator
  // rbegin(void) const {
  //   return const_reverse_iterator(end());
  // }

  // reverse_iterator
  // rend(void) {
  //   return reverse_iterator(begin());
  // }

  // const_reverse_iterator
  // rend(void) const {
  //   return const_reverse_iterator(begin());
  // }

  // bool
  // empty(void) const {
  //   return _M_node_count == 0;
  // }

  // size_type
  // size(void) const {
  //   return _M_node_count;
  // }

  // size_type
  // max_size(void) const {
  //   return size_type(-1);
  // }

  // void
  // swap(_Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>& __t) {
  //   std::swap(_M_header, __t._M_header);
  //   std::swap(_M_node_count, __t._M_node_count);
  //   std::swap(_M_key_compare, __t._M_key_compare);
  // }

  // // accessors }}}

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
