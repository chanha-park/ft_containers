/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 12:20:14 by chanhpar          #+#    #+#             */
/*   Updated: 2022/10/28 21:47:29 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

#include <algorithm>
#include <memory>
#include "algorithm.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"

namespace ft {

// vector_iterator {{{1

// vector_iterator class {{{2

template <typename Iterator, typename Container>
class vector_iterator :
    public ft::iterator<
        typename ft::iterator_traits<Iterator>::iterator_category,
        typename ft::iterator_traits<Iterator>::value_type,
        typename ft::iterator_traits<Iterator>::difference_type,
        typename ft::iterator_traits<Iterator>::pointer,
        typename ft::iterator_traits<Iterator>::reference> {
 protected:
  Iterator current;

 public:
  typedef
      typename ft::iterator_traits<Iterator>::difference_type difference_type;
  typedef typename ft::iterator_traits<Iterator>::reference reference;
  typedef typename ft::iterator_traits<Iterator>::pointer pointer;

  vector_iterator(void) : current(Iterator()) {
  }

  explicit vector_iterator(const Iterator& it) : current(it) {
  }

  template <typename U>
  vector_iterator(const vector_iterator<U, Container>& u) : current(u.base()) {
  }

  const Iterator& base() const {
    return (current);
  }

  reference operator*(void) const {
    return (*current);
  }

  reference operator*(void) {
    return (*current);
  }

  pointer operator->(void) const {
    return (current);
  }

  vector_iterator& operator++(void) {
    ++current;
    return (*this);
  }

  vector_iterator operator++(int) {
    vector_iterator tmp__(*this);
    ++current;
    return (tmp__);
  }

  vector_iterator& operator--(void) {
    --current;
    return (*this);
  }

  vector_iterator operator--(int) {
    vector_iterator tmp__(*this);
    --current;
    return (tmp__);
  }

  vector_iterator operator+(const difference_type& n) const {
    vector_iterator tmp__(current + n);
    return (tmp__);
  }

  vector_iterator operator-(const difference_type& n) const {
    return vector_iterator(current - n);
  }

  vector_iterator& operator+=(const difference_type& n) {
    current += n;
    return (*this);
  }

  vector_iterator& operator-=(const difference_type& n) {
    current -= n;
    return (*this);
  }

  reference operator[](const difference_type& n) const {
    return (current[n]);
  }
};

// vector_iterator class }}}

template <typename Iter1, typename Iter2, typename Container>
bool operator==(const vector_iterator<Iter1, Container>& x,
                const vector_iterator<Iter2, Container>& y) {
  return (x.base() == y.base());
}

template <typename Iter1, typename Iter2, typename Container>
bool operator!=(const vector_iterator<Iter1, Container>& x,
                const vector_iterator<Iter2, Container>& y) {
  return (!(x == y));
}

template <typename Iter1, typename Iter2, typename Container>
bool operator<(const vector_iterator<Iter1, Container>& x,
               const vector_iterator<Iter2, Container>& y) {
  return (x.base() < y.base());
}

template <typename Iter1, typename Iter2, typename Container>
bool operator>(const vector_iterator<Iter1, Container>& x,
               const vector_iterator<Iter2, Container>& y) {
  return (y < x);
}

template <typename Iter1, typename Iter2, typename Container>
bool operator<=(const vector_iterator<Iter1, Container>& x,
                const vector_iterator<Iter2, Container>& y) {
  return (!(y < x));
}

template <typename Iter1, typename Iter2, typename Container>
bool operator>=(const vector_iterator<Iter1, Container>& x,
                const vector_iterator<Iter2, Container>& y) {
  return (!(x < y));
}

template <typename Iter1, typename Iter2, typename Container>
typename vector_iterator<Iter1, Container>::difference_type operator-(
    const vector_iterator<Iter1, Container>& x,
    const vector_iterator<Iter2, Container>& y) {
  return (x.base() - y.base());
}

template <typename Iterator, typename Container>
vector_iterator<Iterator, Container> operator+(
    typename vector_iterator<Iterator, Container>::difference_type n,
    const vector_iterator<Iterator, Container>& x) {
  return vector_iterator<Iterator, Container>(x.base() + n);
}

// vector_iterator }}}

// vector_alloc_base_ {{{

// template <typename T, typename Allocator, bool IsStatic>
template <typename T, typename Allocator>
class vector_alloc_base_ {
 public:
  typedef typename Allocator::template rebind<T>::other allocator_type;

 protected:
  allocator_type data_allocator;
  T* start;
  T* finish;
  T* end_of_storage;

  T* allocate_(size_t n) {
    return (data_allocator.allocate(n));
  }

  void deallocate_(T* p, size_t n) {
    if (p)
      data_allocator.deallocate(p, n);
  }

 protected:
  vector_alloc_base_(const allocator_type& x) :
      data_allocator(x), start(0), finish(0), end_of_storage(0) {
  }

 public:
  virtual ~vector_alloc_base_(void) {
  }

  allocator_type get_allocator(void) const {
    return (data_allocator);
  }
};

// vector_alloc_base_ }}}

// vector_base_ {{{

template <typename T, typename Allocator>
struct vector_base_ : protected vector_alloc_base_<T, Allocator> {
 public:
  typedef vector_alloc_base_<T, Allocator> Base_;
  typedef typename Base_::allocator_type allocator_type;

 protected:
  vector_base_(const allocator_type& x) : Base_(x) {
  }

  vector_base_(size_t n, const allocator_type& x) : Base_(x) {
    Base_::start = Base_::allocate_(n);
    Base_::finish = Base_::start;
    Base_::end_of_storage = Base_::start + n;
  }

 public:
  virtual ~vector_base_() {
    Base_::deallocate_(Base_::start, Base_::end_of_storage - Base_::start);
  }
};

// vector_base_ }}}

template <class T, class Allocator = std::allocator<T> >
class vector : protected vector_base_<T, Allocator> {
 private:
  typedef vector_base_<T, Allocator> Base_;
  typedef vector<T, Allocator> vector_type;

 public:
  typedef T value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;

  typedef vector_iterator<pointer, vector_type> iterator;
  typedef vector_iterator<const_pointer, vector_type> const_iterator;

  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

  typedef typename Base_::allocator_type allocator_type;

  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;

 protected:
  // using Base_::allocate_;
  // using Base_::deallocate_;
  using Base_::end_of_storage;
  using Base_::finish;
  using Base_::start;

 private:
  // _M_insert_aux {{{

  void _M_insert_aux(iterator __position, const T& __x) {
    if (finish != end_of_storage) {
      constructObject_(finish, *(finish - 1));
      ++finish;
      T __x_copy = __x;
      std::copy_backward(
          __position, iterator(finish - 2), iterator(finish - 1));
      *__position = __x_copy;
    } else {
      const size_type __old_size = size();
      const size_type __len = __old_size != 0 ? 2 * __old_size : 1;
      iterator __new_start(Base_::allocate_(__len));
      iterator __new_finish(__new_start);
      try {
        __new_finish
            = std::uninitialized_copy(iterator(start), __position, __new_start);
        constructObject_(__new_finish.base(), __x);
        ++__new_finish;
        __new_finish = std::uninitialized_copy(
            __position, iterator(finish), __new_finish);
      } catch (...) {
        destructObject_(__new_start, __new_finish);
		Base_::deallocate_(__new_start.base(), __len);
        throw;
      }
      destructObject_(begin(), end());
	  Base_::deallocate_(start, end_of_storage - start);
      start = __new_start.base();
      finish = __new_finish.base();
      end_of_storage = __new_start.base() + __len;
    }
  }

  // _M_insert_aux }}}

  // _M_insert_aux {{{

  void _M_insert_aux(iterator __position) {
    if (finish != end_of_storage) {
      constructObject_(finish, *(finish - 1));
      ++finish;
      std::copy_backward(
          __position, iterator(finish - 2), iterator(finish - 1));
      *__position = T();
    } else {
      const size_type __old_size = size();
      const size_type __len = __old_size != 0 ? 2 * __old_size : 1;
      pointer __new_start = Base_::allocate_(__len);
      pointer __new_finish = __new_start;
      try {
        __new_finish
            = std::uninitialized_copy(iterator(start), __position, __new_start);
        constructObject_(__new_finish);
        ++__new_finish;
        __new_finish = std::uninitialized_copy(
            __position, iterator(finish), __new_finish);
      } catch (...) {
        destructObject_(__new_start, __new_finish);
		Base_::deallocate_(__new_start, __len);
        throw;
      }
      destructObject_(begin(), end());
	  Base_::deallocate_(start, end_of_storage - start);
      start = __new_start;
      finish = __new_finish;
      end_of_storage = __new_start + __len;
    }
  }

  // _M_insert_aux }}}

  // _M_fill_assign {{{

  void _M_fill_assign(size_type __n, const T& __val) {
    if (__n > capacity()) {
      vector<T, Allocator> __tmp(__n, __val, get_allocator());
      __tmp.swap(*this);
    } else if (__n > size()) {
      std::fill(begin(), end(), __val);
      finish = std::uninitialized_fill_n(finish, __n - size(), __val);
    } else
      erase(std::fill_n(begin(), __n, __val), end());
  }

  // _M_fill_assign }}}

  // _M_fill_insert {{{

  void _M_fill_insert(iterator __pos, size_type __n, const T& __x) {
    if (__n != 0) {
      if (size_type(end_of_storage - finish) >= __n) {
        T __x_copy = __x;
        const size_type __elems_after = end() - __pos;
        iterator __old_finish(finish);
        if (__elems_after > __n) {
          std::uninitialized_copy(finish - __n, finish, finish);
          finish += __n;
          std::copy_backward(__pos, __old_finish - __n, __old_finish);
          std::fill(__pos, __pos + __n, __x_copy);
        } else {
          std::uninitialized_fill_n(finish, __n - __elems_after, __x_copy);
          finish += __n - __elems_after;
          std::uninitialized_copy(__pos, __old_finish, finish);
          finish += __elems_after;
          std::fill(__pos, __old_finish, __x_copy);
        }
      } else {
        const size_type __old_size = size();
        const size_type __len = __old_size + std::max(__old_size, __n);
        iterator __new_start(Base_::allocate_(__len));
        iterator __new_finish(__new_start);
        try {
          __new_finish = std::uninitialized_copy(begin(), __pos, __new_start);
          __new_finish = std::uninitialized_fill_n(__new_finish, __n, __x);
          __new_finish = std::uninitialized_copy(__pos, end(), __new_finish);
        } catch (...) {
          destructObject_(__new_start, __new_finish);
		  Base_::deallocate_(__new_start.base(), __len);
          throw;
        }
        destructObject_(start, finish);
		Base_::deallocate_(start, end_of_storage - start);
        start = __new_start.base();
        finish = __new_finish.base();
        end_of_storage = __new_start.base() + __len;
      }
    }
  }

  // _M_fill_insert }}}

  // _M_assign_aux {{{
  template <class _InputIterator>
  void _M_assign_aux(_InputIterator __first,
                     _InputIterator __last,
                     input_iterator_tag) {
    iterator __cur(begin());
    for (; __first != __last && __cur != end(); ++__cur, ++__first)
      *__cur = *__first;
    if (__first == __last)
      erase(__cur, end());
    else
      insert(end(), __first, __last);
  }

  // _M_assign_aux }}}

  // _M_assign_aux {{{
  template <class _ForwardIter>
  void _M_assign_aux(_ForwardIter __first,
                     _ForwardIter __last,
                     forward_iterator_tag) {
    size_type __len = ft::distance(__first, __last);

    if (__len > capacity()) {
      pointer __tmp(_M_allocate_and_copy(__len, __first, __last));
      destructObject_(start, finish);
	  Base_::deallocate_(start, end_of_storage - start);
      start = __tmp;
      end_of_storage = finish = start + __len;
    } else if (size() >= __len) {
      iterator __new_finish(std::copy(__first, __last, start));
      destructObject_(__new_finish, end());
      finish = __new_finish.base();
    } else {
      _ForwardIter __mid = __first;
      ft::advance(__mid, size());
      std::copy(__first, __mid, start);
      finish = std::uninitialized_copy(__mid, __last, finish);
    }
  }

  // _M_assign_aux }}}

  // _M_range_insert {{{
  template <class _InputIterator>
  void _M_range_insert(iterator __pos,
                       _InputIterator __first,
                       _InputIterator __last,
                       input_iterator_tag) {
    for (; __first != __last; ++__first) {
      __pos = insert(__pos, *__first);
      ++__pos;
    }
  }

  // _M_range_insert }}}

  // _M_range_insert {{{
  template <class _ForwardIterator>
  void _M_range_insert(iterator __pos,
                       _ForwardIterator __first,
                       _ForwardIterator __last,
                       forward_iterator_tag) {
    if (__first != __last) {
      size_type __n = ft::distance(__first, __last);
      if (size_type(end_of_storage - finish) >= __n) {
        const size_type __elems_after = end() - __pos;
        iterator __old_finish(finish);
        if (__elems_after > __n) {
          std::uninitialized_copy(finish - __n, finish, finish);
          finish += __n;
          std::copy_backward(__pos, __old_finish - __n, __old_finish);
          std::copy(__first, __last, __pos);
        } else {
          _ForwardIterator __mid = __first;
          ft::advance(__mid, __elems_after);
          std::uninitialized_copy(__mid, __last, finish);
          finish += __n - __elems_after;
          std::uninitialized_copy(__pos, __old_finish, finish);
          finish += __elems_after;
          std::copy(__first, __mid, __pos);
        }
      } else {
        const size_type __old_size = size();
        const size_type __len = __old_size + std::max(__old_size, __n);
        iterator __new_start(Base_::allocate_(__len));
        iterator __new_finish(__new_start);
        try {
          __new_finish
              = std::uninitialized_copy(iterator(start), __pos, __new_start);
          __new_finish = std::uninitialized_copy(__first, __last, __new_finish);
          __new_finish
              = std::uninitialized_copy(__pos, iterator(finish), __new_finish);
        } catch (...) {
          destructObject_(__new_start, __new_finish);
		  Base_::deallocate_(__new_start.base(), __len);
          throw;
        }
        destructObject_(start, finish);
		Base_::deallocate_(start, end_of_storage - start);
        start = __new_start.base();
        finish = __new_finish.base();
        end_of_storage = __new_start.base() + __len;
      }
    }
  }

  // _M_range_insert }}}

 protected:
 public:
  allocator_type get_allocator() const {
    return Base_::get_allocator();
  }

  const_iterator begin() const {
    return const_iterator(start);
  }

  iterator begin() {
    return iterator(start);
  }

  const_iterator end() const {
    return const_iterator(finish);
  }

  iterator end() {
    return iterator(finish);
  }

  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }

  reverse_iterator rbegin() {
    return reverse_iterator(end());
  }

  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  }

  reverse_iterator rend() {
    return reverse_iterator(begin());
  }

  size_type size() const {
    return size_type(end() - begin());
  }

  size_type max_size() const {
    return (size_type(-1) / sizeof(T)) >> (sizeof(T) == 1);
  }

  size_type capacity() const {
    return size_type(const_iterator(end_of_storage) - begin());
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
      std::__throw_out_of_range("vector");
  }

  reference at(size_type __n) {
    _M_range_check(__n);
    return (*this)[__n];
  }

  const_reference at(size_type __n) const {
    _M_range_check(__n);
    return (*this)[__n];
  }

  explicit vector(const allocator_type& __a = allocator_type()) : Base_(__a) {
  }

  vector(size_type __n,
         const T& __value,
         const allocator_type& __a = allocator_type()) :
      Base_(__n, __a) {
    finish = std::uninitialized_fill_n(start, __n, __value);
  }

  explicit vector(size_type __n) : Base_(__n, allocator_type()) {
    finish = std::uninitialized_fill_n(start, __n, T());
  }

  vector(const vector<T, Allocator>& __x) :
      Base_(__x.size(), __x.get_allocator()) {
    finish = std::uninitialized_copy(__x.begin(), __x.end(), start);
  }

  template <class _InputIterator>
  vector(_InputIterator __first,
         _InputIterator __last,
         const allocator_type& __a = allocator_type()) :
      Base_(__a) {
    _M_initialize_aux(__first, __last);
  }

  template <class _Integer>
  typename ft::enable_if<ft::is_integral<_Integer>::value, void>::type
  _M_initialize_aux(_Integer __n, _Integer __value) {
    start = Base_::allocate_(__n);
    end_of_storage = start + __n;
    finish = std::uninitialized_fill_n(start, __n, __value);
  }

  template <class _InputIterator>
  typename ft::enable_if<!ft::is_integral<_InputIterator>::value, void>::type
  _M_initialize_aux(_InputIterator __first, _InputIterator __last) {
    typedef typename iterator_traits<_InputIterator>::iterator_category
        _IterCategory;
    _M_range_initialize(__first, __last, _IterCategory());
  }

  ~vector() {
    destructObject_(start, finish);
  }

  vector<T, Allocator>& operator=(const vector<T, Allocator>& __x) {
    if (&__x != this) {
      const size_type __xlen = __x.size();
      if (__xlen > capacity()) {
        pointer __tmp = _M_allocate_and_copy(__xlen, __x.begin(), __x.end());
        destructObject_(start, finish);
		Base_::deallocate_(start, end_of_storage - start);
        start = __tmp;
        end_of_storage = start + __xlen;
      } else if (size() >= __xlen) {
        iterator __i(std::copy(__x.begin(), __x.end(), begin()));
        destructObject_(__i, end());
      } else {
        std::copy(__x.begin(), __x.begin() + size(), start);
        std::uninitialized_copy(__x.begin() + size(), __x.end(), finish);
      }
      finish = start + __xlen;
    }
    return *this;
  }

  void reserve(size_type __n) {
    if (capacity() < __n) {
      const size_type __old_size = size();
      pointer __tmp = _M_allocate_and_copy(__n, start, finish);
      destructObject_(start, finish);
	  Base_::deallocate_(start, end_of_storage - start);
      start = __tmp;
      finish = __tmp + __old_size;
      end_of_storage = start + __n;
    }
  }

  // assign(), a generalized assignment member function.  Two
  // versions: one that takes a count, and one that takes a range.
  // The range version is a member template, so we dispatch on whether
  // or not the type is an integer.

  void assign(size_type __n, const T& __val) {
    _M_fill_assign(__n, __val);
  }

  template <class _InputIterator>
  void assign(_InputIterator __first, _InputIterator __last) {
    _M_assign_dispatch(__first, __last);
  }

  template <class _Integer>
  typename ft::enable_if<ft::is_integral<_Integer>::value, void>::type
  _M_assign_dispatch(_Integer __n, _Integer __val) {
    _M_fill_assign((size_type)__n, (T)__val);
  }

  template <class _InputIter>
  typename ft::enable_if<!ft::is_integral<_InputIter>::value, void>::type
  _M_assign_dispatch(_InputIter __first, _InputIter __last) {
    typedef
        typename iterator_traits<_InputIter>::iterator_category _IterCategory;
    _M_assign_aux(__first, __last, _IterCategory());
  }

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

  void push_back(const T& __x) {
    if (finish != end_of_storage) {
      constructObject_(finish, __x);
      ++finish;
    } else
      _M_insert_aux(end(), __x);
  }

  void push_back() {
    if (finish != end_of_storage) {
      constructObject_(finish);
      ++finish;
    } else
      _M_insert_aux(end());
  }

  void swap(vector<T, Allocator>& __x) {
    std::swap(start, __x.start);
    std::swap(finish, __x.finish);
    std::swap(end_of_storage, __x.end_of_storage);
  }

  iterator insert(iterator __position, const T& __x) {
    size_type __n = __position - begin();
    if (finish != end_of_storage && __position == end()) {
      constructObject_(finish, __x);
      ++finish;
    } else
      _M_insert_aux(iterator(__position), __x);
    return begin() + __n;
  }

  iterator insert(iterator __position) {
    size_type __n = __position - begin();
    if (finish != end_of_storage && __position == end()) {
      constructObject_(finish);
      ++finish;
    } else
      _M_insert_aux(iterator(__position));
    return begin() + __n;
  }

  template <class _InputIterator>
  void insert(iterator __pos, _InputIterator __first, _InputIterator __last) {
    _M_insert_dispatch(__pos, __first, __last);
  }

  template <class _Integer>
  typename ft::enable_if<ft::is_integral<_Integer>::value, void>::type
  _M_insert_dispatch(iterator __pos, _Integer __n, _Integer __val) {
    _M_fill_insert(__pos, static_cast<size_type>(__n), static_cast<T>(__val));
  }

  template <class _InputIterator>
  typename ft::enable_if<!ft::is_integral<_InputIterator>::value, void>::type
  _M_insert_dispatch(iterator __pos,
                     _InputIterator __first,
                     _InputIterator __last) {
    typedef typename iterator_traits<_InputIterator>::iterator_category
        _IterCategory;
    _M_range_insert(__pos, __first, __last, _IterCategory());
  }

  void insert(iterator __pos, size_type __n, const T& __x) {
    _M_fill_insert(__pos, __n, __x);
  }

  void pop_back() {
    --finish;
    destructObject_(finish);
  }

  iterator erase(iterator __position) {
    if (__position + 1 != end())
      std::copy(__position + 1, end(), __position);
    --finish;
    destructObject_(finish);
    return __position;
  }

  iterator erase(iterator __first, iterator __last) {
    iterator __i(std::copy(__last, end(), __first));
    destructObject_(__i, end());
    finish = finish - (__last - __first);
    return __first;
  }

  void resize(size_type __new_size, const T& __x) {
    if (__new_size < size())
      erase(begin() + __new_size, end());
    else
      insert(end(), __new_size - size(), __x);
  }

  void resize(size_type __new_size) {
    resize(__new_size, T());
  }

  void clear() {
    erase(begin(), end());
  }

 protected:
  template <class _ForwardIterator>
  pointer _M_allocate_and_copy(size_type __n,
                               _ForwardIterator __first,
                               _ForwardIterator __last) {
    pointer __result = Base_::allocate_(__n);
    try {
      std::uninitialized_copy(__first, __last, __result);
      return __result;
    } catch (...) {
		Base_::deallocate_(__result, __n);
      throw;
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
    size_type __n = ft::distance(__first, __last);
    start = Base_::allocate_(__n);
    end_of_storage = start + __n;
    finish = std::uninitialized_copy(__first, __last, start);
  }
};

// vector relational operator {{{

template <class T, class Allocator>
inline bool operator==(const vector<T, Allocator>& __x,
                       const vector<T, Allocator>& __y) {
  return __x.size() == __y.size()
         && ft::equal(__x.begin(), __x.end(), __y.begin());
}

template <class T, class Allocator>
inline bool operator<(const vector<T, Allocator>& __x,
                      const vector<T, Allocator>& __y) {
  return ft::lexicographical_compare(
      __x.begin(), __x.end(), __y.begin(), __y.end());
}

template <class T, class Allocator>
inline bool operator!=(const vector<T, Allocator>& __x,
                       const vector<T, Allocator>& __y) {
  return !(__x == __y);
}

template <class T, class Allocator>
inline bool operator>(const vector<T, Allocator>& __x,
                      const vector<T, Allocator>& __y) {
  return __y < __x;
}

template <class T, class Allocator>
inline bool operator<=(const vector<T, Allocator>& __x,
                       const vector<T, Allocator>& __y) {
  return !(__y < __x);
}

template <class T, class Allocator>
inline bool operator>=(const vector<T, Allocator>& __x,
                       const vector<T, Allocator>& __y) {
  return !(__x < __y);
}

// vector relational operator }}}

template <class T, class Allocator>
void swap(vector<T, Allocator>& __x, vector<T, Allocator>& __y) {
  __x.swap(__y);
}

}  // namespace ft

#endif  // FT_CONTAINERS_VECTOR_HPP
