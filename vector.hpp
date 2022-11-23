/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 12:20:14 by chanhpar          #+#    #+#             */
/*   Updated: 2022/11/23 17:52:34 by chanhpar         ###   ########.fr       */
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

// vector_base_ class {{{

template <typename T, typename Allocator>
class vector_base_ {
 public:
  typedef typename Allocator::template rebind<T>::other allocator_type;

 protected:
  allocator_type data_allocator;
  T* start;
  T* finish;
  T* end_of_storage;

  vector_base_(const allocator_type& x) :
      data_allocator(x), start(0), finish(0), end_of_storage(0) {
  }

  vector_base_(size_t n, const allocator_type& x) :
      data_allocator(x),
      start(data_allocator.allocate(n)),
      finish(start),
      end_of_storage(start + n) {
  }

  T* allocate_(size_t n) {
    return (data_allocator.allocate(n));
  }

  void deallocate_(T* p, size_t n) {
    if (p)
      data_allocator.deallocate(p, n);
  }

  virtual ~vector_base_(void) {
    deallocate_(start, end_of_storage - start);
  }
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
  // XXX implement auxiliary functions
  // private auxiliary functions {{{
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
    std::uninitialized_fill_n(this->start, n, val);
    this->finish = this->start + n;
  }

  // copy constructor
  vector(const vector<T, Allocator>& other) :
      Base_(other.size(), other.get_allocator()) {
    this->finish
        = std::uninitialized_copy(other.begin(), other.end(), this->start);
  }

  template <typename InputIter>
  vector(InputIter first,
         InputIter last,
         const allocator_type& alloc = allocator_type()) :
      Base_(ft::distance(first, last), alloc) {
    this->finish = std::uninitialized_copy(first, last, this->start);
  }

  // constructor }}}

  // destructor {{{

  virtual ~vector(void) {
    destructObject_(this->start, this->finish);
  }

  // destructor }}}

  // operator= overload {{{

  // XXX
  vector<T, Allocator>& operator=(const vector<T, Allocator>& other) {
    if (&other != this) {
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
    return ((size_type(-1) / sizeof(T)) >> 1);
  }

  size_type capacity(void) const {
    return (size_type(const_iterator(this->end_of_storage) - begin()));
  }

  bool empty(void) const {
    return (begin() == end());
  }

  // XXX
  void reserve(size_type n) {
  }

  // XXX
  void resize(size_type n, const value_type& val = value_type()) {
    if (n < size())
      erase(begin() + n, end());
    else
      insert(end(), n - size(), val);
  }

  // capacity }}}

  // element access {{{

  reference operator[](size_type n) {
    return (*(begin() + n));
  }

  const_reference operator[](size_type n) const {
    return (*(begin() + n));
  }

  // XXX
  reference at(size_type n) {
  }

  // XXX
  const_reference at(size_type n) const {
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

  // XXX
  void assign(size_type n, const value_type& val) {
  }

  // XXX
  template <typename InputIter>
  void assign(InputIter first, InputIter last) {
  }

  // XXX
  void push_back(const value_type& val) {
  }

  // XXX
  void push_back(void) {
  }

  // XXX
  void pop_back(void) {
    --this->finish;
    destructObject_(this->finish);
  }

  // XXX
  iterator insert(iterator pos, const value_type& val) {
  }

  // XXX
  iterator insert(iterator pos) {
  }

  // XXX
  template <typename InputIter>
  void insert(iterator pos, InputIter first, InputIter last) {
  }

  // XXX
  void insert(iterator pos, size_type n, const value_type& val) {
  }

  // XXX
  iterator erase(iterator pos) {
    if (pos + 1 != end())
      std::copy(pos + 1, end(), pos);
    --this->finish;
    destructObject_(this->finish);
    return (pos);
  }

  // XXX
  iterator erase(iterator first, iterator last) {
    iterator __i(std::copy(last, end(), first));
    destructObject_(__i, end());
    this->finish = this->finish - (last - first);
    return (first);
  }

  void swap(vector<T, Allocator>& other) {
    std::swap(get_allocator(), other.get_allocator());
    std::swap(this->start, other.start);
    std::swap(this->finish, other.finish);
    std::swap(this->end_of_storage, other.end_of_storage);
  }

  // XXX
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
