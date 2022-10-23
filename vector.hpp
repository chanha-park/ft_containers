/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 12:20:14 by chanhpar          #+#    #+#             */
/*   Updated: 2022/10/23 19:43:03 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

#include <memory>
#include "iterator.hpp"
#include "type_traits.hpp"

namespace ft {

// vector_iterator {{{1

// vector_iterator class {{{2

template <typename Iterator, typename Container>
class vector_iterator
    : public ft::iterator<
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

  vector_iterator(void) : current(Iterator()) {}

  explicit vector_iterator(const Iterator& it) : current(it) {}

  template <typename U>
  vector_iterator(const vector_iterator<U, Container>& u) : current(u.base()) {}

  const Iterator& base() const { return (current); }

  reference operator*(void) const { return (*current); }

  pointer operator->(void) const { return (current); }

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

  difference_type operator-(const vector_iterator& x) const {
    return (current - x.base());
  }

  vector_iterator& operator+=(const difference_type& n) {
    current += n;
    return (*this);
  }

  vector_iterator& operator-=(const difference_type& n) {
    current -= n;
    return (*this);
  }

  reference operator[](const difference_type& n) const { return (current[n]); }
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

  T* allocate_(size_t n) { return (data_allocator.allocate(n)); }

  void deallocate_(T* p, size_t n) {
    if (p)
      data_allocator.deallocate(p, n);
  }

 public:
  allocator_type get_allocator(void) const { return (data_allocator); }

  vector_alloc_base_(const allocator_type& x)
      : data_allocator(x), start(0), finish(0), end_of_storage(0) {}
};

// template <typename T, typename Allocator>
// class vector_alloc_base_<T, Allocator, true> {
//  public:
//   typedef typename Allocator::template rebind<T>::other allocator_type;

//  protected:
//   T* start;
//   T* finish;
//   T* end_of_storage;

//   T* allocate_(size_t __n) {
//     return Allocator::allocate(__n);
//   }

//   void deallocate_(T* __p, size_t __n) {
//     Allocator::deallocate(__p, __n);
//   }

//  public:
//   allocator_type get_allocator(void) const {
//     return (allocator_type());
//   }

//   vector_alloc_base_(const allocator_type&) :
//       start(0), finish(0), end_of_storage(0) {
//   }
// };

// vector_alloc_base_ }}}

// vector_base_ {{{

template <typename _Tp, typename _Alloc>
struct vector_base_ : public vector_alloc_base_<_Tp, _Alloc> {
 public:
  typedef vector_alloc_base_<_Tp, _Alloc> _Base;
  typedef typename _Base::allocator_type allocator_type;

  vector_base_(const allocator_type& __a) : _Base(__a) {}

  vector_base_(size_t __n, const allocator_type& __a) : _Base(__a) {
    _Base::start = _Base::allocate_(__n);
    _Base::finish = _Base::start;
    _Base::end_of_storage = _Base::start + __n;
  }

  ~vector_base_() {
    _Base::deallocate_(_Base::start, _Base::end_of_storage - _Base::start);
  }
};

// template <typename _Tp, typename _Alloc>
// struct vector_base_ :
//     public vector_alloc_base_<_Tp,
//                               _Alloc,
//                               _Alloc_traits<_Tp, _Alloc>::_S_instanceless> {
//   typedef vector_alloc_base_<_Tp,
//                              _Alloc,
//                              _Alloc_traits<_Tp, _Alloc>::_S_instanceless>
//       _Base;
//   typedef typename _Base::allocator_type allocator_type;

//   vector_base_(const allocator_type& __a) : _Base(__a) {
//   }

//   vector_base_(size_t __n, const allocator_type& __a) : _Base(__a) {
//     start = allocate_(__n);
//     finish = start;
//     end_of_storage = start + __n;
//   }

//   ~vector_base_() {
//     deallocate_(start, end_of_storage - start);
//   }
// };

// vector_base_ }}}

// vector class {{{

template <class _Tp, class _Alloc = std::allocator<_Tp> >
class vector : protected vector_base_<_Tp, _Alloc> {
 private:
  typedef vector_base_<_Tp, _Alloc> _Base;
  typedef vector<_Tp, _Alloc> vector_type;

 public:
  typedef _Tp value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;

  typedef vector_iterator<pointer, vector_type> iterator;
  typedef vector_iterator<const_pointer, vector_type> const_iterator;

  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

  typedef typename _Base::allocator_type allocator_type;

  allocator_type get_allocator() const { return _Base::get_allocator(); }

  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;

 protected:
  using _Base::allocate_;
  using _Base::deallocate_;
  using _Base::end_of_storage;
  using _Base::finish;
  using _Base::start;

 protected:
  void _M_insert_aux(iterator __position, const _Tp& __x);
  void _M_insert_aux(iterator __position);

 public:
  iterator begin() { return iterator(start); }

  const_iterator begin() const { return const_iterator(start); }

  iterator end() { return iterator(finish); }

  const_iterator end() const { return const_iterator(finish); }

  reverse_iterator rbegin() { return reverse_iterator(end()); }

  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }

  reverse_iterator rend() { return reverse_iterator(begin()); }

  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  }

  size_type size() const { return size_type(end() - begin()); }

  size_type max_size() const { return size_type(-1) / sizeof(_Tp); }

  size_type capacity() const {
    return size_type(const_iterator(end_of_storage) - begin());
  }

  bool empty() const { return begin() == end(); }

  reference operator[](size_type __n) { return *(begin() + __n); }

  const_reference operator[](size_type __n) const { return *(begin() + __n); }

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

  explicit vector(const allocator_type& __a = allocator_type()) : _Base(__a) {}

  vector(size_type __n,
         const _Tp& __value,
         const allocator_type& __a = allocator_type())
      : _Base(__n, __a) {
    finish = uninitialized_fill_n(start, __n, __value);
  }

  explicit vector(size_type __n) : _Base(__n, allocator_type()) {
    finish = uninitialized_fill_n(start, __n, _Tp());
  }

  vector(const vector<_Tp, _Alloc>& __x)
      : _Base(__x.size(), __x.get_allocator()) {
    finish = uninitialized_copy(__x.begin(), __x.end(), start);
  }

  // Check whether it's an integral type.  If so, it's not an iterator.
  template <class _InputIterator>
  vector(_InputIterator __first,
         _InputIterator __last,
         const allocator_type& __a = allocator_type())
      : _Base(__a) {
    typedef typename is_integral<_InputIterator>::value _Integral;
    _M_initialize_aux(__first, __last, _Integral());
  }

  template <class _Integer>
  void _M_initialize_aux(_Integer __n, _Integer __value, true_type) {
    start = allocate_(__n);
    end_of_storage = start + __n;
    finish = uninitialized_fill_n(start, __n, __value);
  }

  template <class _InputIterator>
  void _M_initialize_aux(_InputIterator __first,
                         _InputIterator __last,
                         false_type) {
    typedef typename iterator_traits<_InputIterator>::iterator_category
        _IterCategory;
    _M_range_initialize(__first, __last, _IterCategory());
  }

  ~vector() { destructObject_(start, finish); }

  vector<_Tp, _Alloc>& operator=(const vector<_Tp, _Alloc>& __x);

  void reserve(size_type __n) {
    if (capacity() < __n) {
      const size_type __old_size = size();
      pointer __tmp = _M_allocate_and_copy(__n, start, finish);
      destructObject_(start, finish);
      deallocate_(start, end_of_storage - start);
      start = __tmp;
      finish = __tmp + __old_size;
      end_of_storage = start + __n;
    }
  }

  // assign(), a generalized assignment member function.  Two
  // versions: one that takes a count, and one that takes a range.
  // The range version is a member template, so we dispatch on whether
  // or not the type is an integer.

  void assign(size_type __n, const _Tp& __val) { _M_fill_assign(__n, __val); }

  void _M_fill_assign(size_type __n, const _Tp& __val);

  template <class _InputIterator>
  void assign(_InputIterator __first, _InputIterator __last) {
    typedef typename is_integral<_InputIterator>::value _Integral;
    _M_assign_dispatch(__first, __last, _Integral());
  }

  template <class _Integer>
  void _M_assign_dispatch(_Integer __n, _Integer __val, true_type) {
    _M_fill_assign((size_type)__n, (_Tp)__val);
  }

  template <class _InputIter>
  void _M_assign_dispatch(_InputIter __first, _InputIter __last, false_type) {
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

  reference front() { return *begin(); }

  const_reference front() const { return *begin(); }

  reference back() { return *(end() - 1); }

  const_reference back() const { return *(end() - 1); }

  void push_back(const _Tp& __x) {
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

  void swap(vector<_Tp, _Alloc>& __x) {
    std::swap(start, __x.start);
    std::swap(finish, __x.finish);
    std::swap(end_of_storage, __x.end_of_storage);
  }

  iterator insert(iterator __position, const _Tp& __x) {
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

  // Check whether it's an integral type.  If so, it's not an iterator.
  template <class _InputIterator>
  void insert(iterator __pos, _InputIterator __first, _InputIterator __last) {
    typedef typename is_integral<_InputIterator>::value _Integral;
    _M_insert_dispatch(__pos, __first, __last, _Integral());
  }

  template <class _Integer>
  void _M_insert_dispatch(iterator __pos,
                          _Integer __n,
                          _Integer __val,
                          true_type) {
    _M_fill_insert(__pos, static_cast<size_type>(__n), static_cast<_Tp>(__val));
  }

  template <class _InputIterator>
  void _M_insert_dispatch(iterator __pos,
                          _InputIterator __first,
                          _InputIterator __last,
                          false_type) {
    typedef typename iterator_traits<_InputIterator>::iterator_category
        _IterCategory;
    _M_range_insert(__pos, __first, __last, _IterCategory());
  }

  void insert(iterator __pos, size_type __n, const _Tp& __x) {
    _M_fill_insert(__pos, __n, __x);
  }

  void _M_fill_insert(iterator __pos, size_type __n, const _Tp& __x);

  void pop_back() {
    --finish;
    destructObject_(finish);
  }

  iterator erase(iterator __position) {
    if (__position + 1 != end())
      copy(__position + 1, end(), __position);
    --finish;
    destructObject_(finish);
    return __position;
  }

  iterator erase(iterator __first, iterator __last) {
    iterator __i(copy(__last, end(), __first));
    destructObject_(__i, end());
    finish = finish - (__last - __first);
    return __first;
  }

  void resize(size_type __new_size, const _Tp& __x) {
    if (__new_size < size())
      erase(begin() + __new_size, end());
    else
      insert(end(), __new_size - size(), __x);
  }

  void resize(size_type __new_size) { resize(__new_size, _Tp()); }

  void clear() { erase(begin(), end()); }

 protected:
  template <class _ForwardIterator>
  pointer _M_allocate_and_copy(size_type __n,
                               _ForwardIterator __first,
                               _ForwardIterator __last) {
    pointer __result = allocate_(__n);
    try {
      uninitialized_copy(__first, __last, __result);
      return __result;
    } catch (...) {
      deallocate_(__result, __n);
      // std::__throw_exception_again;
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
    start = allocate_(__n);
    end_of_storage = start + __n;
    finish = uninitialized_copy(__first, __last, start);
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
