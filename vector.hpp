/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 12:20:14 by chanhpar          #+#    #+#             */
/*   Updated: 2022/12/15 21:29:35 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

#include <algorithm>
#include <limits>
#include "algorithm.hpp"
#include "iterator.hpp"
#include "memory.hpp"
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

  const Iterator&
  base(void) const {
    return (current);
  }

  reference
  operator*(void) const {
    return (*current);
  }

  reference
  operator*(void) {
    return (*current);
  }

  pointer
  operator->(void) const {
    return (current);
  }

  vector_iterator&
  operator++(void) {
    ++current;
    return (*this);
  }

  vector_iterator
  operator++(int) {
    vector_iterator tmp__(*this);
    ++current;
    return (tmp__);
  }

  vector_iterator&
  operator--(void) {
    --current;
    return (*this);
  }

  vector_iterator
  operator--(int) {
    vector_iterator tmp__(*this);
    --current;
    return (tmp__);
  }

  vector_iterator
  operator+(const difference_type& n) const {
    return (vector_iterator(current + n));
  }

  vector_iterator
  operator-(const difference_type& n) const {
    return (vector_iterator(current - n));
  }

  vector_iterator&
  operator+=(const difference_type& n) {
    current += n;
    return (*this);
  }

  vector_iterator&
  operator-=(const difference_type& n) {
    current -= n;
    return (*this);
  }

  reference
  operator[](const difference_type& n) const {
    return (current[n]);
  }
};

// vector_iterator class }}}

template <typename Iter1, typename Iter2, typename Container>
bool
operator==(const vector_iterator<Iter1, Container>& x,
           const vector_iterator<Iter2, Container>& y) {
  return (x.base() == y.base());
}

template <typename Iter1, typename Iter2, typename Container>
bool
operator!=(const vector_iterator<Iter1, Container>& x,
           const vector_iterator<Iter2, Container>& y) {
  return (!(x == y));
}

template <typename Iter1, typename Iter2, typename Container>
bool
operator<(const vector_iterator<Iter1, Container>& x,
          const vector_iterator<Iter2, Container>& y) {
  return (x.base() < y.base());
}

template <typename Iter1, typename Iter2, typename Container>
bool
operator>(const vector_iterator<Iter1, Container>& x,
          const vector_iterator<Iter2, Container>& y) {
  return (y < x);
}

template <typename Iter1, typename Iter2, typename Container>
bool
operator<=(const vector_iterator<Iter1, Container>& x,
           const vector_iterator<Iter2, Container>& y) {
  return (!(y < x));
}

template <typename Iter1, typename Iter2, typename Container>
bool
operator>=(const vector_iterator<Iter1, Container>& x,
           const vector_iterator<Iter2, Container>& y) {
  return (!(x < y));
}

template <typename Iter1, typename Iter2, typename Container>
typename vector_iterator<Iter1, Container>::difference_type
operator-(const vector_iterator<Iter1, Container>& x,
          const vector_iterator<Iter2, Container>& y) {
  return (x.base() - y.base());
}

template <typename Iterator, typename Container>
vector_iterator<Iterator, Container>
operator+(typename vector_iterator<Iterator, Container>::difference_type n,
          const vector_iterator<Iterator, Container>& x) {
  return (vector_iterator<Iterator, Container>(x.base() + n));
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

  vector_base_(size_t n, const allocator_type& x) try :
      data_allocator(x),
      start(data_allocator.allocate(n)),
      finish(start),
      end_of_storage(start + n) {
  } catch (...) {
    throw(std::length_error("ft::vector"));
  }

  T*
  allocate_(size_t n) {
    return (data_allocator.allocate(n));
  }

  void
  deallocate_(T* p, size_t n) {
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
  typedef vector<T, Allocator> vector_type_;

 public:
  // member types {{{

  typedef T value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;

  typedef vector_iterator<pointer, vector_type_> iterator;
  typedef vector_iterator<const_pointer, vector_type_> const_iterator;

  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

  typedef typename Base_::allocator_type allocator_type;

  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;

  // member types }}}

 private:
  // private auxiliary functions

  size_type
  recommend__(size_type newSize__) const {
    static const size_type ms__ = this->max_size();

    if (newSize__ > ms__)
      throw(std::length_error("ft::vector"));
    const size_type cap__ = this->capacity();
    if (cap__ >= (ms__ >> 1))
      return (ms__);
    return (std::max<size_type>(cap__ << 1, newSize__));
  }

  // auxiliary constructor. n > last - first {{{

  template <typename InputIter>
  vector(size_type n,
         InputIter first,
         InputIter last,
         const allocator_type& alloc) :
      Base_(n, alloc) {
    this->finish = ft::addressof(*ft::uninitialized_copy(
        first, last, this->start, this->data_allocator));
  }

  // auxiliary constructor. n > last - first }}}

  // insert_range__ {{{

  template <typename InputIter>
  iterator
  insert_range__(iterator pos,
                 InputIter first,
                 InputIter last,
                 ft::input_iterator_tag) {
    const difference_type offset__ = pos - this->begin();
    for (; first != last; ++first) {
      pos = insert(pos, *first);
      ++pos;
    }
    return (iterator(this->start + offset__));
  }

  template <typename ForwardIter>
  iterator
  insert_range__(iterator pos,
                 ForwardIter first,
                 ForwardIter last,
                 ft::forward_iterator_tag) {
    const size_type insertSize__ = ft::distance(first, last);
    if (insertSize__ == 0)
      return (pos);
    const size_type offset__ = pos - this->begin();
    if (size_type(this->end_of_storage - this->finish) >= insertSize__
        && pos == this->end()) {
      this->finish = ft::addressof(*ft::uninitialized_copy(
          first, last, this->end(), this->data_allocator));
    } else {
      const size_type oldSize__ = this->size();
      vector_type_ tmp__(this->recommend__(oldSize__ + insertSize__),
                         this->begin(),
                         pos,
                         this->get_allocator());
      tmp__.finish = ft::addressof(*ft::uninitialized_copy(
          first, last, tmp__.end(), tmp__.data_allocator));
      tmp__.finish = ft::addressof(*ft::uninitialized_copy(
          pos, this->end(), tmp__.end(), tmp__.data_allocator));
      this->swap(tmp__);
    }
    return (iterator(this->start + offset__));
  }

  // insert_range__ }}}

  // assign_range__ {{{

  template <typename InputIter>
  void
  assign_range__(InputIter first, InputIter last, ft::input_iterator_tag) {
    iterator cur__(this->begin());

    for (; first != last && cur__ != this->end(); ++cur__, (void)++first)
      *cur__ = *first;
    if (first == last)
      this->erase(cur__, this->end());
    else
      this->insert(this->end(), first, last);
  }

  template <typename ForwardIter>
  void
  assign_range__(ForwardIter first,
                 ForwardIter last,
                 ft::forward_iterator_tag) {
    const size_type oldSize__ = this->size();
    const size_type newSize__ = ft::distance(first, last);

    if (newSize__ > this->capacity()) {
      vector_type_ tmp__(
          this->recommend__(newSize__), first, last, this->get_allocator());
      this->swap(tmp__);
      return;
    }
    if (oldSize__ >= newSize__) {
      iterator it__(std::copy(first, last, this->begin()));
      ft::destroy(it__, this->end(), this->data_allocator);
    } else {
      ForwardIter mid__(first);
      ft::advance(mid__, oldSize__);
      std::copy(first, mid__, this->begin());
      ft::uninitialized_copy(mid__, last, this->end(), this->data_allocator);
    }
    this->finish = this->start + newSize__;
  }

  template <typename RandIter>
  void
  assign_range__(RandIter first,
                 RandIter last,
                 ft::random_access_iterator_tag) {
    const size_type oldSize__ = this->size();
    const size_type newSize__ = ft::distance(first, last);

    if (newSize__ > this->capacity()) {
      vector_type_ tmp__(
          this->recommend__(newSize__), first, last, this->get_allocator());
      this->swap(tmp__);
      return;
    }
    if (this->size() >= newSize__) {
      iterator it__(std::copy(first, last, this->begin()));
      ft::destroy(it__, this->end(), this->data_allocator);
    } else {
      std::copy(first, first + oldSize__, this->begin());
      ft::uninitialized_copy(
          first + oldSize__, last, this->end(), this->data_allocator);
    }
    this->finish = this->start + newSize__;
  }

  // assign_range__ }}}

 public:
  // constructor {{{

  explicit vector(const allocator_type& alloc = allocator_type()) :
      Base_(alloc) {
  }

  explicit vector(size_type n,
                  const value_type& val = value_type(),
                  const allocator_type& alloc = allocator_type()) :
      Base_(n, alloc) {
    this->finish = ft::addressof(
        *ft::uninitialized_fill_n(this->start, n, val, this->data_allocator));
  }

  // copy constructor
  vector(const vector<T, Allocator>& other) :
      Base_(other.size(), other.get_allocator()) {
    this->finish = ft::addressof(*ft::uninitialized_copy(
        other.begin(), other.end(), this->start, this->data_allocator));
  }

  template <typename InputIter>
  vector(typename ft::enable_if<is_integral<InputIter>::value, InputIter>::type
             first,
         InputIter last,
         const allocator_type& alloc = allocator_type()) :
      Base_(static_cast<size_type>(first), alloc) {
    const size_type n = static_cast<size_type>(first);
    const value_type val = static_cast<value_type>(last);

    this->finish = ft::addressof(
        *ft::uninitialized_fill_n(this->start, n, val, this->data_allocator));
  }

  template <typename InputIter>
  vector(
      typename ft::enable_if<
          !is_integral<InputIter>::value
              && is_same<typename iterator_traits<InputIter>::iterator_category,
                         ft::input_iterator_tag>::value,
          InputIter>::type first,
      InputIter last,
      const allocator_type& alloc = allocator_type()) :
      Base_(alloc) {
    for (; first != last; ++first)
      push_back(*first);
  }

  template <typename InputIter>
  vector(
      typename ft::enable_if<!is_integral<InputIter>::value
                                 && !is_same<typename iterator_traits<
                                                 InputIter>::iterator_category,
                                             ft::input_iterator_tag>::value,
                             InputIter>::type first,
      InputIter last,
      const allocator_type& alloc = allocator_type()) :
      Base_(ft::distance(first, last), alloc) {
    this->finish = ft::addressof(*ft::uninitialized_copy(
        first, last, this->start, this->data_allocator));
  }

  // constructor }}}

  // destructor {{{

  virtual ~vector(void) {
    ft::destroy(this->start, this->finish, this->data_allocator);
  }

  // destructor }}}

  // operator= overload {{{

  vector<T, Allocator>&
  operator=(const vector<T, Allocator>& other) {
    if (&other != this) {
      const size_type oldSize__ = this->size();
      const size_type newSize__ = other.size();
      if (this->capacity() < newSize__) {
        vector_type_ tmp__(other);
        this->swap(tmp__);
        return (*this);
      }
      if (oldSize__ >= newSize__) {
        iterator it__(std::copy(other.begin(), other.end(), this->begin()));
        ft::destroy(it__, this->end(), this->data_allocator);
      } else {
        std::copy(other.begin(), other.begin() + oldSize__, this->begin());
        ft::uninitialized_copy(other.begin() + oldSize__,
                               other.end(),
                               this->end(),
                               this->data_allocator);
      }
      this->finish = this->start + newSize__;
    }
    return (*this);
  }

  // operator= overload }}}

  // iterators {{{

  iterator
  begin(void) {
    return (iterator(this->start));
  }

  const_iterator
  begin(void) const {
    return (const_iterator(this->start));
  }

  iterator
  end(void) {
    return (iterator(this->finish));
  }

  const_iterator
  end(void) const {
    return (const_iterator(this->finish));
  }

  reverse_iterator
  rbegin(void) {
    return (reverse_iterator(end()));
  }

  const_reverse_iterator
  rbegin(void) const {
    return (const_reverse_iterator(end()));
  }

  reverse_iterator
  rend(void) {
    return (reverse_iterator(begin()));
  }

  const_reverse_iterator
  rend(void) const {
    return (const_reverse_iterator(begin()));
  }

  // iterators }}}

  // size, max_size, capacity, empty, reserve, resize {{{

  size_type
  size(void) const {
    return (size_type(end() - begin()));
  }

  size_type
  max_size(void) const {
    static const size_type maxSize__
        = std::min<size_type>(this->data_allocator.max_size(),
                              std::numeric_limits<difference_type>::max());
    return (maxSize__);
  }

  size_type
  capacity(void) const {
    return (size_type(const_iterator(this->end_of_storage) - begin()));
  }

  bool
  empty(void) const {
    return (begin() == end());
  }

  void
  reserve(size_type n) {
    if (n > this->max_size())
      throw(std::length_error("ft::vector"));

    if (this->capacity() < n) {
      vector_type_ tmp__(n, this->begin(), this->end(), this->get_allocator());
      this->swap(tmp__);
    }
  }

  void
  resize(size_type n, const value_type& val = value_type()) {
    if (n < this->size())
      this->erase(this->begin() + n, this->end());
    else
      this->insert(this->end(), n - this->size(), val);
  }

  // size, max_size, capacity, empty, reserve, resize }}}

  // element access {{{

  reference
  operator[](size_type n) {
    return (*(begin() + n));
  }

  const_reference
  operator[](size_type n) const {
    return (*(begin() + n));
  }

  reference
  at(size_type n) {
    if (n >= this->size())
      throw(std::out_of_range("ft::vector"));
    return (this->start[n]);
  }

  const_reference
  at(size_type n) const {
    if (n >= this->size())
      throw(std::out_of_range("ft::vector"));
    return (this->start[n]);
  }

  reference
  front(void) {
    return (*begin());
  }

  const_reference
  front(void) const {
    return (*begin());
  }

  reference
  back(void) {
    return (*(end() - 1));
  }

  const_reference
  back(void) const {
    return (*(end() - 1));
  }

  // element access }}}

  // assign {{{

  // XXX
  void
  assign(size_type n, const value_type& val) {
    if (n > this->capacity()) {
      vector_type_ tmp__(n, val, this->get_allocator());
      this->swap(tmp__);
    } else if (n > this->size()) {
      std::fill(this->begin(), this->end(), val);
      this->finish = ft::addressof(*ft::uninitialized_fill_n(
          this->end(), n - this->size(), val, this->data_allocator));
    } else {
      std::fill_n(this->begin(), n, val);
      this->erase(this->begin() + n, this->end());
    }
  }

  template <typename InputIter>
  typename ft::enable_if<!ft::is_integral<InputIter>::value, void>::type
  assign(InputIter first, InputIter last) {
    this->assign_range__(
        first, last, typename iterator_traits<InputIter>::iterator_category());
  }

  template <typename InputIter>
  typename ft::enable_if<ft::is_integral<InputIter>::value, void>::type
  assign(InputIter first, InputIter last) {
    this->assign(static_cast<size_type>(first), static_cast<value_type>(last));
  }

  // assign }}}

  // insert {{{

  iterator
  insert(iterator pos, const value_type& val) {
    return (this->insert(pos, 1, val));
  }

  template <typename InputIter>
  typename ft::enable_if<!ft::is_integral<InputIter>::value, iterator>::type
  insert(iterator pos, InputIter first, InputIter last) {
    return (this->insert_range__(
        pos,
        first,
        last,
        typename iterator_traits<InputIter>::iterator_category()));
  }

  template <typename InputIter>
  typename ft::enable_if<ft::is_integral<InputIter>::value, iterator>::type
  insert(iterator pos, InputIter first, InputIter last) {
    return (this->insert(
        pos, static_cast<size_type>(first), static_cast<value_type>(last)));
  }

  iterator
  insert(iterator pos, size_type n, const value_type& val) {
    if (n == 0)
      return (pos);
    const size_type offset__ = pos - this->begin();
    if (size_type(this->end_of_storage - this->finish) >= n) {
      // enough space. no need to realloc
      iterator oldEnd__(this->finish);
      if (pos == oldEnd__) {
        this->finish = ft::addressof(
            *ft::uninitialized_fill_n(oldEnd__, n, val, this->data_allocator));
      } else if (n <= size_type(oldEnd__ - pos)) {
        // enough space, but need to shift elements back. pos + n <= end
        iterator mid__(oldEnd__ - n);
        this->finish = ft::addressof(*ft::uninitialized_copy(
            mid__, oldEnd__, oldEnd__, this->data_allocator));
        std::copy_backward(pos, mid__, oldEnd__);
        std::fill(pos, pos + n, val);
      } else {
        // enough space, but need to shift elements back. pos + n > end
        this->finish = ft::addressof(
            *ft::uninitialized_fill_n(oldEnd__,
                                      n - size_type(oldEnd__ - pos),
                                      val,
                                      this->data_allocator));
        this->finish = ft::addressof(*ft::uninitialized_copy(
            pos, oldEnd__, pos + n, this->data_allocator));
        std::fill(pos, oldEnd__, val);
      }
    } else {
      // need realloc
      vector_type_ tmp__(this->recommend__(this->size() + n),
                         this->begin(),
                         pos,
                         this->get_allocator());
      tmp__.finish = ft::addressof(*ft::uninitialized_fill_n(
          tmp__.finish, n, val, tmp__.data_allocator));
      tmp__.finish = ft::addressof(*ft::uninitialized_copy(
          pos, this->end(), tmp__.end(), tmp__.data_allocator));
      this->swap(tmp__);
    }
    return (iterator(this->start + offset__));
  }

  // insert }}}

  // erase, clear, swap, push_back, pop_back {{{

  iterator
  erase(iterator pos) {
    if (pos + 1 != this->end())
      std::copy(pos + 1, this->end(), pos);
    --this->finish;
    ft::destroy_at(this->finish, this->data_allocator);
    return (pos);
  }

  iterator
  erase(iterator first, iterator last) {
    ft::destroy(
        std::copy(last, this->end(), first), this->end(), this->data_allocator);
    this->finish -= (last - first);
    return (first);
  }

  void
  swap(vector<T, Allocator>& other) {
    std::swap(this->start, other.start);
    std::swap(this->finish, other.finish);
    std::swap(this->end_of_storage, other.end_of_storage);
  }

  void
  clear(void) {
    this->erase(this->begin(), this->end());
  }

  void
  push_back(const value_type& val) {
    this->insert(this->end(), 1, val);
  }

  void
  pop_back(void) {
    --this->finish;
    ft::destroy_at(this->finish, this->data_allocator);
  }

  // erase, clear, swap, push_back, pop_back }}}

  allocator_type
  get_allocator(void) const {
    return (this->data_allocator);
  }
};

// vector class end

// vector relational operator {{{

template <typename T, typename Allocator>
bool
operator==(const vector<T, Allocator>& x, const vector<T, Allocator>& y) {
  return (x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin()));
}

template <typename T, typename Allocator>
bool
operator<(const vector<T, Allocator>& x, const vector<T, Allocator>& y) {
  return (ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()));
}

template <typename T, typename Allocator>
bool
operator!=(const vector<T, Allocator>& x, const vector<T, Allocator>& y) {
  return (!(x == y));
}

template <typename T, typename Allocator>
bool
operator>(const vector<T, Allocator>& x, const vector<T, Allocator>& y) {
  return (y < x);
}

template <typename T, typename Allocator>
bool
operator<=(const vector<T, Allocator>& x, const vector<T, Allocator>& y) {
  return (!(y < x));
}

template <typename T, typename Allocator>
bool
operator>=(const vector<T, Allocator>& x, const vector<T, Allocator>& y) {
  return (!(x < y));
}

// vector relational operator }}}

template <typename T, typename Allocator>
void
swap(vector<T, Allocator>& x, vector<T, Allocator>& y) {
  x.swap(y);
}

}  // namespace ft

#endif  // FT_CONTAINERS_VECTOR_HPP
