/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree__.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:07:57 by chanhpar          #+#    #+#             */
/*   Updated: 2023/01/17 21:57:26 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_TREE_HPP
#define FT_CONTAINERS_TREE_HPP

#include <algorithm>
#include <limits>
#include <memory>
#include "iterator.hpp"
#include "memory.hpp"
#include "utility.hpp"

namespace ft {

namespace detail {

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

template <typename T>
class rb_tree_value_node__ : public ft::detail::rb_tree_base_node__ {
 public:
  T val;
};

template <typename T>
class rb_tree_const_iterator__;

template <typename T>
class rb_tree_iterator__ {
  // class rb_tree_iterator__ {{{
 public:
  typedef ptrdiff_t difference_type;
  typedef T value_type;
  typedef T& reference;
  typedef T* pointer;
  typedef ft::bidirectional_iterator_tag iterator_category;

  rb_tree_base_node__* node__;

  typedef rb_tree_iterator__<T> self;

 private:
  // iterate_node {{{2

  void
  iter_next_node__(void) throw() {
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
  iter_prev_node__(void) throw() {
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
  rb_tree_iterator__(void) : node__() {
  }

  explicit rb_tree_iterator__(rb_tree_base_node__* x) : node__(x) {
  }

  rb_tree_iterator__(const self& it) : node__(it.node__) {
  }

  reference
  operator*() const {
    return (static_cast<rb_tree_value_node__<T>*>(node__)->val);
  }

  pointer
  operator->() const {
    return (ft::addressof(operator*()));
  }

  self&
  operator++(void) {
    iter_next_node__();
    return (*this);
  }

  self
  operator++(int) {
    self tmp__(*this);
    iter_next_node__();
    return (tmp__);
  }

  self&
  operator--(void) {
    iter_prev_node__();
    return (*this);
  }

  self
  operator--(int) {
    self tmp__(*this);
    iter_prev_node__();
    return (tmp__);
  }

  bool
  operator==(const self& other) const {
    return (this->node__ == other.node__);
  }

  bool
  operator!=(const self& other) const {
    return (this->node__ != other.node__);
  }

  bool
  operator==(const ft::detail::rb_tree_const_iterator__<T>& other) const {
    return (this->node__ == other.node__);
  }

  bool
  operator!=(const ft::detail::rb_tree_const_iterator__<T>& other) const {
    return (this->node__ != other.node__);
  }

  // class rb_tree_iterator__ }}}
};

template <typename T>
class rb_tree_const_iterator__ {
  // class rb_tree_const_iterator__ {{{

 public:
  typedef ptrdiff_t difference_type;
  typedef T value_type;
  typedef const T& reference;
  typedef const T* pointer;
  typedef ft::bidirectional_iterator_tag iterator_category;

  const rb_tree_base_node__* node__;

  typedef rb_tree_const_iterator__<T> self;

 private:
  // iterate_node {{{2

  void
  iter_next_node__(void) throw() {
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
  iter_prev_node__(void) throw() {
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
  rb_tree_const_iterator__(void) : node__() {
  }

  explicit rb_tree_const_iterator__(const rb_tree_base_node__* x) : node__(x) {
  }

  rb_tree_const_iterator__(const rb_tree_iterator__<T>& it) :
      node__(it.node__) {
  }

  reference
  operator*() const {
    return (static_cast<const rb_tree_value_node__<T>*>(node__)->val);
  }

  pointer
  operator->() const {
    return (ft::addressof(operator*()));
  }

  self&
  operator++(void) {
    iter_next_node__();
    return (*this);
  }

  self
  operator++(int) {
    self tmp__(*this);
    iter_next_node__();
    return (tmp__);
  }

  self&
  operator--(void) {
    iter_prev_node__();
    return (*this);
  }

  self
  operator--(int) {
    self tmp__(*this);
    iter_prev_node__();
    return (tmp__);
  }

  bool
  operator==(const self& other) const {
    return (this->node__ == other.node__);
  }

  bool
  operator!=(const self& other) const {
    return (this->node__ != other.node__);
  }

  bool
  operator==(const ft::detail::rb_tree_iterator__<T>& other) const {
    return (this->node__ == other.node__);
  }

  bool
  operator!=(const ft::detail::rb_tree_iterator__<T>& other) const {
    return (this->node__ != other.node__);
  }

  // class rb_tree_const_iterator__ }}}
};

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
  typedef rb_tree_base_node__ base_node__;
  typedef rb_tree_value_node__<value_type> value_node__;

  class rb_tree_alloc_base__ {
    // class rb_tree_alloc_base__ {{{
   public:
    typedef typename Allocator::template rebind<Value>::other allocator_type;

   protected:
    typename Allocator::template rebind<value_node__>::other node_allocator;

   public:
    rb_tree_alloc_base__(const allocator_type& a) :
        node_allocator(a),
        header(static_cast<base_node__*>(this->allocate_node__())) {
    }

    ~rb_tree_alloc_base__(void) {
      this->deallocate_node__(static_cast<value_node__*>(this->header));
    }

    allocator_type
    get_allocator(void) const {
      return (node_allocator);
    }

    base_node__* header;

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

 private:
  rb_tree_alloc_base__ Base__;
  size_type node_count__;
  key_compare comp__;

 public:
  typedef typename rb_tree_alloc_base__::allocator_type allocator_type;

  typedef rb_tree_iterator__<value_type> iterator;
  typedef rb_tree_const_iterator__<value_type> const_iterator;

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
  clone_node__(const value_node__* other) {
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

  base_node__*&
  _header__(void) {
    return (this->Base__.header);
  }

  const base_node__*
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

  value_node__*
  _begin__(void) {
    return (static_cast<value_node__*>(this->Base__.header->parent));
  }

  const value_node__*
  _begin__(void) const {
    return (static_cast<const value_node__*>(this->Base__.header->parent));
  }

  base_node__*
  _end__(void) {
    return (this->Base__.header);
  }

  const base_node__*
  _end__(void) const {
    return (this->Base__.header);
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

  static const key_type&
  _key__(const value_node__* x) {
    return (KeyFromValue()(x->val));
  }

  static const key_type&
  _key__(const base_node__* x) {
    return (KeyFromValue()(static_cast<const value_node__*>(x)->val));
  }

  static node_color__&
  _color__(base_node__* x) {
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

  static void
  rotate_left__(base_node__* x, base_node__*& root) {
    base_node__* const y__ = x->right;
    x->right = y__->left;
    if (y__->left != NULL)
      y__->left->parent = x;
    y__->parent = x->parent;

    if (x == root)
      root = y__;
    else if (x == x->parent->left)
      x->parent->left = y__;
    else
      x->parent->right = y__;

    y__->left = x;
    x->parent = y__;
  }

  static void
  rotate_right__(base_node__* x, base_node__*& root) {
    base_node__* const y__ = x->left;
    x->left = y__->right;
    if (y__->right != NULL)
      y__->right->parent = x;
    y__->parent = x->parent;

    if (x == root)
      root = y__;
    else if (x == x->parent->left)
      x->parent->left = y__;
    else
      x->parent->right = y__;

    y__->right = x;
    x->parent = y__;
  }

  // since x is newly inserted node, x's color is red and non-NULL
  static void
  rebalance_for_insert__(base_node__* x, base_node__*& root) throw() {
    // while x && x->parent are red, does not satisfy the rule
    while (x != root && x->parent->color == red__) {
      base_node__* grand_parent__ = x->parent->parent;

      if (x->parent == grand_parent__->left) {
        // x->parent == grand_parent__->left {{{
        base_node__* uncle__ = grand_parent__->right;

        if (uncle__ != NULL
            && uncle__->color == red__) {  //             gp(black)
          x->parent->color = black__;      //      p(red)    u(red)
          uncle__->color = black__;        //  ->         gp(red)
          grand_parent__->color = red__;   //      p(black)  u(black)
          x = grand_parent__;

        } else {
          if (x == x->parent->right) {    //             gp(black)
            x = x->parent;                //      p(red)    u(black)
            rotate_left__(x, root);       //  x(red)   y
          }                               //  ->         p(black)
          x->parent->color = black__;     //         x(red)   gp(red)
          grand_parent__->color = red__;  //                 y    u(black__)
          rotate_right__(grand_parent__, root);
          break;
        }

        // x->parent == grand_parent__->left }}}
      } else {
        // opposite direction {{{
        base_node__* uncle__ = grand_parent__->left;

        if (uncle__ && uncle__->color == red__) {
          x->parent->color = black__;
          uncle__->color = black__;
          grand_parent__->color = red__;
          x = grand_parent__;

        } else {
          if (x == x->parent->left) {
            x = x->parent;
            rotate_right__(x, root);
          }
          x->parent->color = black__;
          x->parent->parent->color = red__;
          rotate_left__(x->parent->parent, root);
          break;
        }
        // opposite direction }}}
      }
    }
    root->color = black__;
  }

  // insert new node with value v as y's child.
  // y must be unsaturated
  // bool will_insert_left = (x != NULL || y == this->_header__() ||
  // this->comp__(KeyFromValue()(v), _key__(y__))) )
  iterator
  insert_and_rebalance__(bool will_insert_left,
                         base_node__* y,
                         const value_type& v) {
    // insert_and_rebalance__ {{{
    value_node__* node_to_insert__ = this->create_node__(v);

    if (will_insert_left) {
      y->left = static_cast<base_node__*>(node_to_insert__);

      if (y == this->_header__()) {
        this->_root__() = node_to_insert__;
        this->_rightmost__() = node_to_insert__;

      } else if (y == this->_leftmost__()) {
        this->_leftmost__() = node_to_insert__;
      }
    } else {
      y->right = static_cast<base_node__*>(node_to_insert__);

      if (y == this->_rightmost__())
        this->_rightmost__() = node_to_insert__;
    }

    node_to_insert__->parent = y;
    node_to_insert__->left = NULL;
    node_to_insert__->right = NULL;
    node_to_insert__->color = red__;

    rebalance_for_insert__(node_to_insert__, _header__()->parent);
    ++(this->node_count__);
    // insert_and_rebalance__ }}}
    return (iterator(node_to_insert__));
  }

  // x and parent_new are newly linked by moving successor. need rebalance
  static void
  rebalance_for_erase__(base_node__*& x,
                        base_node__*& parent_new,
                        base_node__*& root) throw() {
    while (x != root && (x == NULL || x->color == black__)) {
      if (x == parent_new->left) {
        // x is a left child {{{
        base_node__* uncle__ = parent_new->right;
        if (uncle__->color == red__) {
          uncle__->color = black__;
          parent_new->color = red__;
          rotate_left__(parent_new, root);
          uncle__ = parent_new->right;
        }

        if ((uncle__->left == NULL || uncle__->left->color == black__)
            && (uncle__->right == NULL || uncle__->right->color == black__)) {
          uncle__->color = red__;
          x = parent_new;
          parent_new = parent_new->parent;

        } else {
          if (uncle__->right == NULL || uncle__->right->color == black__) {
            uncle__->left->color = black__;
            uncle__->color = red__;
            rotate_right__(uncle__, root);
            uncle__ = parent_new->right;
          }
          uncle__->color = parent_new->color;
          parent_new->color = black__;

          if (uncle__->right)
            uncle__->right->color = black__;

          rotate_left__(parent_new, root);
          break;
        }

        // x is a left child }}}
      } else {
        // opposite direction {{{

        base_node__* uncle__ = parent_new->left;
        if (uncle__->color == red__) {
          uncle__->color = black__;
          parent_new->color = red__;
          rotate_right__(parent_new, root);
          uncle__ = parent_new->left;
        }
        if ((uncle__->right == NULL || uncle__->right->color == black__)
            && (uncle__->left == NULL || uncle__->left->color == black__)) {
          uncle__->color = red__;
          x = parent_new;
          parent_new = parent_new->parent;

        } else {
          if (uncle__->left == NULL || uncle__->left->color == black__) {
            uncle__->right->color = black__;
            uncle__->color = red__;
            rotate_left__(uncle__, root);
            uncle__ = parent_new->left;
          }
          uncle__->color = parent_new->color;
          parent_new->color = black__;

          if (uncle__->left)
            uncle__->left->color = black__;

          rotate_right__(parent_new, root);
          break;
        }
        // opposite direction }}}
      }
    }
    if (x)
      x->color = black__;
  }

  static base_node__*
  erase_and_rebalance__(base_node__* const node_to_delete,
                        base_node__*& header) throw() {
    // erase_and_rebalance__ {{{
    base_node__*& root__ = header->parent;
    base_node__*& leftmost__ = header->left;
    base_node__*& rightmost__ = header->right;
    base_node__* succ__;
    base_node__* succ_child__;
    base_node__* parent_new__ = NULL;

    if (node_to_delete->left == NULL) {
      succ__ = node_to_delete;
      succ_child__ = succ__->right;

    } else if (node_to_delete->right == NULL) {
      succ__ = node_to_delete;
      succ_child__ = succ__->left;

    } else {
      succ__ = node_to_delete->right;
      while (succ__->left != NULL)
        succ__ = succ__->left;
      succ_child__ = succ__->right;
    }

    const node_color__ removed_color__ = succ__->color;

    if (succ__ != node_to_delete) {
      node_to_delete->left->parent = succ__;
      succ__->left = node_to_delete->left;

      if (succ__ == node_to_delete->right) {
        parent_new__ = succ__;

      } else {
        parent_new__ = succ__->parent;
        if (succ_child__)
          succ_child__->parent = parent_new__;

        parent_new__->left = succ_child__;
        succ__->right = node_to_delete->right;
        node_to_delete->right->parent = succ__;
      }

      if (node_to_delete == root__)
        root__ = succ__;
      else if (node_to_delete == node_to_delete->parent->left)
        node_to_delete->parent->left = succ__;
      else
        node_to_delete->parent->right = succ__;

      succ__->parent = node_to_delete->parent;

      succ__->color = node_to_delete->color;

    } else {
      // succ__ == node_to_delete i.e. node_to_delete has NULL child

      parent_new__ = node_to_delete->parent;
      if (succ_child__)
        succ_child__->parent = parent_new__;

      if (root__ == node_to_delete)
        root__ = succ_child__;
      else if (node_to_delete->parent->left == node_to_delete)
        node_to_delete->parent->left = succ_child__;
      else
        node_to_delete->parent->right = succ_child__;

      if (leftmost__ == node_to_delete) {
        if (succ_child__ == NULL)
          leftmost__ = node_to_delete->parent;
        else
          leftmost__ = local_leftmost__(succ_child__);
      }

      if (rightmost__ == node_to_delete) {
        if (succ_child__ == NULL)
          rightmost__ = node_to_delete->parent;
        else
          rightmost__ = local_rightmost__(succ_child__);
      }
    }

    if (removed_color__ == black__) {
      rebalance_for_erase__(succ_child__, parent_new__, root__);
    }
    return (node_to_delete);
    // erase_and_rebalance__  }}}
  }

  value_node__*
  copy_subtree__(const value_node__* x, value_node__* parent) {
    value_node__* tmp__;

    value_node__* top__ = this->clone_node__(x);
    top__->parent = parent;

    try {
      if (x->right != NULL) {
        top__->right
            = static_cast<base_node__*>(copy_subtree__(_right__(x), top__));
      }
      parent = top__;
      x = _left__(x);
      while (x != NULL) {
        tmp__ = this->clone_node__(x);
        parent->left = tmp__;
        tmp__->parent = parent;
        if (x->right != NULL)
          tmp__->right = copy_subtree__(_right__(x), tmp__);
        parent = tmp__;
        x = _left__(x);
      }
    } catch (...) {
      clear_subtree__(top__);
      throw;
    }
    return (top__);
  }

  // erase every nodes below x without balancing (inclusive)
  void
  clear_subtree__(value_node__* x) {
    value_node__* tmp__;
    while (x != NULL) {
      clear_subtree__(_right__(x));
      tmp__ = x;
      x = _left__(x);
      destroy_node__(tmp__);
    }
  }

  void
  empty_initialize(void) {
    _color__(this->_header__()) = red__;
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
      _color__(this->_header__()) = red__;
      this->_root__()
          = copy_subtree__(static_cast<const value_node__*>(other._root__()),
                           static_cast<value_node__*>(this->_header__()));
      this->_leftmost__() = local_leftmost__(this->_root__());
      this->_rightmost__() = local_rightmost__(this->_root__());
    }
  }

  rb_tree__<Key, Value, KeyFromValue, Compare, Allocator>&
  operator=(
      const rb_tree__<Key, Value, KeyFromValue, Compare, Allocator>& other) {
    if (this != &other) {
      this->clear();
      this->comp__ = other.comp__;

      if (other._root__() == NULL) {
        this->_root__() = NULL;
        this->_leftmost__() = this->_header__();
        this->_rightmost__() = this->_header__();
        this->node_count__ = 0;

      } else {
        this->_root__()
            = copy_subtree__(static_cast<const value_node__*>(other._root__()),
                             static_cast<value_node__*>(this->_header__()));
        this->_leftmost__() = local_leftmost__(this->_root__());
        this->_rightmost__() = local_rightmost__(this->_root__());
        this->node_count__ = other.node_count__;
      }
    }
    return (*this);
  }

  ~rb_tree__(void) {
    this->clear_subtree__(static_cast<value_node__*>(this->_root__()));
  }

  // ctor, operator=, dtor }}}

  // observer

  key_compare
  key_comp(void) const {
    return (this->comp__);
  }

  // iterator {{{

  iterator
  begin(void) {
    return (iterator(this->_leftmost__()));
  }

  const_iterator
  begin(void) const {
    return (const_iterator(this->_leftmost__()));
  }

  iterator
  end(void) {
    return (iterator(this->Base__.header));
  }

  const_iterator
  end(void) const {
    return (const_iterator(this->Base__.header));
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
    static const size_type maxSize__ = std::min<size_type>(
        static_cast<typename Allocator::template rebind<value_node__>::other>(
            this->get_allocator())
            .max_size(),
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

  ft::pair<iterator, bool>
  insert_unique(const value_type& v) {
    base_node__* y__ = this->_end__();
    value_node__* x__ = this->_begin__();
    const key_type key__ = KeyFromValue()(v);
    bool comp_value__ = true;

    while (x__ != NULL) {
      y__ = static_cast<base_node__*>(x__);
      comp_value__ = this->comp__(key__, _key__(x__));
      x__ = comp_value__ ? _left__(x__) : _right__(x__);
    }

    iterator it__(y__);

    if (comp_value__) {
      if (it__ == this->begin())
        return (ft::pair<iterator, bool>(insert_and_rebalance__(true, y__, v),
                                         true));
      --it__;
    }
    // XXX
    if (this->comp__(_key__(it__.node__), key__))
      return (ft::pair<iterator, bool>(
          insert_and_rebalance__(
              (y__ == this->_header__()) || comp_value__, y__, v),
          true));
    return (ft::pair<iterator, bool>(it__, false));
  }

  iterator
  insert_hint_unique(const_iterator pos, const value_type& v) {
    const key_type key__ = KeyFromValue()(v);
    const base_node__* x__;
    const base_node__* y__;

    if (pos.node__ == this->_end__()) {
      if (this->size() > 0
          && this->comp__(_key__(this->_rightmost__()), key__)) {
        x__ = NULL;
        y__ = this->_rightmost__();

      } else {
        return (insert_unique(v).first);
      }

    } else if (this->comp__(key__, _key__(pos.node__))) {
      const_iterator prev__(pos);

      if (pos.node__ == this->_leftmost__()) {
        x__ = this->_leftmost__();
        y__ = this->_leftmost__();

      } else if (this->comp__(_key__((--prev__).node__), key__)) {
        if (_right__(prev__.node__) == NULL) {
          x__ = NULL;
          y__ = prev__.node__;

        } else {
          x__ = pos.node__;
          y__ = pos.node__;
        }

      } else {
        return (insert_unique(v).first);
      }

    } else if (this->comp__(_key__(pos.node__), key__)) {
      const_iterator next__(pos);

      if (pos.node__ == this->_rightmost__()) {
        x__ = NULL;
        y__ = this->_rightmost__();

      } else if (this->comp__(key__, _key__((++next__).node__))) {
        if (_right__(pos.node__) == NULL) {
          x__ = NULL;
          y__ = pos.node__;

        } else {
          x__ = next__.node__;
          y__ = next__.node__;
        }

      } else {
        return (insert_unique(v).first);
      }

    } else {
      x__ = pos.node__;
      y__ = NULL;
    }

    bool will_insert_left = (x__ != NULL || y__ == this->_header__()
                             || this->comp__(KeyFromValue()(v), _key__(y__)));

    // XXX
    if (y__)
      return (insert_and_rebalance__(
          will_insert_left, const_cast<base_node__*>(y__), v));
    return (iterator(const_cast<base_node__*>(x__)));
  }

  template <typename InputIter>
  void
  insert_range_unique(InputIter first, InputIter last) {
    for (; first != last; ++first)
      insert_hint_unique(this->end(), *first);
  }

  // insert }}}

  // erase, clear {{{

  void
  erase(const_iterator pos) {
    value_node__* const tmp__
        = static_cast<value_node__* const>(erase_and_rebalance__(
            const_cast<base_node__* const>(pos.node__), this->_header__()));

    this->destroy_node__(tmp__);
    --this->node_count__;
  }

  size_type
  erase_unique(const key_type& x) {
    iterator it__ = this->find(x);
    if (it__ == this->end())
      return (0);
    this->erase(it__);
    return (1);
  }

  void
  erase(const_iterator first, const_iterator last) {
    if (first == this->begin() && last == this->end())
      this->clear();
    else {
      while (first != last) {
        this->erase(first++);
      }
    }
  }

  void
  clear(void) {
    if (this->node_count__ != 0) {
      this->clear_subtree__(static_cast<value_node__*>(this->_root__()));
      this->_leftmost__() = this->_header__();
      this->_root__() = NULL;
      this->_rightmost__() = this->_header__();
      this->node_count__ = 0;
    }
  }

  // erase, clear }}}

  // find {{{

  iterator
  find(const key_type& key) {
    value_node__* prev__ = static_cast<value_node__*>(this->_header__());
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
    const value_node__* prev__
        = static_cast<const value_node__*>(this->_header__());
    const value_node__* curr__
        = static_cast<const value_node__*>(prev__->parent);

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

  // find }}}

  // count_unique {{{

  size_type
  count_unique(const key_type& key) const {
    const value_node__* curr__
        = static_cast<const value_node__*>(this->_root__());

    while (curr__ != NULL) {
      if (this->comp__(_key__(curr__), key)) {
        curr__ = _right__(curr__);

      } else if (this->comp__(key, _key__(curr__))) {
        curr__ = _left__(curr__);

      } else {
        return (1);
      }
    }

    return (0);
  }

  // count_unique }}}

  // lower_bound {{{

  iterator
  lower_bound(const key_type& key) {
    value_node__* prev__ = static_cast<value_node__*>(this->_header__());
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
    const value_node__* prev__
        = static_cast<const value_node__*>(this->_header__());
    const value_node__* curr__
        = static_cast<const value_node__*>(prev__->parent);

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

  // lower_bound }}}

  // upper_bound {{{

  iterator
  upper_bound(const key_type& key) {
    value_node__* prev__ = static_cast<value_node__*>(this->_header__());
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
    const value_node__* prev__
        = static_cast<const value_node__*>(this->_header__());
    const value_node__* curr__
        = static_cast<const value_node__*>(prev__->parent);

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

  // upper_bound }}}

  // equal_range_unique {{{

  ft::pair<iterator, iterator>
  equal_range_unique(const key_type& key) {
    value_node__* prev__ = static_cast<value_node__*>(this->_header__());
    value_node__* curr__ = static_cast<value_node__*>(this->_root__());

    while (curr__ != NULL) {
      if (this->comp__(_key__(curr__), key)) {
        curr__ = _right__(curr__);

      } else if (this->comp__(key, _key__(curr__))) {
        prev__ = curr__;
        curr__ = _left__(curr__);
      } else {
        return (ft::pair<iterator, iterator>(
            iterator(curr__),
            iterator(curr__->right != NULL ? static_cast<value_node__*>(
                         local_leftmost__(curr__->right))
                                           : prev__)));
      }
    }
    return (ft::pair<iterator, iterator>(iterator(prev__), iterator(prev__)));
  }

  ft::pair<const_iterator, const_iterator>
  equal_range_unique(const key_type& key) const {
    const value_node__* prev__
        = static_cast<const value_node__*>(this->_header__());
    const value_node__* curr__
        = static_cast<const value_node__*>(this->_root__());

    while (curr__ != NULL) {
      if (this->comp__(_key__(curr__), key)) {
        curr__ = _right__(curr__);

      } else if (this->comp__(key, _key__(curr__))) {
        prev__ = curr__;
        curr__ = _left__(curr__);
      } else {
        return (ft::pair<const_iterator, const_iterator>(
            const_iterator(curr__),
            const_iterator(curr__->right != NULL ? static_cast<value_node__*>(
                               local_leftmost__(curr__->right))
                                                 : prev__)));
      }
    }
    return (ft::pair<const_iterator, const_iterator>(const_iterator(prev__),
                                                     const_iterator(prev__)));
  }

  // equal_range_unique }}}

 private:
  // debugging helper function {{{

  static size_type
  count_black_node__(const base_node__* node, const base_node__* root) throw() {
    if (node == NULL)
      return (0);
    size_type sum__ = 0;
    do {
      if (node->color == black__)
        ++sum__;
      if (node == root)
        break;
      node = node->parent;
    } while (1);
    return (sum__);
  }

  // }}}

 public:
  // debugging helper function {{{

  bool
  verify_tree__(void) const {
    if (this->node_count__ == 0 || this->begin() == this->end())
      return (this->node_count__ == 0 && this->begin() == this->end()
              && this->Base__.header->left == this->_end__()
              && this->Base__.header->right == this->_end__());

    size_type len__ = count_black_node__(this->_leftmost__(), this->_root__());
    for (const_iterator it__ = this->begin(); it__ != this->end(); ++it__) {
      const value_node__* x__ = static_cast<const value_node__*>(it__.node__);
      const value_node__* L__ = _left__(x__);
      const value_node__* R__ = _right__(x__);

      if (x__->color == red__)
        if ((L__ && L__->color == red__) || (R__ && R__->color == red__))
          return (false);

      if (L__ && this->comp__(_key__(x__), _key__(L__)))
        return (false);
      if (R__ && this->comp__(_key__(R__), _key__(x__)))
        return (false);

      if (!L__ && !R__ && count_black_node__(x__, this->_root__()) != len__)
        return (false);
    }

    if (_leftmost__() != local_leftmost__(this->_root__()))
      return (false);
    if (_rightmost__() != local_rightmost__(this->_root__()))
      return (false);
    return (true);
  }

  // debugging helper function }}}

};  // class rb_tree__

}  // namespace detail

}  // namespace ft

#endif  // FT_CONTAINERS_TREE_HPP
