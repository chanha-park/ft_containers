/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 12:20:14 by chanhpar          #+#    #+#             */
/*   Updated: 2022/11/03 17:26:47 by chanhpar         ###   ########.fr       */
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

  const Iterator& base(void) const {
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
    return (vector_iterator(current - n));
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

// template <typename T, typename Allocator>
// class vector_alloc_base_ {
//  public:
//   typedef typename Allocator::template rebind<T>::other allocator_type;

//  protected:
//   allocator_type data_allocator;
//   T* start;
//   T* finish;
//   T* end_of_storage;

//   T* allocate_(size_t n) {
//     return (data_allocator.allocate(n));
//   }

//   void deallocate_(T* p, size_t n) {
//     if (p)
//       data_allocator.deallocate(p, n);
//   }

//  protected:
//   vector_alloc_base_(const allocator_type& x) :
//       data_allocator(x), start(0), finish(0), end_of_storage(0) {
//   }

//  public:
//   virtual ~vector_alloc_base_(void) {
//   }

//   allocator_type get_allocator(void) const {
//     return (data_allocator);
//   }
// };

// vector_alloc_base_ }}}

// vector_base_ {{{

template <typename T, typename Allocator>
class vector_base_ {
 public:
  typedef typename Allocator::template rebind<T>::other allocator_type;
  // typedef vector_alloc_base_<T, Allocator> Base_;
  // typedef typename Base_::allocator_type allocator_type;

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

  vector_base_(const allocator_type& x) :
      data_allocator(x), start(0), finish(0), end_of_storage(0) {
  }

  vector_base_(size_t n, const allocator_type& x) : data_allocator(x) {
    start = allocate_(n);
    finish = start;
    end_of_storage = start + n;
  }

 public:
  virtual ~vector_base_(void) {
    deallocate_(start, end_of_storage - start);
  }

  // allocator_type get_allocator(void) const {
  //   return (data_allocator);
  // }
};

// vector_base_ }}}

template <typename T, typename Allocator = std::allocator<T> >
class vector : protected vector_base_<T, Allocator> {
 private:
  typedef vector_base_<T, Allocator> Base_;
  typedef vector<T, Allocator> vector_type;

 public:
  // typedefs {{{
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

  // typedefs }}}

 private:
  // _M_insert_aux {{{

  void _M_insert_aux(iterator __position, const T& __x) {
    if (this->finish != this->end_of_storage) {
      constructObject_(this->finish, *(this->finish - 1));
      ++this->finish;
      T __x_copy = __x;
      std::copy_backward(
          __position, iterator(this->finish - 2), iterator(this->finish - 1));
      *__position = __x_copy;
    } else {
      const size_type __old_size = size();
      const size_type __len = __old_size != 0 ? 2 * __old_size : 1;
      iterator __new_start(this->allocate_(__len));
      iterator __new_finish(__new_start);
      try {
        __new_finish = std::uninitialized_copy(
            iterator(this->start), __position, __new_start);
        constructObject_(__new_finish.base(), __x);
        ++__new_finish;
        __new_finish = std::uninitialized_copy(
            __position, iterator(this->finish), __new_finish);
      } catch (...) {
        destructObject_(__new_start, __new_finish);
        this->deallocate_(__new_start.base(), __len);
        throw;
      }
      destructObject_(begin(), end());
      this->deallocate_(this->start, this->end_of_storage - this->start);
      this->start = __new_start.base();
      this->finish = __new_finish.base();
      this->end_of_storage = __new_start.base() + __len;
    }
  }

  void _M_insert_aux(iterator __position) {
    if (this->finish != this->end_of_storage) {
      constructObject_(this->finish, *(this->finish - 1));
      ++this->finish;
      std::copy_backward(
          __position, iterator(this->finish - 2), iterator(this->finish - 1));
      *__position = T();
    } else {
      const size_type __old_size = size();
      const size_type __len = __old_size != 0 ? 2 * __old_size : 1;
      pointer __new_start = this->allocate_(__len);
      pointer __new_finish = __new_start;
      try {
        __new_finish = std::uninitialized_copy(
            iterator(this->start), __position, __new_start);
        constructObject_(__new_finish);
        ++__new_finish;
        __new_finish = std::uninitialized_copy(
            __position, iterator(this->finish), __new_finish);
      } catch (...) {
        destructObject_(__new_start, __new_finish);
        deallocate_(__new_start, __len);
        throw;
      }
      destructObject_(begin(), end());
      deallocate_(this->start, this->end_of_storage - this->start);
      this->start = __new_start;
      this->finish = __new_finish;
      this->end_of_storage = __new_start + __len;
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
      this->finish
          = std::uninitialized_fill_n(this->finish, __n - size(), __val);
    } else
      erase(std::fill_n(begin(), __n, __val), end());
  }

  // _M_fill_assign }}}

  // _M_fill_insert {{{

  void _M_fill_insert(iterator __pos, size_type __n, const T& __x) {
    if (__n != 0) {
      if (size_type(this->end_of_storage - this->finish) >= __n) {
        T __x_copy = __x;
        const size_type __elems_after = end() - __pos;
        iterator __old_finish(this->finish);
        if (__elems_after > __n) {
          std::uninitialized_copy(
              this->finish - __n, this->finish, this->finish);
          this->finish += __n;
          std::copy_backward(__pos, __old_finish - __n, __old_finish);
          std::fill(__pos, __pos + __n, __x_copy);
        } else {
          std::uninitialized_fill_n(
              this->finish, __n - __elems_after, __x_copy);
          this->finish += __n - __elems_after;
          std::uninitialized_copy(__pos, __old_finish, this->finish);
          this->finish += __elems_after;
          std::fill(__pos, __old_finish, __x_copy);
        }
      } else {
        const size_type __old_size = size();
        const size_type __len = __old_size + std::max(__old_size, __n);
        iterator __new_start(this->allocate_(__len));
        iterator __new_finish(__new_start);
        try {
          __new_finish = std::uninitialized_copy(begin(), __pos, __new_start);
          __new_finish = std::uninitialized_fill_n(__new_finish, __n, __x);
          __new_finish = std::uninitialized_copy(__pos, end(), __new_finish);
        } catch (...) {
          destructObject_(__new_start, __new_finish);
          deallocate_(__new_start.base(), __len);
          throw;
        }
        destructObject_(this->start, this->finish);
        deallocate_(this->start, this->end_of_storage - this->start);
        this->start = __new_start.base();
        this->finish = __new_finish.base();
        this->end_of_storage = __new_start.base() + __len;
      }
    }
  }

  // _M_fill_insert }}}

  // _M_assign_aux {{{
  template <typename _InputIterator>
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

  template <typename _ForwardIter>
  void _M_assign_aux(_ForwardIter __first,
                     _ForwardIter __last,
                     forward_iterator_tag) {
    size_type __len = ft::distance(__first, __last);

    if (__len > capacity()) {
      pointer __tmp(_M_allocate_and_copy(__len, __first, __last));
      destructObject_(this->start, this->finish);
      deallocate_(this->start, this->end_of_storage - this->start);
      this->start = __tmp;
      this->end_of_storage = this->finish = this->start + __len;
    } else if (size() >= __len) {
      iterator __new_finish(std::copy(__first, __last, this->start));
      destructObject_(__new_finish, end());
      this->finish = __new_finish.base();
    } else {
      _ForwardIter __mid = __first;
      ft::advance(__mid, size());
      std::copy(__first, __mid, this->start);
      this->finish = std::uninitialized_copy(__mid, __last, this->finish);
    }
  }

  // _M_assign_aux }}}

  // _M_range_insert {{{

  template <typename _InputIterator>
  void _M_range_insert(iterator __pos,
                       _InputIterator __first,
                       _InputIterator __last,
                       input_iterator_tag) {
    for (; __first != __last; ++__first) {
      __pos = insert(__pos, *__first);
      ++__pos;
    }
  }

  template <typename _ForwardIterator>
  void _M_range_insert(iterator __pos,
                       _ForwardIterator __first,
                       _ForwardIterator __last,
                       forward_iterator_tag) {
    if (__first != __last) {
      size_type __n = ft::distance(__first, __last);
      if (size_type(this->end_of_storage - this->finish) >= __n) {
        const size_type __elems_after = end() - __pos;
        iterator __old_finish(this->finish);
        if (__elems_after > __n) {
          std::uninitialized_copy(
              this->finish - __n, this->finish, this->finish);
          this->finish += __n;
          std::copy_backward(__pos, __old_finish - __n, __old_finish);
          std::copy(__first, __last, __pos);
        } else {
          _ForwardIterator __mid = __first;
          ft::advance(__mid, __elems_after);
          std::uninitialized_copy(__mid, __last, this->finish);
          this->finish += __n - __elems_after;
          std::uninitialized_copy(__pos, __old_finish, this->finish);
          this->finish += __elems_after;
          std::copy(__first, __mid, __pos);
        }
      } else {
        const size_type __old_size = size();
        const size_type __len = __old_size + std::max(__old_size, __n);
        iterator __new_start(this->allocate_(__len));
        iterator __new_finish(__new_start);
        try {
          __new_finish = std::uninitialized_copy(
              iterator(this->start), __pos, __new_start);
          __new_finish = std::uninitialized_copy(__first, __last, __new_finish);
          __new_finish = std::uninitialized_copy(
              __pos, iterator(this->finish), __new_finish);
        } catch (...) {
          destructObject_(__new_start, __new_finish);
          deallocate_(__new_start.base(), __len);
          throw;
        }
        destructObject_(this->start, this->finish);
        deallocate_(this->start, this->end_of_storage - this->start);
        this->start = __new_start.base();
        this->finish = __new_finish.base();
        this->end_of_storage = __new_start.base() + __len;
      }
    }
  }

  // _M_range_insert }}}

  // _M_range_check {{{

  void _M_range_check(size_type n) const {
    if (n >= this->size())
      throw std::out_of_range("vector");
    // std::__throw_out_of_range("vector");
  }

  // _M_range_check }}}

  // _M_initialize_aux {{{

  template <typename _Integer>
  typename ft::enable_if<ft::is_integral<_Integer>::value, void>::type
  _M_initialize_aux(_Integer n, _Integer __value) {
    this->start = this->allocate_(n);
    this->end_of_storage = this->start + n;
    this->finish = std::uninitialized_fill_n(this->start, n, __value);
  }

  template <typename _InputIterator>
  typename ft::enable_if<!ft::is_integral<_InputIterator>::value, void>::type
  _M_initialize_aux(_InputIterator __first, _InputIterator __last) {
    typedef typename iterator_traits<_InputIterator>::iterator_category
        _IterCategory;
    _M_range_initialize(__first, __last, _IterCategory());
  }

  // _M_initialize_aux }}}

  // _M_assign_dispatch {{{

  template <typename _Integer>
  typename ft::enable_if<ft::is_integral<_Integer>::value, void>::type
  _M_assign_dispatch(_Integer n, _Integer __val) {
    _M_fill_assign((size_type)n, (T)__val);
  }

  template <typename _InputIter>
  typename ft::enable_if<!ft::is_integral<_InputIter>::value, void>::type
  _M_assign_dispatch(_InputIter __first, _InputIter __last) {
    typedef
        typename iterator_traits<_InputIter>::iterator_category _IterCategory;
    _M_assign_aux(__first, __last, _IterCategory());
  }

  // _M_assign_dispatch }}}

  // _M_allocate_and_copy {{{

  template <typename _ForwardIterator>
  pointer _M_allocate_and_copy(size_type n,
                               _ForwardIterator __first,
                               _ForwardIterator __last) {
    pointer __result = this->allocate_(n);
    try {
      std::uninitialized_copy(__first, __last, __result);
      return __result;
    } catch (...) {
      deallocate_(__result, n);
      throw;
    }
  }

  // _M_allocate_and_copy }}}

  // _M_range_initialize {{{

  template <typename _InputIterator>
  void _M_range_initialize(_InputIterator __first,
                           _InputIterator __last,
                           input_iterator_tag) {
    for (; __first != __last; ++__first)
      push_back(*__first);
  }

  // This function is only called by the constructor.
  template <typename _ForwardIterator>
  void _M_range_initialize(_ForwardIterator __first,
                           _ForwardIterator __last,
                           forward_iterator_tag) {
    size_type n = ft::distance(__first, __last);
    this->start = this->allocate_(n);
    this->end_of_storage = this->start + n;
    this->finish = std::uninitialized_copy(__first, __last, this->start);
  }

  // _M_range_initialize }}}

 public:
  allocator_type get_allocator(void) const {
    return (this->data_allocator);
  }

  iterator begin(void) {
    return (iterator(this->start));
  }

  const_iterator begin(void) const {
    return (const_iterator(this->start));
  }

  iterator end(void) {
    return (iterator(this->finish));
  }

  const_iterator end(void) const {
    return (const_iterator(this->finish));
  }

  reverse_iterator rbegin(void) {
    return (reverse_iterator(end()));
  }

  const_reverse_iterator rbegin(void) const {
    return (const_reverse_iterator(end()));
  }

  reverse_iterator rend(void) {
    return (reverse_iterator(begin()));
  }

  const_reverse_iterator rend(void) const {
    return (const_reverse_iterator(begin()));
  }

  size_type size(void) const {
    return (size_type(end() - begin()));
  }

  size_type max_size(void) const {
    return ((size_type(-1) / sizeof(T)) >> (sizeof(T) == 1));
  }

  size_type capacity(void) const {
    return (size_type(const_iterator(this->end_of_storage) - begin()));
  }

  bool empty(void) const {
    return (begin() == end());
  }

  reference operator[](size_type n) {
    return (*(begin() + n));
  }

  const_reference operator[](size_type n) const {
    return (*(begin() + n));
  }

  reference at(size_type n) {
    _M_range_check(n);
    return ((*this)[n]);
  }

  const_reference at(size_type n) const {
    _M_range_check(n);
    return ((*this)[n]);
  }

  explicit vector(const allocator_type& __a = allocator_type()) : Base_(__a) {
  }

  vector(size_type n,
         const T& __value,
         const allocator_type& __a = allocator_type()) :
      Base_(n, __a) {
    this->finish = std::uninitialized_fill_n(this->start, n, __value);
  }

  explicit vector(size_type n) : Base_(n, allocator_type()) {
    this->finish = std::uninitialized_fill_n(this->start, n, T());
  }

  vector(const vector<T, Allocator>& __x) :
      Base_(__x.size(), __x.get_allocator()) {
    this->finish = std::uninitialized_copy(__x.begin(), __x.end(), this->start);
  }

  template <typename _InputIterator>
  vector(_InputIterator __first,
         _InputIterator __last,
         const allocator_type& __a = allocator_type()) :
      Base_(__a) {
    _M_initialize_aux(__first, __last);
  }

  virtual ~vector(void) {
    destructObject_(this->start, this->finish);
  }

  vector<T, Allocator>& operator=(const vector<T, Allocator>& __x) {
    if (&__x != this) {
      const size_type __xlen = __x.size();
      if (__xlen > capacity()) {
        pointer __tmp = _M_allocate_and_copy(__xlen, __x.begin(), __x.end());
        destructObject_(this->start, this->finish);
        deallocate_(this->start, this->end_of_storage - this->start);
        this->start = __tmp;
        this->end_of_storage = this->start + __xlen;
      } else if (size() >= __xlen) {
        iterator __i(std::copy(__x.begin(), __x.end(), begin()));
        destructObject_(__i, end());
      } else {
        std::copy(__x.begin(), __x.begin() + size(), this->start);
        std::uninitialized_copy(__x.begin() + size(), __x.end(), this->finish);
      }
      this->finish = this->start + __xlen;
    }
    return (*this);
  }

  void reserve(size_type n) {
    if (capacity() < n) {
      const size_type __old_size = size();
      pointer __tmp = _M_allocate_and_copy(n, this->start, this->finish);
      destructObject_(this->start, this->finish);
      deallocate_(this->start, this->end_of_storage - this->start);
      this->start = __tmp;
      this->finish = __tmp + __old_size;
      this->end_of_storage = this->start + n;
    }
  }

  void assign(size_type n, const T& __val) {
    _M_fill_assign(n, __val);
  }

  template <typename _InputIterator>
  void assign(_InputIterator __first, _InputIterator __last) {
    _M_assign_dispatch(__first, __last);
  }

  reference front(void) {
    return (*begin());
  }

  const_reference front(void) const {
    return (*begin());
  }

  reference back(void) {
    return (*(end() - 1));
  }

  const_reference back(void) const {
    return (*(end() - 1));
  }

  void push_back(const T& __x) {
    if (this->finish != this->end_of_storage) {
      constructObject_(this->finish, __x);
      ++this->finish;
    } else
      _M_insert_aux(end(), __x);
  }

  void push_back(void) {
    if (this->finish != this->end_of_storage) {
      constructObject_(this->finish);
      ++this->finish;
    } else
      _M_insert_aux(end());
  }

  void swap(vector<T, Allocator>& __x) {
    std::swap(this->start, __x.start);
    std::swap(this->finish, __x.finish);
    std::swap(this->end_of_storage, __x.end_of_storage);
  }

  iterator insert(iterator __position, const T& __x) {
    size_type n = __position - begin();
    if (this->finish != this->end_of_storage && __position == end()) {
      constructObject_(this->finish, __x);
      ++this->finish;
    } else
      _M_insert_aux(iterator(__position), __x);
    return (begin() + n);
  }

  iterator insert(iterator __position) {
    size_type n = __position - begin();
    if (this->finish != this->end_of_storage && __position == end()) {
      constructObject_(this->finish);
      ++this->finish;
    } else
      _M_insert_aux(iterator(__position));
    return (begin() + n);
  }

  template <typename _InputIterator>
  void insert(iterator __pos, _InputIterator __first, _InputIterator __last) {
    _M_insert_dispatch(__pos, __first, __last);
  }

  template <typename _Integer>
  typename ft::enable_if<ft::is_integral<_Integer>::value, void>::type
  _M_insert_dispatch(iterator __pos, _Integer n, _Integer __val) {
    _M_fill_insert(__pos, static_cast<size_type>(n), static_cast<T>(__val));
  }

  template <typename _InputIterator>
  typename ft::enable_if<!ft::is_integral<_InputIterator>::value, void>::type
  _M_insert_dispatch(iterator __pos,
                     _InputIterator __first,
                     _InputIterator __last) {
    typedef typename iterator_traits<_InputIterator>::iterator_category
        _IterCategory;
    _M_range_insert(__pos, __first, __last, _IterCategory());
  }

  void insert(iterator __pos, size_type n, const T& __x) {
    _M_fill_insert(__pos, n, __x);
  }

  void pop_back(void) {
    --this->finish;
    destructObject_(this->finish);
  }

  iterator erase(iterator __position) {
    if (__position + 1 != end())
      std::copy(__position + 1, end(), __position);
    --this->finish;
    destructObject_(this->finish);
    return (__position);
  }

  iterator erase(iterator __first, iterator __last) {
    iterator __i(std::copy(__last, end(), __first));
    destructObject_(__i, end());
    this->finish = this->finish - (__last - __first);
    return (__first);
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

  void clear(void) {
    erase(begin(), end());
  }
};

// vector relational operator {{{

template <typename T, typename Allocator>
inline bool operator==(const vector<T, Allocator>& __x,
                       const vector<T, Allocator>& __y) {
  return __x.size() == __y.size()
         && ft::equal(__x.begin(), __x.end(), __y.begin());
}

template <typename T, typename Allocator>
inline bool operator<(const vector<T, Allocator>& __x,
                      const vector<T, Allocator>& __y) {
  return ft::lexicographical_compare(
      __x.begin(), __x.end(), __y.begin(), __y.end());
}

template <typename T, typename Allocator>
inline bool operator!=(const vector<T, Allocator>& __x,
                       const vector<T, Allocator>& __y) {
  return !(__x == __y);
}

template <typename T, typename Allocator>
inline bool operator>(const vector<T, Allocator>& __x,
                      const vector<T, Allocator>& __y) {
  return __y < __x;
}

template <typename T, typename Allocator>
inline bool operator<=(const vector<T, Allocator>& __x,
                       const vector<T, Allocator>& __y) {
  return !(__y < __x);
}

template <typename T, typename Allocator>
inline bool operator>=(const vector<T, Allocator>& __x,
                       const vector<T, Allocator>& __y) {
  return !(__x < __y);
}

// vector relational operator }}}

template <typename T, typename Allocator>
void swap(vector<T, Allocator>& __x, vector<T, Allocator>& __y) {
  __x.swap(__y);
}

}  // namespace ft

#endif  // FT_CONTAINERS_VECTOR_HPP
