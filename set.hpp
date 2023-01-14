/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 19:09:39 by chanhpar          #+#    #+#             */
/*   Updated: 2023/01/12 09:53:59 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_SET_HPP
#define FT_CONTAINERS_SET_HPP

#include <functional>
#include <memory>
#include "algorithm.hpp"
#include "iterator.hpp"
#include "tree__.hpp"
#include "utility.hpp"

namespace ft {

template <typename Key,
          typename Compare = std::less<Key>,
          typename Allocator = std::allocator<Key> >
class set {
 public:
  typedef Key key_type;
  typedef Key value_type;
  typedef Compare key_compare;
  typedef Compare value_compare;
  typedef Allocator allocator_type;

  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef typename Allocator::pointer pointer;
  typedef typename Allocator::const_pointer const_pointer;

  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;

 private:
  typedef typename ft::rb_tree__<key_type,
                                 value_type,
                                 ft::functor_identity__<value_type>,
                                 key_compare,
                                 allocator_type>
      tree_type__;

  tree_type__ tree__;

 public:
  typedef typename tree_type__::iterator iterator;
  typedef typename tree_type__::const_iterator const_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

 protected:
 public:
  // constructor {{{

  set(void) : tree__(key_compare(), allocator_type()) {
  }

  explicit set(const key_compare& cmp,
               const allocator_type& alloc = allocator_type()) :
      tree__(cmp, alloc) {
  }

  template <typename InputIter>
  set(InputIter first, InputIter last) :
      tree__(key_compare(), allocator_type()) {
    tree__.insert_range_unique(first, last);
  }

  template <typename InputIter>
  set(InputIter first,
      InputIter last,
      const key_compare& cmp,
      const allocator_type& alloc = allocator_type()) :
      tree__(cmp, alloc) {
    tree__.insert_range_unique(first, last);
  }

  set(const ft::set<key_type, key_compare, allocator_type>& other) :
      tree__(other.tree__) {
  }

  // constructor }}}

  // operator= overload {{{

  set<key_type, key_compare, allocator_type>&
  operator=(const set<key_type, key_compare, allocator_type>& x) {
    this->tree__ = x.tree__;
    return (*this);
  }

  // operator= overload }}}

  allocator_type
  get_allocator(void) const {
    return (tree__.get_allocator());
  }

  // iterators {{{

  iterator
  begin(void) {
    return (tree__.begin());
  }

  const_iterator
  begin(void) const {
    return (tree__.begin());
  }

  iterator
  end(void) {
    return (tree__.end());
  }

  const_iterator
  end(void) const {
    return (tree__.end());
  }

  reverse_iterator
  rbegin(void) {
    return (reverse_iterator(tree__.end()));
  }

  const_reverse_iterator
  rbegin(void) const {
    return (const_reverse_iterator(tree__.end()));
  }

  reverse_iterator
  rend(void) {
    return (reverse_iterator(tree__.begin()));
  }

  const_reverse_iterator
  rend(void) const {
    return (const_reverse_iterator(tree__.begin()));
  }

  // iterators }}}

  // capacity {{{

  bool
  empty(void) const {
    return (tree__.empty());
  }

  size_type
  size(void) const {
    return (tree__.size());
  }

  size_type
  max_size(void) const {
    return (tree__.max_size());
  }

  // capacity }}}

  // modifiers {{{

  void
  clear(void) {
    tree__.clear();
  }

  ft::pair<iterator, bool>
  insert(const value_type& value) {
    return (tree__.insert_unique(value));
  }

  iterator
  insert(iterator pos, const value_type& value) {
    return (tree__.insert_hint_unique(pos, value));
  }

  template <typename InputIter>
  void
  insert(InputIter first, InputIter last) {
    tree__.insert_range_unique(first, last);
  }

  void
  erase(iterator pos) {
    tree__.erase(pos);
  }

  void
  erase(iterator first, iterator last) {
    tree__.erase(first, last);
  }

  size_type
  erase(const key_type& k) {
    return (tree__.erase_unique(k));
  }

  void
  swap(ft::set<key_type, key_compare, allocator_type>& other) {
    tree__.swap(other.tree__);
  }

  // modifiers }}}

  // lookup {{{

  size_type
  count(const key_type& k) const {
    return (tree__.count_unique(k));
  }

  iterator
  find(const key_type& k) {
    return (tree__.find(k));
  }

  const_iterator
  find(const key_type& k) const {
    return (tree__.find(k));
  }

  ft::pair<iterator, iterator>
  equal_range(const key_type& k) {
    return (tree__.equal_range_unique(k));
  }

  ft::pair<const_iterator, const_iterator>
  equal_range(const key_type& k) const {
    return (tree__.equal_range_unique(k));
  }

  iterator
  lower_bound(const key_type& k) {
    return (tree__.lower_bound(k));
  }

  const_iterator
  lower_bound(const key_type& k) const {
    return (tree__.lower_bound(k));
  }

  iterator
  upper_bound(const key_type& k) {
    return (tree__.upper_bound(k));
  }

  const_iterator
  upper_bound(const key_type& k) const {
    return (tree__.upper_bound(k));
  }

  // lookup }}}

  key_compare
  key_comp(void) const {
    return (tree__.key_comp());
  }

  value_compare
  value_comp(void) const {
    return (value_compare(tree__.key_comp()));
  }

  // relational operator {{{

  bool
  operator==(
      const ft::set<key_type, key_compare, allocator_type>& other) const {
    return (this->size() == other.size()
            && ft::equal(this->begin(), this->end(), other.begin()));
  }

  bool
  operator!=(
      const ft::set<key_type, key_compare, allocator_type>& other) const {
    return (!(*this == other));
  }

  bool
  operator<(const ft::set<key_type, key_compare, allocator_type>& other) const {
    return (ft::lexicographical_compare(
        this->begin(), this->end(), other.begin(), other.end()));
  }

  bool
  operator<=(
      const ft::set<key_type, key_compare, allocator_type>& other) const {
    return (!(other < *this));
  }

  bool
  operator>(const ft::set<key_type, key_compare, allocator_type>& other) const {
    return (other < *this);
  }

  bool
  operator>=(
      const ft::set<key_type, key_compare, allocator_type>& other) const {
    return (!(*this < other));
  }

  // relational operator }}}
};

template <typename Key, typename Compare, typename Allocator>
void
swap(ft::set<Key, Compare, Allocator>& x, ft::set<Key, Compare, Allocator>& y) {
  x.swap(y);
}

}  // namespace ft

#endif  // FT_CONTAINERS_SET_HPP
