/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 14:47:02 by chanhpar          #+#    #+#             */
/*   Updated: 2022/10/15 20:56:11 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_ITERATOR_HPP
#define FT_CONTAINERS_ITERATOR_HPP

#include <iterator>
#include "type_traits.hpp"

// iterator synopsis

namespace ft {

template <typename Iterator>
struct iterator_traits {
  typedef typename Iterator::difference_type difference_type;
  typedef typename Iterator::value_type value_type;
  typedef typename Iterator::pointer pointer;
  typedef typename Iterator::reference reference;
  typedef typename Iterator::iterator_category iterator_category;
};

template <typename T>
struct iterator_traits<T*> {
  typedef std::ptrdiff_t difference_type;
  typedef T value_type;
  typedef T* pointer;
  typedef T& reference;
  typedef std::random_access_iterator_tag iterator_category;
};

template <typename T>
struct iterator_traits<const T*> {
  typedef std::ptrdiff_t difference_type;
  typedef T value_type;
  typedef const T* pointer;
  typedef const T& reference;
  typedef std::random_access_iterator_tag iterator_category;
};

template <typename Category,
          typename T,
          typename Distance = ptrdiff_t,
          typename Pointer = T*,
          typename Reference = T&>
struct iterator {
  typedef T value_type;
  typedef Distance difference_type;
  typedef Pointer pointer;
  typedef Reference reference;
  typedef Category iterator_category;
};

struct input_iterator_tag {};

struct output_iterator_tag {};

struct forward_iterator_tag : public input_iterator_tag {};

struct bidirectional_iterator_tag : public forward_iterator_tag {};

struct random_access_iterator_tag : public bidirectional_iterator_tag {};

// advance {{{

template <typename InputIter, typename Distance>
void advance__(InputIter& i, Distance n, input_iterator_tag) {
  for (; n > 0; --n)
    ++i;
}

template <typename BidirectionalIter, typename Distance>
void advance__(BidirectionalIter& i, Distance n, bidirectional_iterator_tag) {
  if (n >= 0)
    for (; n > 0; --n)
      ++i;
  else
    for (; n < 0; ++n)
      --i;
}

template <typename RandomIter, typename Distance>
void advance__(RandomIter& i, Distance n, random_access_iterator_tag) {
  i += n;
}

template <typename InputIter, typename Distance>
void advance(InputIter& i, Distance n) {
  advance__(i, n, typename iterator_traits<InputIter>::iterator_category(i));
}

// }}}

// distance {{{

template <typename InputIter>
typename iterator_traits<InputIter>::difference_type
distance__(InputIter first, InputIter last, input_iterator_tag) {
  typename iterator_traits<InputIter>::difference_type r(0);
  for (; first != last; ++first)
    ++r;
  return (r);
}

template <typename RandomIter>
typename iterator_traits<RandomIter>::difference_type
distance__(RandomIter first, RandomIter last, random_access_iterator_tag) {
  return (last - first);
}

template <typename InputIter>
typename iterator_traits<InputIter>::difference_type distance(InputIter first,
                                                              InputIter last) {
  return (distance__(
      first, last, typename iterator_traits<InputIter>::iterator_category()));
}

// }}}

// template <typename InputIterator>
// InputIterator next(InputIterator x,
//                    typename iterator_traits<InputIterator>::difference_type n
//                    = 1);

// template <typename BidirectionalIterator>
// BidirectionalIterator prev(
//     BidirectionalIterator x,
//     typename iterator_traits<BidirectionalIterator>::difference_type n = 1);


// reverse_iterator {{{1

// reverse_iterator: class {{{2

template <typename Iterator>
class reverse_iterator :
    public iterator<typename iterator_traits<Iterator>::iterator_category,
                    typename iterator_traits<Iterator>::value_type,
                    typename iterator_traits<Iterator>::difference_type,
                    typename iterator_traits<Iterator>::pointer,
                    typename iterator_traits<Iterator>::reference> {
 protected:
  Iterator current;

 public:
  typedef Iterator iterator_type;
  typedef typename iterator_traits<Iterator>::iterator_category iterator_category; // is this neccesary?
  typedef typename iterator_traits<Iterator>::value_type value_type; // is this neccesary?
  typedef typename iterator_traits<Iterator>::difference_type difference_type;
  typedef typename iterator_traits<Iterator>::reference reference;
  typedef typename iterator_traits<Iterator>::pointer pointer;

  reverse_iterator(void) : current() {
  }

  explicit reverse_iterator(iterator_type it) : current(it) {
  }

  reverse_iterator(const reverse_iterator& it) : current(it.current) {
  }

  template <typename U>
  reverse_iterator(const reverse_iterator<U>& u) : current(u.base()) {
  }

  template <typename U>
  reverse_iterator& operator=(const reverse_iterator<U>& u) {
	  current = u.base();
	  return (*this);
  }

  iterator_type base(void) const {
    return (current);
  }

  reference operator*(void) const {
    iterator_type tmp__ = current;
    return (*--tmp__);
  }

  pointer operator->(void) const {
    return (&(operator*()));
  }

  reverse_iterator& operator++(void) {
    --current;
    return (*this);
  }

  reverse_iterator operator++(int) {
    reverse_iterator tmp__(*this);
    --current;
    return (tmp__);
  }

  reverse_iterator& operator--(void) {
    ++current;
    return (*this);
  }

  reverse_iterator operator--(int) {
    reverse_iterator tmp__(*this);
    ++current;
    return (tmp__);
  }

  reverse_iterator operator+(difference_type n) const {
    return (reverse_iterator(current - n));
  }

  reverse_iterator& operator+=(difference_type n) {
    current -= n;
    return (*this);
  }

  reverse_iterator operator-(difference_type n) const {
    return (reverse_iterator(current + n));
  }

  reverse_iterator& operator-=(difference_type n) {
    current += n;
    return (*this);
  }

  reference operator[](difference_type n) const {
    return (*(*this + n));
  }
};

// reverse_iterator: class }}}

// reverse_iterator: relational operators {{{2

template <typename Iterator>
bool operator==(const reverse_iterator<Iterator>& x,
                const reverse_iterator<Iterator>& y) {
	return (x.base() == y.base());
}

template <typename Iterator>
bool operator!=(const reverse_iterator<Iterator>& x,
                const reverse_iterator<Iterator>& y) {
	return (!(x == y));
}

template <typename Iterator>
bool operator<(const reverse_iterator<Iterator>& x,
               const reverse_iterator<Iterator>& y) {
	return (y.base() < x.base());
}

template <typename Iterator>
bool operator<=(const reverse_iterator<Iterator>& x,
                const reverse_iterator<Iterator>& y) {
	return (!(y < x));
}

template <typename Iterator>
bool operator>(const reverse_iterator<Iterator>& x,
               const reverse_iterator<Iterator>& y) {
	return (y < x);
}

template <typename Iterator>
bool operator>=(const reverse_iterator<Iterator>& x,
                const reverse_iterator<Iterator>& y) {
	return (!(x < y));
}

// reverse_iterator: relational operators }}}

// reverse_iterator: addition, subtraction operators {{{

  template<typename Iterator>
    typename reverse_iterator<Iterator>::difference_type
    operator-(const reverse_iterator<Iterator>& x, 
	      const reverse_iterator<Iterator>& y) {
		return (y.base() - x.base());
	}


template <typename Iterator>
    reverse_iterator<Iterator> 
    operator+(typename reverse_iterator<Iterator>::difference_type n,
	      const reverse_iterator<Iterator>& x) {
		return (reverse_iterator<Iterator>(x.base() - n));
	}

// reverse_iterator: addition, subtraction operators }}}

// reverse iterator }}}

// back_insert_iterator class {{{

template <typename Container>
class back_insert_iterator : public iterator<output_iterator_tag, void, void, void, void> {
 protected:
  Container* container;

 public:
  typedef Container container_type;
  typedef void value_type; // is this neccesary?
  typedef void difference_type; // is this neccesary?
  typedef void reference; // is this neccesary?
  typedef void pointer; // is this neccesary?

  explicit back_insert_iterator(Container& x) : container(&x) {}

  back_insert_iterator& operator=(typename Container::const_reference value) {
	  container->push_back(value);
	  return (*this);
  }

  back_insert_iterator& operator*() {
	  return (*this);
  }

  back_insert_iterator& operator++() {
	  return (*this);
  }

  back_insert_iterator operator++(int) {
	  return (*this);
  }

};

// back_insert_iterator class }}}

template <typename Container>
back_insert_iterator<Container> back_inserter(Container& x) {
	return (back_insert_iterator<Container>(x));
}

// front_insert_iterator class {{{

template <typename Container>
class front_insert_iterator
    : public iterator<output_iterator_tag, void, void, void, void> {
 protected:
  Container* container;

 public:
  typedef Container container_type;
  typedef void value_type; // is this neccesary?
  typedef void difference_type; // is this neccesary?
  typedef void reference; // is this neccesary?
  typedef void pointer; // is this neccesary?

  explicit front_insert_iterator(Container& x) : container(&x) {}

  front_insert_iterator& operator=(typename Container::const_reference& value) {
	  container->push_front(value);
	  return (*this);
  }

  front_insert_iterator& operator*() {
	  return (*this);
  }
  front_insert_iterator& operator++() {
	  return (*this);
  }
  front_insert_iterator operator++(int) {
	  return (*this);
  }

};

// front_insert_iterator class }}}

template <typename Container>
front_insert_iterator<Container> front_inserter(Container& x) {
	return (front_insert_iterator<Container>(x));
}

// insert_iterator class {{{

template <typename Container>
class insert_iterator
    : public iterator<output_iterator_tag, void, void, void, void> {
 protected:
  Container* container;
  typename Container::iterator iter;

 public:
  typedef Container container_type;
  typedef void value_type; // is this neccesary?
  typedef void difference_type; // is this neccesary?
  typedef void reference; // is this neccesary?
  typedef void pointer; // is this neccesary?

  insert_iterator(Container& x, typename Container::iterator i) : container(&x), iter(&i) {}
  insert_iterator& operator=(const typename Container::const_reference value) {
	  iter = container->insert(iter, value);
	  ++iter;
	  return (*this);
  }

  insert_iterator& operator*() {
	  return (*this);
  }

  insert_iterator& operator++() {
	  return (*this);
  }

  insert_iterator& operator++(int) {
	  return (*this);
  }
};

// insert_iterator class }}}

template <typename Container, typename Iterator>
insert_iterator<Container> inserter(Container& x, Iterator i) {
      return insert_iterator<Container>(x, typename Container::iterator(i));
}

template <class T,
          class charT = char,
          class traits = char_traits<charT>,
          class Distance = ptrdiff_t>
class istream_iterator :
    public iterator<input_iterator_tag, T, Distance, const T*, const T&> {
 public:
  typedef charT char_type;
  typedef traits traits_type;
  typedef basic_istream<charT, traits> istream_type;

  constexpr istream_iterator();
  istream_iterator(istream_type& s);
  istream_iterator(const istream_iterator& x);
  ~istream_iterator();

  const T& operator*() const;
  const T* operator->() const;
  istream_iterator& operator++();
  istream_iterator operator++(int);
};

template <class T, class charT, class traits, class Distance>
bool operator==(const istream_iterator<T, charT, traits, Distance>& x,
                const istream_iterator<T, charT, traits, Distance>& y);
template <class T, class charT, class traits, class Distance>
bool operator!=(const istream_iterator<T, charT, traits, Distance>& x,
                const istream_iterator<T, charT, traits, Distance>& y);

template <class T, class charT = char, class traits = char_traits<charT>>
class ostream_iterator :
    public iterator<output_iterator_tag, void, void, void, void> {
 public:
  typedef charT char_type;
  typedef traits traits_type;
  typedef basic_ostream<charT, traits> ostream_type;

  ostream_iterator(ostream_type& s);
  ostream_iterator(ostream_type& s, const charT* delimiter);
  ostream_iterator(const ostream_iterator& x);
  ~ostream_iterator();
  ostream_iterator& operator=(const T& value);

  ostream_iterator& operator*();
  ostream_iterator& operator++();
  ostream_iterator& operator++(int);
};

template <class charT, class traits = char_traits<charT>>
class istreambuf_iterator :
    public iterator<input_iterator_tag,
                    charT,
                    typename traits::off_type,
                    unspecified,
                    charT> {
 public:
  typedef charT char_type;
  typedef traits traits_type;
  typedef typename traits::int_type int_type;
  typedef basic_streambuf<charT, traits> streambuf_type;
  typedef basic_istream<charT, traits> istream_type;

  istreambuf_iterator() noexcept;
  istreambuf_iterator(istream_type& s) noexcept;
  istreambuf_iterator(streambuf_type* s) noexcept;
  istreambuf_iterator(a - private - type) noexcept;

  charT operator*() const;
  pointer operator->() const;
  istreambuf_iterator& operator++();
  a - private - type operator++(int);

  bool equal(const istreambuf_iterator& b) const;
};

template <class charT, class traits>
bool operator==(const istreambuf_iterator<charT, traits>& a,
                const istreambuf_iterator<charT, traits>& b);
template <class charT, class traits>
bool operator!=(const istreambuf_iterator<charT, traits>& a,
                const istreambuf_iterator<charT, traits>& b);

template <class charT, class traits = char_traits<charT>>
class ostreambuf_iterator :
    public iterator<output_iterator_tag, void, void, void, void> {
 public:
  typedef charT char_type;
  typedef traits traits_type;
  typedef basic_streambuf<charT, traits> streambuf_type;
  typedef basic_ostream<charT, traits> ostream_type;

  ostreambuf_iterator(ostream_type& s) noexcept;
  ostreambuf_iterator(streambuf_type* s) noexcept;
  ostreambuf_iterator& operator=(charT c);
  ostreambuf_iterator& operator*();
  ostreambuf_iterator& operator++();
  ostreambuf_iterator& operator++(int);
  bool failed() const noexcept;
};

template <class C>
constexpr auto begin(C& c) -> decltype(c.begin());
template <class C>
constexpr auto begin(const C& c) -> decltype(c.begin());
template <class C>
constexpr auto end(C& c) -> decltype(c.end());
template <class C>
constexpr auto end(const C& c) -> decltype(c.end());
template <class T, size_t N>
constexpr T* begin(T (&array)[N]);
template <class T, size_t N>
constexpr T* end(T (&array)[N]);

}  // namespace ft

// iterator synopsis end
