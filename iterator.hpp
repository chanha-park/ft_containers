/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 14:47:02 by chanhpar          #+#    #+#             */
/*   Updated: 2023/01/14 17:13:12 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_ITERATOR_HPP
#define FT_CONTAINERS_ITERATOR_HPP

#include <iterator>
#include "type_traits.hpp"

namespace ft {

// iterator tags {{{

// struct input_iterator_tag {};

// struct output_iterator_tag {};

// struct forward_iterator_tag : public input_iterator_tag {};

// struct bidirectional_iterator_tag : public forward_iterator_tag {};

// struct random_access_iterator_tag : public bidirectional_iterator_tag {};

typedef std::input_iterator_tag input_iterator_tag;

typedef std::output_iterator_tag output_iterator_tag;

typedef std::forward_iterator_tag forward_iterator_tag;

typedef std::bidirectional_iterator_tag bidirectional_iterator_tag;

typedef std::random_access_iterator_tag random_access_iterator_tag;

// iterator tags }}}

namespace detail {

// has_iterator_typedef__ {{{

template <typename T>
struct has_iterator_typedef__ {
 private:
  struct two__ {
    char dummy__[2];
  };

  template <typename>
  struct void_t__ {
    typedef void type;
  };

  template <typename U>
  static two__
  test__(...);

  template <typename U>
  static char
  test__(typename void_t__<typename U::iterator_category>::type* = 0,
         typename void_t__<typename U::difference_type>::type* = 0,
         typename void_t__<typename U::value_type>::type* = 0,
         typename void_t__<typename U::reference>::type* = 0,
         typename void_t__<typename U::pointer>::type* = 0);

 public:
  static const bool value = sizeof(test__<T>(0, 0, 0, 0, 0)) == 1;
};

// has_iterator_typedef__ }}}

}  // namespace detail

// is_iterator_tag {{{

template <typename T>
struct is_iterator_tag : ft::false_type {};

template <>
struct is_iterator_tag<ft::input_iterator_tag> : ft::true_type {};

template <>
struct is_iterator_tag<ft::output_iterator_tag> : ft::true_type {};

template <>
struct is_iterator_tag<ft::forward_iterator_tag> : ft::true_type {};

template <>
struct is_iterator_tag<ft::bidirectional_iterator_tag> : ft::true_type {};

template <>
struct is_iterator_tag<ft::random_access_iterator_tag> : ft::true_type {};

// is_iterator_tag }}}

namespace detail {

// iterator_traits__ {{{

template <typename Iterator, bool>
struct iterator_traits_internal {};

template <typename Iterator>
struct iterator_traits_internal<Iterator, true> {
  typedef typename Iterator::difference_type difference_type;
  typedef typename Iterator::value_type value_type;
  typedef typename Iterator::pointer pointer;
  typedef typename Iterator::reference reference;
  typedef typename Iterator::iterator_category iterator_category;
};

template <typename Iterator, bool>
struct iterator_traits__ {};

template <typename Iterator>
struct iterator_traits__<Iterator, true> :
    ft::detail::iterator_traits_internal<
        Iterator,
        ft::is_iterator_tag<typename Iterator::iterator_category>::value> {};

// iterator_traits__ }}}

}  // namespace detail

template <typename Iterator>
struct iterator_traits :
    ft::detail::iterator_traits__<
        Iterator,
        ft::detail::has_iterator_typedef__<Iterator>::value> {};

template <typename T>
struct iterator_traits<T*> {
  typedef std::ptrdiff_t difference_type;
  typedef T value_type;
  typedef T* pointer;
  typedef T& reference;
  typedef ft::random_access_iterator_tag iterator_category;
};

template <typename T>
struct iterator_traits<const T*> {
  typedef std::ptrdiff_t difference_type;
  typedef T value_type;
  typedef const T* pointer;
  typedef const T& reference;
  typedef ft::random_access_iterator_tag iterator_category;
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

// advance {{{

template <typename InputIter, typename Distance>
void
advance__(InputIter& i, Distance n, input_iterator_tag) {
  for (; n > 0; --n)
    ++i;
}

template <typename BidirectionalIter, typename Distance>
void
advance__(BidirectionalIter& i, Distance n, bidirectional_iterator_tag) {
  if (n >= 0)
    for (; n > 0; --n)
      ++i;
  else
    for (; n < 0; ++n)
      --i;
}

template <typename RandomIter, typename Distance>
void
advance__(RandomIter& i, Distance n, random_access_iterator_tag) {
  i += n;
}

template <typename InputIter, typename Distance>
void
advance(InputIter& i, Distance n) {
  advance__(i, n, typename iterator_traits<InputIter>::iterator_category());
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
typename iterator_traits<InputIter>::difference_type
distance(InputIter first, InputIter last) {
  return (distance__(
      first, last, typename iterator_traits<InputIter>::iterator_category()));
}

// }}}

// reverse_iterator {{{1

// reverse_iterator: class {{{2

template <typename Iterator>
class reverse_iterator :
    public ft::iterator<
        typename ft::iterator_traits<Iterator>::iterator_category,
        typename ft::iterator_traits<Iterator>::value_type,
        typename ft::iterator_traits<Iterator>::difference_type,
        typename ft::iterator_traits<Iterator>::pointer,
        typename ft::iterator_traits<Iterator>::reference> {
 protected:
  Iterator current;

 public:
  typedef Iterator iterator_type;
  typedef
      typename ft::iterator_traits<Iterator>::difference_type difference_type;
  typedef typename ft::iterator_traits<Iterator>::reference reference;
  typedef typename ft::iterator_traits<Iterator>::pointer pointer;

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
  reverse_iterator&
  operator=(const reverse_iterator<U>& u) {
    current = u.base();
    return (*this);
  }

  iterator_type
  base(void) const {
    return (current);
  }

  reference
  operator*(void) const {
    iterator_type tmp__ = current;
    return (*--tmp__);
  }

  pointer
  operator->(void) const {
    return (&(operator*()));
  }

  reverse_iterator&
  operator++(void) {
    --current;
    return (*this);
  }

  reverse_iterator
  operator++(int) {
    reverse_iterator tmp__(*this);
    --current;
    return (tmp__);
  }

  reverse_iterator&
  operator--(void) {
    ++current;
    return (*this);
  }

  reverse_iterator
  operator--(int) {
    reverse_iterator tmp__(*this);
    ++current;
    return (tmp__);
  }

  reverse_iterator
  operator+(difference_type n) const {
    return (reverse_iterator(current - n));
  }

  reverse_iterator&
  operator+=(difference_type n) {
    current -= n;
    return (*this);
  }

  reverse_iterator
  operator-(difference_type n) const {
    return (reverse_iterator(current + n));
  }

  reverse_iterator&
  operator-=(difference_type n) {
    current += n;
    return (*this);
  }

  reference
  operator[](difference_type n) const {
    return (*(*this + n));
  }
};

// reverse_iterator: class }}}

// reverse_iterator: relational operators {{{2

template <typename Iter1, typename Iter2>
bool
operator==(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y) {
  return (x.base() == y.base());
}

template <typename Iter1, typename Iter2>
bool
operator!=(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y) {
  return (!(x == y));
}

template <typename Iter1, typename Iter2>
bool
operator<(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y) {
  return (y.base() < x.base());
}

template <typename Iter1, typename Iter2>
bool
operator<=(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y) {
  return (!(y < x));
}

template <typename Iter1, typename Iter2>
bool
operator>(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y) {
  return (y < x);
}

template <typename Iter1, typename Iter2>
bool
operator>=(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y) {
  return (!(x < y));
}

// reverse_iterator: relational operators }}}

// reverse_iterator: addition, subtraction operators {{{

template <typename Iter1, typename Iter2>
typename reverse_iterator<Iter1>::difference_type
operator-(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y) {
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

// template <typename T1, typename T2>
// void
// constructObject_(T1* p, const T2& value) {
//   new (static_cast<void*>(p)) T1(value);
// }

// template <typename T>
// void
// constructObject_(T* p) {
//   new (static_cast<void*>(p)) T();
// }

// template <typename T>
// void
// destructObject_(T* p) {
//   p->~T();
// }

// template <typename ForwardIter>
// typename ft::enable_if<!ft::has_trivial_destructor<typename
// ft::iterator_traits<
//                            ForwardIter>::value_type>::value,
//                        void>::type
// destruct_(ForwardIter first, ForwardIter last) {
//   for (; first != last; ++first)
//     ft::destructObject_(&*first);
// }

// template <typename ForwardIter>
// typename ft::enable_if<ft::has_trivial_destructor<typename
// ft::iterator_traits<
//                            ForwardIter>::value_type>::value,
//                        void>::type
// destruct_(ForwardIter, ForwardIter) {
// }

// template <typename ForwardIter>
// void
// destructObject_(ForwardIter first, ForwardIter last) {
//   ft::destruct_<ForwardIter>(first, last);
// }

}  // namespace ft

#endif  // FT_CONTAINERS_ITERATOR_HPP
