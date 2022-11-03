/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 12:20:14 by chanhpar          #+#    #+#             */
/*   Updated: 2022/11/04 00:37:11 by chanhpar         ###   ########.fr       */
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

// vector_base_ class {{{

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

 protected:
  virtual ~vector_base_(void) {
    deallocate_(start, end_of_storage - start);
  }

  // allocator_type get_allocator(void) const {
  //   return (data_allocator);
  // }
};

// vector_base_ class }}}

// vector class start
template <typename T, typename Allocator = std::allocator<T> >
class vector : protected vector_base_<T, Allocator> {
 private:
  typedef vector_base_<T, Allocator> Base_;
  typedef vector<T, Allocator> vector_type;

 public:
  // member types {{{
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

  // member types }}}

 private:
  // private auxiliary functions {{{
  // _M_insert_aux {{{

  void _M_insert_aux(iterator pos, const value_type& val) {
    if (this->finish != this->end_of_storage) {
      constructObject_(this->finish, *(this->finish - 1));
      ++this->finish;
      T __x_copy = val;
      std::copy_backward(
          pos, iterator(this->finish - 2), iterator(this->finish - 1));
      *pos = __x_copy;
    } else {
      const size_type orig_size__ = size();
      const size_type __len = orig_size__ != 0 ? 2 * orig_size__ : 1;
      iterator __new_start(this->allocate_(__len));
      iterator __new_finish(__new_start);
      try {
        __new_finish
            = std::uninitialized_copy(iterator(this->start), pos, __new_start);
        constructObject_(__new_finish.base(), val);
        ++__new_finish;
        __new_finish = std::uninitialized_copy(
            pos, iterator(this->finish), __new_finish);
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

  void _M_insert_aux(iterator pos) {
    if (this->finish != this->end_of_storage) {
      constructObject_(this->finish, *(this->finish - 1));
      ++this->finish;
      std::copy_backward(
          pos, iterator(this->finish - 2), iterator(this->finish - 1));
      *pos = T();
    } else {
      const size_type orig_size__ = size();
      const size_type __len = orig_size__ != 0 ? 2 * orig_size__ : 1;
      pointer __new_start = this->allocate_(__len);
      pointer __new_finish = __new_start;
      try {
        __new_finish
            = std::uninitialized_copy(iterator(this->start), pos, __new_start);
        constructObject_(__new_finish);
        ++__new_finish;
        __new_finish = std::uninitialized_copy(
            pos, iterator(this->finish), __new_finish);
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

  void _M_fill_assign(size_type n, const value_type& val) {
    if (n > capacity()) {
      vector<T, Allocator> tmp__(n, val, get_allocator());
      tmp__.swap(*this);
    } else if (n > size()) {
      std::fill(begin(), end(), val);
      this->finish = std::uninitialized_fill_n(this->finish, n - size(), val);
    } else
      erase(std::fill_n(begin(), n, val), end());
  }

  // _M_fill_assign }}}

  // _M_fill_insert {{{

  void _M_fill_insert(iterator pos, size_type n, const value_type& val) {
    if (n != 0) {
      if (size_type(this->end_of_storage - this->finish) >= n) {
        T __x_copy = val;
        const size_type __elems_after = end() - pos;
        iterator __old_finish(this->finish);
        if (__elems_after > n) {
          std::uninitialized_copy(this->finish - n, this->finish, this->finish);
          this->finish += n;
          std::copy_backward(pos, __old_finish - n, __old_finish);
          std::fill(pos, pos + n, __x_copy);
        } else {
          std::uninitialized_fill_n(this->finish, n - __elems_after, __x_copy);
          this->finish += n - __elems_after;
          std::uninitialized_copy(pos, __old_finish, this->finish);
          this->finish += __elems_after;
          std::fill(pos, __old_finish, __x_copy);
        }
      } else {
        const size_type orig_size__ = size();
        const size_type __len = orig_size__ + std::max(orig_size__, n);
        iterator __new_start(this->allocate_(__len));
        iterator __new_finish(__new_start);
        try {
          __new_finish = std::uninitialized_copy(begin(), pos, __new_start);
          __new_finish = std::uninitialized_fill_n(__new_finish, n, val);
          __new_finish = std::uninitialized_copy(pos, end(), __new_finish);
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
  template <typename InputIter>
  void _M_assign_aux(InputIter first, InputIter last, input_iterator_tag) {
    iterator __cur(begin());
    for (; first != last && __cur != end(); ++__cur, ++first)
      *__cur = *first;
    if (first == last)
      erase(__cur, end());
    else
      insert(end(), first, last);
  }

  template <typename _ForwardIter>
  void _M_assign_aux(_ForwardIter first,
                     _ForwardIter last,
                     forward_iterator_tag) {
    size_type __len = ft::distance(first, last);

    if (__len > capacity()) {
      pointer tmp__(_M_allocate_and_copy(__len, first, last));
      destructObject_(this->start, this->finish);
      deallocate_(this->start, this->end_of_storage - this->start);
      this->start = tmp__;
      this->end_of_storage = this->finish = this->start + __len;
    } else if (size() >= __len) {
      iterator __new_finish(std::copy(first, last, this->start));
      destructObject_(__new_finish, end());
      this->finish = __new_finish.base();
    } else {
      _ForwardIter __mid = first;
      ft::advance(__mid, size());
      std::copy(first, __mid, this->start);
      this->finish = std::uninitialized_copy(__mid, last, this->finish);
    }
  }

  // _M_assign_aux }}}

  // _M_range_insert {{{

  template <typename InputIter>
  void _M_range_insert(iterator pos,
                       InputIter first,
                       InputIter last,
                       input_iterator_tag) {
    for (; first != last; ++first) {
      pos = insert(pos, *first);
      ++pos;
    }
  }

  template <typename _ForwardIterator>
  void _M_range_insert(iterator pos,
                       _ForwardIterator first,
                       _ForwardIterator last,
                       forward_iterator_tag) {
    if (first != last) {
      size_type __n = ft::distance(first, last);
      if (size_type(this->end_of_storage - this->finish) >= __n) {
        const size_type __elems_after = end() - pos;
        iterator __old_finish(this->finish);
        if (__elems_after > __n) {
          std::uninitialized_copy(
              this->finish - __n, this->finish, this->finish);
          this->finish += __n;
          std::copy_backward(pos, __old_finish - __n, __old_finish);
          std::copy(first, last, pos);
        } else {
          _ForwardIterator __mid = first;
          ft::advance(__mid, __elems_after);
          std::uninitialized_copy(__mid, last, this->finish);
          this->finish += __n - __elems_after;
          std::uninitialized_copy(pos, __old_finish, this->finish);
          this->finish += __elems_after;
          std::copy(first, __mid, pos);
        }
      } else {
        const size_type orig_size__ = size();
        const size_type __len = orig_size__ + std::max(orig_size__, __n);
        iterator __new_start(this->allocate_(__len));
        iterator __new_finish(__new_start);
        try {
          __new_finish = std::uninitialized_copy(
              iterator(this->start), pos, __new_start);
          __new_finish = std::uninitialized_copy(first, last, __new_finish);
          __new_finish = std::uninitialized_copy(
              pos, iterator(this->finish), __new_finish);
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
  _M_initialize_aux(_Integer n, _Integer val) {
    this->start = this->allocate_(n);
    this->end_of_storage = this->start + n;
    this->finish = std::uninitialized_fill_n(this->start, n, val);
  }

  template <typename InputIter>
  typename ft::enable_if<!ft::is_integral<InputIter>::value, void>::type
  _M_initialize_aux(InputIter first, InputIter last) {
    typedef
        typename iterator_traits<InputIter>::iterator_category _IterCategory;
    _M_range_initialize(first, last, _IterCategory());
  }

  // _M_initialize_aux }}}

  // _M_assign_dispatch {{{

  template <typename _Integer>
  typename ft::enable_if<ft::is_integral<_Integer>::value, void>::type
  _M_assign_dispatch(_Integer n, _Integer val) {
    _M_fill_assign((size_type)n, (T)val);  // type casting????
  }

  template <typename _InputIter>
  typename ft::enable_if<!ft::is_integral<_InputIter>::value, void>::type
  _M_assign_dispatch(_InputIter first, _InputIter last) {
    typedef
        typename iterator_traits<_InputIter>::iterator_category _IterCategory;
    _M_assign_aux(first, last, _IterCategory());
  }

  // _M_assign_dispatch }}}

  // _M_allocate_and_copy {{{

  template <typename _ForwardIterator>
  pointer _M_allocate_and_copy(size_type n,
                               _ForwardIterator first,
                               _ForwardIterator last) {
    pointer __result = this->allocate_(n);
    try {
      std::uninitialized_copy(first, last, __result);
      return __result;
    } catch (...) {
      deallocate_(__result, n);
      throw;
    }
  }

  // _M_allocate_and_copy }}}

  // _M_range_initialize {{{

  template <typename InputIter>
  void _M_range_initialize(InputIter first,
                           InputIter last,
                           input_iterator_tag) {
    for (; first != last; ++first)
      push_back(*first);
  }

  // This function is only called by the constructor.
  template <typename _ForwardIterator>
  void _M_range_initialize(_ForwardIterator first,
                           _ForwardIterator last,
                           forward_iterator_tag) {
    size_type n = ft::distance(first, last);
    this->start = this->allocate_(n);
    this->end_of_storage = this->start + n;
    this->finish = std::uninitialized_copy(first, last, this->start);
  }

  // _M_range_initialize }}}

  // _M_insert_dispatch {{{

  template <typename _Integer>
  typename ft::enable_if<ft::is_integral<_Integer>::value, void>::type
  _M_insert_dispatch(iterator pos, _Integer n, _Integer val) {
    _M_fill_insert(pos, static_cast<size_type>(n), static_cast<T>(val));
  }

  template <typename InputIter>
  typename ft::enable_if<!ft::is_integral<InputIter>::value, void>::type
  _M_insert_dispatch(iterator pos, InputIter first, InputIter last) {
    typedef
        typename iterator_traits<InputIter>::iterator_category _IterCategory;
    _M_range_insert(pos, first, last, _IterCategory());
  }

  // _M_insert_dispatch }}}

  // private auxiliary functions }}}

 public:
  // constructor {{{

  explicit vector(const allocator_type& alloc = allocator_type()) :
      Base_(alloc) {
  }

  explicit vector(size_type n,
                  const value_type& val = value_type(),
                  const allocator_type& alloc = allocator_type()) :
      Base_(n, alloc) {
    // XXX need fix uninitialized_fill_n does not return in c++98
    this->finish = std::uninitialized_fill_n(this->start, n, val);
  }

  // is this constructor neccesary?
  explicit vector(size_type n) : Base_(n, allocator_type()) {
    // XXX need fix uninitialized_fill_n does not return in c++98
    this->finish = std::uninitialized_fill_n(this->start, n, value_type());
  }

  // copy constructor
  vector(const vector<T, Allocator>& other) :
      Base_(other.size(), other.get_allocator()) {
    // XXX need fix uninitialized_fill_n does not return in c++98
    this->finish
        = std::uninitialized_copy(other.begin(), other.end(), this->start);
  }

  template <typename InputIter>
  vector(InputIter first,
         InputIter last,
         const allocator_type& alloc = allocator_type()) :
      Base_(alloc) {
    _M_initialize_aux(first, last);
  }

  // constructor }}}

  // destructor {{{

  virtual ~vector(void) {
    destructObject_(this->start, this->finish);
  }

  // destructor }}}

  // operator= overload {{{

  vector<T, Allocator>& operator=(const vector<T, Allocator>& other) {
    if (&other != this) {
      const size_type __xlen = other.size();
      if (__xlen > capacity()) {
        pointer tmp__
            = _M_allocate_and_copy(__xlen, other.begin(), other.end());
        destructObject_(this->start, this->finish);
        deallocate_(this->start, this->end_of_storage - this->start);
        this->start = tmp__;
        this->end_of_storage = this->start + __xlen;
      } else if (size() >= __xlen) {
        iterator __i(std::copy(other.begin(), other.end(), begin()));
        destructObject_(__i, end());
      } else {
        std::copy(other.begin(), other.begin() + size(), this->start);
        std::uninitialized_copy(
            other.begin() + size(), other.end(), this->finish);
      }
      this->finish = this->start + __xlen;
    }
    return (*this);
  }

  // operator= overload }}}

  // iterators {{{

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

  // iterators }}}

  // capacity {{{

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

  void reserve(size_type n) {
    if (capacity() < n) {
      const size_type orig_size__ = size();
      pointer tmp__ = _M_allocate_and_copy(n, this->start, this->finish);
      destructObject_(this->start, this->finish);
      deallocate_(this->start, this->end_of_storage - this->start);
      this->start = tmp__;
      this->finish = tmp__ + orig_size__;
      this->end_of_storage = this->start + n;
    }
  }

  void resize(size_type n, const value_type& val = value_type()) {
    if (n < size())
      erase(begin() + n, end());
    else
      insert(end(), n - size(), val);
  }

  // void resize(size_type n) {
  //   resize(n, T());
  // }

  // capacity }}}

  // element access {{{

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

  // element access }}}

  // modifiers {{{

  void assign(size_type n, const value_type& val) {
    _M_fill_assign(n, val);
  }

  template <typename InputIter>
  void assign(InputIter first, InputIter last) {
    _M_assign_dispatch(first, last);
  }

  void push_back(const value_type& val) {
    if (this->finish != this->end_of_storage) {
      constructObject_(this->finish, val);
      ++this->finish;
    } else
      _M_insert_aux(end(), val);
  }

  void push_back(void) {
    if (this->finish != this->end_of_storage) {
      constructObject_(this->finish);
      ++this->finish;
    } else
      _M_insert_aux(end());
  }

  void pop_back(void) {
    --this->finish;
    destructObject_(this->finish);
  }

  iterator insert(iterator pos, const value_type& val) {
    size_type n = pos - begin();
    if (this->finish != this->end_of_storage && pos == end()) {
      constructObject_(this->finish, val);
      ++this->finish;
    } else
      _M_insert_aux(iterator(pos), val);
    return (begin() + n);
  }

  iterator insert(iterator pos) {
    size_type n = pos - begin();
    if (this->finish != this->end_of_storage && pos == end()) {
      constructObject_(this->finish);
      ++this->finish;
    } else
      _M_insert_aux(iterator(pos));
    return (begin() + n);
  }

  template <typename InputIter>
  void insert(iterator pos, InputIter first, InputIter last) {
    _M_insert_dispatch(pos, first, last);
  }

  void insert(iterator pos, size_type n, const value_type& val) {
    _M_fill_insert(pos, n, val);
  }

  iterator erase(iterator pos) {
    if (pos + 1 != end())
      std::copy(pos + 1, end(), pos);
    --this->finish;
    destructObject_(this->finish);
    return (pos);
  }

  iterator erase(iterator first, iterator last) {
    iterator __i(std::copy(last, end(), first));
    destructObject_(__i, end());
    this->finish = this->finish - (last - first);
    return (first);
  }

  void swap(vector<T, Allocator>& val) {
    std::swap(this->start, val.start);
    std::swap(this->finish, val.finish);
    std::swap(this->end_of_storage, val.end_of_storage);
  }

  void clear(void) {
    erase(begin(), end());
  }

  // modifiers }}}

  allocator_type get_allocator(void) const {
    return (this->data_allocator);
  }
};

// vector class end

// vector relational operator {{{

template <typename T, typename Allocator>
bool operator==(const vector<T, Allocator>& x, const vector<T, Allocator>& y) {
  return (x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin()));
}

template <typename T, typename Allocator>
bool operator<(const vector<T, Allocator>& x, const vector<T, Allocator>& y) {
  return (ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()));
}

template <typename T, typename Allocator>
bool operator!=(const vector<T, Allocator>& x, const vector<T, Allocator>& y) {
  return (!(x == y));
}

template <typename T, typename Allocator>
bool operator>(const vector<T, Allocator>& x, const vector<T, Allocator>& y) {
  return (y < x);
}

template <typename T, typename Allocator>
bool operator<=(const vector<T, Allocator>& x, const vector<T, Allocator>& y) {
  return (!(y < x));
}

template <typename T, typename Allocator>
bool operator>=(const vector<T, Allocator>& x, const vector<T, Allocator>& y) {
  return (!(x < y));
}

// vector relational operator }}}

template <typename T, typename Allocator>
void swap(vector<T, Allocator>& x, vector<T, Allocator>& y) {
  x.swap(y);
}

}  // namespace ft

#endif  // FT_CONTAINERS_VECTOR_HPP
