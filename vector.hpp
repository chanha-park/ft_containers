/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 12:20:14 by chanhpar          #+#    #+#             */
/*   Updated: 2022/10/18 14:50:28 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

#include <memory>
#include "iterator.hpp"
#include "type_traits.hpp"

namespace ft {

// _Vector_alloc_base {{{

// The vector base class serves two purposes.  First, its constructor
// and destructor allocate (but don't initialize) storage.  This makes
// exception safety easier.  Second, the base class encapsulates all of
// the differences between SGI-style allocators and standard-conforming
// allocators.

// Base class for ordinary allocators.
template <class _Tp, class _Allocator, bool _IsStatic>
class _Vector_alloc_base {
 public:
  typedef
      typename _Alloc_traits<_Tp, _Allocator>::allocator_type allocator_type;

  allocator_type get_allocator() const {
    return _M_data_allocator;
  }

  _Vector_alloc_base(const allocator_type& __a) :
      _M_data_allocator(__a), _M_start(0), _M_finish(0), _M_end_of_storage(0) {
  }

 protected:
  allocator_type _M_data_allocator;
  _Tp* _M_start;
  _Tp* _M_finish;
  _Tp* _M_end_of_storage;

  _Tp* _M_allocate(size_t __n) {
    return _M_data_allocator.allocate(__n);
  }

  void _M_deallocate(_Tp* __p, size_t __n) {
    if (__p)
      _M_data_allocator.deallocate(__p, __n);
  }
};

// Specialization for allocators that have the property that we don't
// actually have to store an allocator object.
template <class _Tp, class _Allocator>
class _Vector_alloc_base<_Tp, _Allocator, true> {
 public:
  typedef
      typename _Alloc_traits<_Tp, _Allocator>::allocator_type allocator_type;

  allocator_type get_allocator() const {
    return allocator_type();
  }

  _Vector_alloc_base(const allocator_type&) :
      _M_start(0), _M_finish(0), _M_end_of_storage(0) {
  }

 protected:
  _Tp* _M_start;
  _Tp* _M_finish;
  _Tp* _M_end_of_storage;

  typedef typename _Alloc_traits<_Tp, _Allocator>::_Alloc_type _Alloc_type;

  _Tp* _M_allocate(size_t __n) {
    return _Alloc_type::allocate(__n);
  }

  void _M_deallocate(_Tp* __p, size_t __n) {
    _Alloc_type::deallocate(__p, __n);
  }
};

// _Vector_alloc_base }}}

// _Vector_base {{{

template <class _Tp, class _Alloc>
struct _Vector_base :
    public _Vector_alloc_base<_Tp,
                              _Alloc,
                              _Alloc_traits<_Tp, _Alloc>::_S_instanceless> {
  typedef _Vector_alloc_base<_Tp,
                             _Alloc,
                             _Alloc_traits<_Tp, _Alloc>::_S_instanceless>
      _Base;
  typedef typename _Base::allocator_type allocator_type;

  _Vector_base(const allocator_type& __a) : _Base(__a) {
  }

  _Vector_base(size_t __n, const allocator_type& __a) : _Base(__a) {
    _M_start = _M_allocate(__n);
    _M_finish = _M_start;
    _M_end_of_storage = _M_start + __n;
  }

  ~_Vector_base() {
    _M_deallocate(_M_start, _M_end_of_storage - _M_start);
  }
};

// _Vector_base }}}

// vector class {{{

template <class _Tp, class _Alloc = allocator<_Tp> >
class vector : protected _Vector_base<_Tp, _Alloc> {
 private:
  typedef _Vector_base<_Tp, _Alloc> _Base;
  typedef vector<_Tp, _Alloc> vector_type;

 public:
  typedef _Tp value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef __normal_iterator<pointer, vector_type> iterator;
  typedef __normal_iterator<const_pointer, vector_type> const_iterator;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

  typedef typename _Base::allocator_type allocator_type;

  allocator_type get_allocator() const {
    return _Base::get_allocator();
  }

  typedef reverse_iterator<const_iterator> const_reverse_iterator;
  typedef reverse_iterator<iterator> reverse_iterator;

 protected:
  using _Base::_M_allocate;
  using _Base::_M_deallocate;
  using _Base::_M_end_of_storage;
  using _Base::_M_finish;
  using _Base::_M_start;

 protected:
  void _M_insert_aux(iterator __position, const _Tp& __x);
  void _M_insert_aux(iterator __position);

 public:
  iterator begin() {
    return iterator(_M_start);
  }

  const_iterator begin() const {
    return const_iterator(_M_start);
  }

  iterator end() {
    return iterator(_M_finish);
  }

  const_iterator end() const {
    return const_iterator(_M_finish);
  }

  reverse_iterator rbegin() {
    return reverse_iterator(end());
  }

  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }

  reverse_iterator rend() {
    return reverse_iterator(begin());
  }

  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  }

  size_type size() const {
    return size_type(end() - begin());
  }

  size_type max_size() const {
    return size_type(-1) / sizeof(_Tp);
  }

  size_type capacity() const {
    return size_type(const_iterator(_M_end_of_storage) - begin());
  }

  bool empty() const {
    return begin() == end();
  }

  reference operator[](size_type __n) {
    return *(begin() + __n);
  }

  const_reference operator[](size_type __n) const {
    return *(begin() + __n);
  }

  void _M_range_check(size_type __n) const {
    if (__n >= this->size())
      __throw_out_of_range("vector");
  }

  reference at(size_type __n) {
    _M_range_check(__n);
    return (*this)[__n];
  }

  const_reference at(size_type __n) const {
    _M_range_check(__n);
    return (*this)[__n];
  }

  explicit vector(const allocator_type& __a = allocator_type()) : _Base(__a) {
  }

  vector(size_type __n,
         const _Tp& __value,
         const allocator_type& __a = allocator_type()) :
      _Base(__n, __a) {
    _M_finish = uninitialized_fill_n(_M_start, __n, __value);
  }

  explicit vector(size_type __n) : _Base(__n, allocator_type()) {
    _M_finish = uninitialized_fill_n(_M_start, __n, _Tp());
  }

  vector(const vector<_Tp, _Alloc>& __x) :
      _Base(__x.size(), __x.get_allocator()) {
    _M_finish = uninitialized_copy(__x.begin(), __x.end(), _M_start);
  }

  // Check whether it's an integral type.  If so, it's not an iterator.
  template <class _InputIterator>
  vector(_InputIterator __first,
         _InputIterator __last,
         const allocator_type& __a = allocator_type()) :
      _Base(__a) {
    typedef typename _Is_integer<_InputIterator>::_Integral _Integral;
    _M_initialize_aux(__first, __last, _Integral());
  }

  template <class _Integer>
  void _M_initialize_aux(_Integer __n, _Integer __value, __true_type) {
    _M_start = _M_allocate(__n);
    _M_end_of_storage = _M_start + __n;
    _M_finish = uninitialized_fill_n(_M_start, __n, __value);
  }

  template <class _InputIterator>
  void _M_initialize_aux(_InputIterator __first,
                         _InputIterator __last,
                         __false_type) {
    typedef typename iterator_traits<_InputIterator>::iterator_category
        _IterCategory;
    _M_range_initialize(__first, __last, _IterCategory());
  }

  ~vector() {
    _Destroy(_M_start, _M_finish);
  }

  vector<_Tp, _Alloc>& operator=(const vector<_Tp, _Alloc>& __x);

  void reserve(size_type __n) {
    if (capacity() < __n) {
      const size_type __old_size = size();
      pointer __tmp = _M_allocate_and_copy(__n, _M_start, _M_finish);
      _Destroy(_M_start, _M_finish);
      _M_deallocate(_M_start, _M_end_of_storage - _M_start);
      _M_start = __tmp;
      _M_finish = __tmp + __old_size;
      _M_end_of_storage = _M_start + __n;
    }
  }

  // assign(), a generalized assignment member function.  Two
  // versions: one that takes a count, and one that takes a range.
  // The range version is a member template, so we dispatch on whether
  // or not the type is an integer.

  void assign(size_type __n, const _Tp& __val) {
    _M_fill_assign(__n, __val);
  }

  void _M_fill_assign(size_type __n, const _Tp& __val);

  template <class _InputIterator>
  void assign(_InputIterator __first, _InputIterator __last) {
    typedef typename _Is_integer<_InputIterator>::_Integral _Integral;
    _M_assign_dispatch(__first, __last, _Integral());
  }

  template <class _Integer>
  void _M_assign_dispatch(_Integer __n, _Integer __val, __true_type) {
    _M_fill_assign((size_type)__n, (_Tp)__val);
  }

  template <class _InputIter>
  void _M_assign_dispatch(_InputIter __first, _InputIter __last, __false_type) {
    typedef
        typename iterator_traits<_InputIter>::iterator_category _IterCategory;
    _M_assign_aux(__first, __last, _IterCategory());
  }

  template <class _InputIterator>
  void _M_assign_aux(_InputIterator __first,
                     _InputIterator __last,
                     input_iterator_tag);

  template <class _ForwardIterator>
  void _M_assign_aux(_ForwardIterator __first,
                     _ForwardIterator __last,
                     forward_iterator_tag);

  reference front() {
    return *begin();
  }

  const_reference front() const {
    return *begin();
  }

  reference back() {
    return *(end() - 1);
  }

  const_reference back() const {
    return *(end() - 1);
  }

  void push_back(const _Tp& __x) {
    if (_M_finish != _M_end_of_storage) {
      _Construct(_M_finish, __x);
      ++_M_finish;
    } else
      _M_insert_aux(end(), __x);
  }

  void push_back() {
    if (_M_finish != _M_end_of_storage) {
      _Construct(_M_finish);
      ++_M_finish;
    } else
      _M_insert_aux(end());
  }

  void swap(vector<_Tp, _Alloc>& __x) {
    std::swap(_M_start, __x._M_start);
    std::swap(_M_finish, __x._M_finish);
    std::swap(_M_end_of_storage, __x._M_end_of_storage);
  }

  iterator insert(iterator __position, const _Tp& __x) {
    size_type __n = __position - begin();
    if (_M_finish != _M_end_of_storage && __position == end()) {
      _Construct(_M_finish, __x);
      ++_M_finish;
    } else
      _M_insert_aux(iterator(__position), __x);
    return begin() + __n;
  }

  iterator insert(iterator __position) {
    size_type __n = __position - begin();
    if (_M_finish != _M_end_of_storage && __position == end()) {
      _Construct(_M_finish);
      ++_M_finish;
    } else
      _M_insert_aux(iterator(__position));
    return begin() + __n;
  }

  // Check whether it's an integral type.  If so, it's not an iterator.
  template <class _InputIterator>
  void insert(iterator __pos, _InputIterator __first, _InputIterator __last) {
    typedef typename _Is_integer<_InputIterator>::_Integral _Integral;
    _M_insert_dispatch(__pos, __first, __last, _Integral());
  }

  template <class _Integer>
  void _M_insert_dispatch(iterator __pos,
                          _Integer __n,
                          _Integer __val,
                          __true_type) {
    _M_fill_insert(__pos, static_cast<size_type>(__n), static_cast<_Tp>(__val));
  }

  template <class _InputIterator>
  void _M_insert_dispatch(iterator __pos,
                          _InputIterator __first,
                          _InputIterator __last,
                          __false_type) {
    typedef typename iterator_traits<_InputIterator>::iterator_category
        _IterCategory;
    _M_range_insert(__pos, __first, __last, _IterCategory());
  }

  void insert(iterator __pos, size_type __n, const _Tp& __x) {
    _M_fill_insert(__pos, __n, __x);
  }

  void _M_fill_insert(iterator __pos, size_type __n, const _Tp& __x);

  void pop_back() {
    --_M_finish;
    _Destroy(_M_finish);
  }

  iterator erase(iterator __position) {
    if (__position + 1 != end())
      copy(__position + 1, end(), __position);
    --_M_finish;
    _Destroy(_M_finish);
    return __position;
  }

  iterator erase(iterator __first, iterator __last) {
    iterator __i(copy(__last, end(), __first));
    _Destroy(__i, end());
    _M_finish = _M_finish - (__last - __first);
    return __first;
  }

  void resize(size_type __new_size, const _Tp& __x) {
    if (__new_size < size())
      erase(begin() + __new_size, end());
    else
      insert(end(), __new_size - size(), __x);
  }

  void resize(size_type __new_size) {
    resize(__new_size, _Tp());
  }

  void clear() {
    erase(begin(), end());
  }

 protected:
  template <class _ForwardIterator>
  pointer _M_allocate_and_copy(size_type __n,
                               _ForwardIterator __first,
                               _ForwardIterator __last) {
    pointer __result = _M_allocate(__n);
    try {
      uninitialized_copy(__first, __last, __result);
      return __result;
    } catch (...) {
      _M_deallocate(__result, __n);
      __throw_exception_again;
    }
  }

  template <class _InputIterator>
  void _M_range_initialize(_InputIterator __first,
                           _InputIterator __last,
                           input_iterator_tag) {
    for (; __first != __last; ++__first)
      push_back(*__first);
  }

  // This function is only called by the constructor.
  template <class _ForwardIterator>
  void _M_range_initialize(_ForwardIterator __first,
                           _ForwardIterator __last,
                           forward_iterator_tag) {
    size_type __n = distance(__first, __last);
    _M_start = _M_allocate(__n);
    _M_end_of_storage = _M_start + __n;
    _M_finish = uninitialized_copy(__first, __last, _M_start);
  }

  template <class _InputIterator>
  void _M_range_insert(iterator __pos,
                       _InputIterator __first,
                       _InputIterator __last,
                       input_iterator_tag);

  template <class _ForwardIterator>
  void _M_range_insert(iterator __pos,
                       _ForwardIterator __first,
                       _ForwardIterator __last,
                       forward_iterator_tag);
};

// vector class }}}

}  // namespace ft

#endif  // FT_CONTAINERS_VECTOR_HPP
