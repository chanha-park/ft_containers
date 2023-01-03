/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree__.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:07:57 by chanhpar          #+#    #+#             */
/*   Updated: 2023/01/03 16:16:22 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_TREE_HPP
#define FT_CONTAINERS_TREE_HPP

#include <algorithm>
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
  typedef bool node_color__;
  static const node_color__ red__ = true;
  static const node_color__ black__ = false;

  class rb_tree_base_node__ {
    // class rb_tree_base_node__ {{{
   public:
    rb_tree_base_node__* parent;
    rb_tree_base_node__* left;
    rb_tree_base_node__* right;
    node_color__ color;

    static rb_tree_base_node__*
    local_leftmost__(rb_tree_base_node__* x) {
      while (x->left != NULL)
        x = x->left;
      return (x);
    }

    static const rb_tree_base_node__*
    local_leftmost__(const rb_tree_base_node__* x) {
      while (x->left != NULL)
        x = x->left;
      return (x);
    }

    static rb_tree_base_node__*
    local_rightmost__(rb_tree_base_node__* x) {
      while (x->right != NULL)
        x = x->right;
      return (x);
    }

    static const rb_tree_base_node__*
    local_rightmost__(const rb_tree_base_node__* x) {
      while (x->right != NULL)
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
      if (node__->right != NULL) {
        node__ = node__->right;
        while (node__->left != NULL)
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
      if (node__->color == red__ && node__->parent->parent == node__) {
        node__ = node__->right;
      } else if (node__->left != NULL) {
        node__ = node__->left;
        while (node__->right != NULL)
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

    value_node__*
    allocate_node__(void) {
      return (node_allocator.allocate(1));
    }

    void
    deallocate_node__(value_node__* ptr) {
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
      this->header = this->allocate_node__();
    }

    ~rb_tree_node__(void) {
      this->deallocate_node__(this->header);
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
    value_node__* tmp__ = this->Base__.allocate_node__();
    try {
      this->Base__.get_allocator().construct(ft::addressof(tmp__->val), x);
    } catch (...) {
      this->Base__.deallocate_node__(tmp__);
      throw;
    }
    return (tmp__);
  }

  value_node__*
  clone_node__(value_node__* other) {
    value_node__* tmp__ = this->create_node__(other->val);
    tmp__->color = other->color;
    tmp__->left = NULL;
    tmp__->right = NULL;
    return (tmp__);
  }

  void
  destroy_node__(value_node__* ptr) {
    this->Base__.get_allocator().destroy(ft::addressof(ptr->val));
    this->Base__.deallocate_node__(ptr);
  }

  // create, clone, destroy node }}}

  // methods for root, leftmost, rightmost {{{

  value_node__*&
  _header__(void) {
    return (this->Base__.header);
  }

  const value_node__*
  _header__(void) const {
    return (this->Base__.header);
  }

  base_node__*&
  _root__(void) {
    return (this->Base__.header->parent);
  }

  const base_node__*
  _root__(void) const {
    return (this->Base__.header->parent);
  }

  base_node__*&
  _leftmost__(void) {
    return (this->Base__.header->left);
  }

  const base_node__*
  _leftmost__(void) const {
    return (this->Base__.header->left);
  }

  base_node__*&
  _rightmost__(void) {
    return (this->Base__.header->right);
  }

  const base_node__*
  _rightmost__(void) const {
    return (this->Base__.header->right);
  }

  // methods for root, leftmost, rightmost }}}

  // static methods for base_node__* type {{{

  static value_node__*
  _left__(base_node__* x) {
    return (static_cast<value_node__*>(x->left));
  }

  static const value_node__*
  _left__(const base_node__* x) {
    return (static_cast<const value_node__*>(x->left));
  }

  static value_node__*
  _right__(base_node__* x) {
    return (static_cast<value_node__*>(x->right));
  }

  static const value_node__*
  _right__(const base_node__* x) {
    return (static_cast<const value_node__*>(x->right));
  }

  static value_node__*
  _parent__(base_node__* x) {
    return (static_cast<value_node__*>(x->parent));
  }

  static const value_node__*
  _parent__(const base_node__* x) {
    return (static_cast<const value_node__*>(x->parent));
  }

  // static reference
  // get_value__(value_node__* x) {
  //   return (x->val);
  // }

  static const key_type&
  _key__(const value_node__* x) {
    return (KeyFromValue()(x->val));
  }

  static const key_type&
  _key__(const base_node__* x) {
    return (KeyFromValue()(static_cast<const value_node__*>(x)->val));
  }

  static node_color__&
  is_red__(base_node__* x) {
    return (x->color);
  }

  // static getter for value_node__* type }}}

  static base_node__*
  local_leftmost__(base_node__* x) {
    return (base_node__::local_leftmost__(x));
  }

  static const base_node__*
  local_leftmost__(const base_node__* x) {
    return (base_node__::local_leftmost__(x));
  }

  static base_node__*
  local_rightmost__(base_node__* x) {
    return (base_node__::local_rightmost__(x));
  }

  static const base_node__*
  local_rightmost__(const base_node__* x) {
    return (base_node__::local_rightmost__(x));
  }

  // XXX Need Rename
  void
  _Rb_tree_rebalance(base_node__* x, base_node__*& root) {
    (void)x;
    (void)root;
  }

  // XXX insert new node(v) to y. y must be unsaturated, Need Rename
  iterator
  _M_insert(bool has_right_child, base_node__* y, const value_type& v) {
    value_node__* y__ = static_cast<value_node__*>(y);
    value_node__* node_to_insert__;

    node_to_insert__ = this->create_node__(v);
    if (y__ == this->_header__() || !has_right_child
        || this->comp__(KeyFromValue()(v), _key__(y__))) {
      _left__(y__) = node_to_insert__;

      if (y__ == this->_header__()) {
        this->_root__() = node_to_insert__;
        this->_rightmost__() = node_to_insert__;
      } else if (y__ == this->_leftmost__()) {
        this->_leftmost__() = node_to_insert__;
      }
    } else {
      _right__(y__) = node_to_insert__;

      if (y__ == this->_rightmost__())
        this->_rightmost__() = node_to_insert__;
    }

    _parent__(node_to_insert__) = y__;
    _left__(node_to_insert__) = NULL;
    _right__(node_to_insert__) = NULL;

    _Rb_tree_rebalance(node_to_insert__, _header__()->parent);
    ++(this->node_count__);
    return (iterator(node_to_insert__));
  }

  value_node__*
  _M_copy(value_node__* x, value_node__* parent) {
    value_node__* tmp__;

    value_node__* top__ = this->clone_node__(x);
    top__->parent = parent;

    try {
      if (x->right != NULL) {
        top__->right = static_cast<base_node__*>(_M_copy(_right__(x), top__));
      }
      parent = top__;
      x = _left__(x);
      while (x != NULL) {
        tmp__ = this->clone_node__(x);
        parent->left = tmp__;
        tmp__->parent = parent;
        if (x->right != NULL)
          tmp__->right = _M_copy(_right__(x), tmp__);
        parent = tmp__;
        x = _left__(x);
      }
    } catch (...) {
      _M_erase(top__);
      throw;
    }
    return (top__);
  }

  // XXX Need Rename: erase every nodes below x (inclusive)
  void
  _M_erase(value_node__* x) {
    value_node__* tmp__;
    while (x != NULL) {
      _M_erase(_right__(x));
      tmp__ = x;
      x = _left__(x);
      destroy_node__(tmp__);
    }
  }

  void
  empty_initialize(void) {
    this->is_red__(this->_header__()) = true;
    this->_root__() = NULL;
    this->_leftmost__() = this->_header__();
    this->_rightmost__() = this->_header__();
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
    if (other._root__() == NULL)
      this->empty_initialize();
    else {
      this->is_red(this->_header__()) = true;
      this->_root__() = _M_copy(other._root__(), this->_header__());
      this->_leftmost__() = this->local_leftmost(this->_root__());
      this->_rightmost__() = this->local_rightmost(this->_root__());
    }
  }

  rb_tree__<Key, Value, KeyFromValue, Compare, Allocator>&
  operator=(
      const rb_tree__<Key, Value, KeyFromValue, Compare, Allocator>& other) {
    if (this != &other) {
      this->clear();
      this->comp__ = other.comp__;

      if (other._root__() == 0) {
        this->_root__() = NULL;
        this->_leftmost__() = this->_header__();
        this->_rightmost__() = this->_header__();
        this->node_count__ = 0;

      } else {
        this->_root__() = _M_copy(other._root__(), this->_header__());
        this->_leftmost__() = this->local_leftmost(this->_root__());
        this->_rightmost__() = this->local_rightmost(this->_root__());
        this->node_count__ = other.node_count__;
      }
    }
    return (*this);
  }

  // just _M_erase might be enough
  ~rb_tree__(void) {
    this->clear();
  }

  // ctor, operator=, dtor }}}

  // accessors {{{

  // accessors }}}

  // observer

  key_compare
  key_comp(void) const {
    return (this->comp__);
  }

  // iterator {{{

  iterator
  begin(void) {
    return (this->_leftmost__());
  }

  const_iterator
  begin(void) const {
    return (this->_leftmost__());
  }

  iterator
  end(void) {
    return (this->Base__.header);
  }

  const_iterator
  end(void) const {
    return (this->Base__.header);
  }

  reverse_iterator
  rbegin(void) {
    return (reverse_iterator(this->end()));
  }

  const_reverse_iterator
  rbegin(void) const {
    return (const_reverse_iterator(this->end()));
  }

  reverse_iterator
  rend(void) {
    return (reverse_iterator(this->begin()));
  }

  const_reverse_iterator
  rend(void) const {
    return (const_reverse_iterator(this->begin()));
  }

  // iterator }}}

  // capacity {{{

  bool
  empty(void) const {
    return (this->node_count__ == 0);
  }

  size_type
  size(void) const {
    return (this->node_count__);
  }

  size_type
  max_size(void) const {
    static const size_type maxSize__
        = std::min<size_type>(this->node_allocator.max_size(),
                              std::numeric_limits<difference_type>::max());
    return (maxSize__);
  }

  // capacity }}}

  void
  swap(rb_tree__<Key, Value, KeyFromValue, Compare, Allocator>& other) {
    std::swap(this->Base__.header, other.Base__.header);
    std::swap(this->node_count__, other.node_count__);
    std::swap(this->comp__, other.comp__);
  }

  // insert {{{

  // XXX
  ft::pair<iterator, bool>
  insert_unique(const value_type& x) {
    // to compile
    (void)x;
    return (ft::pair<iterator, bool>(iterator(x), true));
    // to compile
  }

  // XXX
  iterator
  insert_equal(const value_type& x) {
    // to compile
    (void)x;
    return (iterator());
    // to compile
  }

  // XXX
  iterator
  insert_unique(iterator position, const value_type& x) {
    // to compile
    (void)position;
    (void)x;
    return (iterator());
    // to compile
  }

  // XXX
  iterator
  insert_equal(iterator position, const value_type& x) {
    // to compile
    (void)position;
    (void)x;
    return (iterator());
    // to compile
  }

  // XXX
  template <class InputIter>
  void
  insert_unique(InputIter first, InputIter last) {
    // to compile
    (void)first;
    (void)last;
    // to compile
  }

  // XXX
  template <class InputIter>
  void
  insert_equal(InputIter first, InputIter last) {
    // to compile
    (void)first;
    (void)last;
    // to compile
  }

  // insert }}}

  // erase, clear {{{

  // XXX
  void
  erase(iterator pos) {
    // to compile
    (void)pos;
    // to compile
  }

  // XXX
  size_type
  erase(const key_type& x) {
    // to compile
    (void)x;
    // to compile
  }

  void
  erase(iterator first, iterator last) {
    if (first == this->begin() && last == this->end())
      this->clear();
    else {
      while (first != last)
        this->erase(first++);
    }
  }

  void
  clear(void) {
    if (this->node_count__ != 0) {
      this->_M_erase(static_cast<value_node__*>(this->_root__()));
      this->_leftmost__() = this->_header__();
      this->_root__() = NULL;
      this->_rightmost__() = this->_header__();
      this->node_count__ = 0;
    }
  }

  // erase, clear }}}

  // find, count, lower_bound, upper_bound, equal_range {{{

  iterator
  find(const key_type& key) {
    value_node__* prev__ = this->_header__();
    value_node__* curr__ = static_cast<value_node__*>(prev__->parent);

    while (curr__ != NULL)
      if (this->comp__(_key__(curr__), key)) {
        curr__ = _right__(curr__);
      } else {
        prev__ = curr__;
        curr__ = _left__(curr__);
      }

    iterator it__(prev__);
    return ((it__ == this->end() || this->comp__(key, _key__(prev__)))
                ? this->end()
                : it__);
  }

  const_iterator
  find(const key_type& key) const {
    value_node__* prev__ = this->_header__();
    value_node__* curr__ = static_cast<value_node__*>(prev__->parent);

    while (curr__ != NULL)
      if (this->comp__(_key__(curr__), key)) {
        curr__ = _right__(curr__);
      } else {
        prev__ = curr__;
        curr__ = _left__(curr__);
      }

    const_iterator it__(prev__);
    return ((it__ == this->end() || this->comp__(key, _key__(prev__)))
                ? this->end()
                : it__);
  }

  size_type
  count(const key_type& key) const {
    ft::pair<const_iterator, const_iterator> range__ = equal_range(key);
    size_type n__ = distance(range__.first, range__.second);
    return (n__);
  }

  iterator
  lower_bound(const key_type& key) {
    value_node__* prev__ = this->_header__();
    value_node__* curr__ = static_cast<value_node__*>(prev__->parent);

    while (curr__ != NULL) {
      if (this->comp__(_key__(curr__), key)) {
        curr__ = _right__(curr__);
      } else {
        prev__ = curr__;
        curr__ = _left__(curr__);
      }
    }
    return (iterator(prev__));
  }

  const_iterator
  lower_bound(const key_type& key) const {
    value_node__* prev__ = this->_header__();
    value_node__* curr__ = static_cast<value_node__*>(prev__->parent);

    while (curr__ != NULL) {
      if (this->comp__(_key__(curr__), key)) {
        curr__ = _right__(curr__);
      } else {
        prev__ = curr__;
        curr__ = _left__(curr__);
      }
    }
    return (const_iterator(prev__));
  }

  iterator
  upper_bound(const key_type& key) {
    value_node__* prev__ = this->_header__();
    value_node__* curr__ = static_cast<value_node__*>(prev__->parent);

    while (curr__ != NULL) {
      if (this->comp__(key, _key__(curr__))) {
        prev__ = curr__;
        curr__ = _left__(curr__);
      } else {
        curr__ = _right__(curr__);
      }
    }
    return (iterator(prev__));
  }

  const_iterator
  upper_bound(const key_type& key) const {
    value_node__* prev__ = this->_header__();
    value_node__* curr__ = static_cast<value_node__*>(prev__->parent);

    while (curr__ != NULL) {
      if (this->comp__(key, _key__(curr__))) {
        prev__ = curr__;
        curr__ = _left__(curr__);
      } else {
        curr__ = _right__(curr__);
      }
    }
    return (const_iterator(prev__));
  }

  ft::pair<iterator, iterator>
  equal_range(const key_type& key) {
    return (ft::pair<iterator, iterator>(lower_bound(key), upper_bound(key)));
  }

  ft::pair<const_iterator, const_iterator>
  equal_range(const key_type& key) const {
    return (ft::pair<const_iterator, const_iterator>(lower_bound(key),
                                                     upper_bound(key)));
  }

  // find, count, lower_bound, upper_bound, equal_range }}}

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
