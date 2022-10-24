/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 14:47:02 by chanhpar          #+#    #+#             */
/*   Updated: 2022/10/24 19:40:39 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_ITERATOR_HPP
#define FT_CONTAINERS_ITERATOR_HPP

#include <iterator>
#include "type_traits.hpp"

namespace ft {

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
typename iterator_traits<InputIter>::difference_type distance(InputIter first,
                                                              InputIter last) {
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

  // reverse_iterator(const reverse_iterator& it) : current(it.current) {
  // }

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

template <typename Iter1, typename Iter2>
bool operator==(const reverse_iterator<Iter1>& x,
                const reverse_iterator<Iter2>& y) {
  return (x.base() == y.base());
}

template <typename Iter1, typename Iter2>
bool operator!=(const reverse_iterator<Iter1>& x,
                const reverse_iterator<Iter2>& y) {
  return (!(x == y));
}

template <typename Iter1, typename Iter2>
bool operator<(const reverse_iterator<Iter1>& x,
               const reverse_iterator<Iter2>& y) {
  return (y.base() < x.base());
}

template <typename Iter1, typename Iter2>
bool operator<=(const reverse_iterator<Iter1>& x,
                const reverse_iterator<Iter2>& y) {
  return (!(y < x));
}

template <typename Iter1, typename Iter2>
bool operator>(const reverse_iterator<Iter1>& x,
               const reverse_iterator<Iter2>& y) {
  return (y < x);
}

template <typename Iter1, typename Iter2>
bool operator>=(const reverse_iterator<Iter1>& x,
                const reverse_iterator<Iter2>& y) {
  return (!(x < y));
}

// reverse_iterator: relational operators }}}

// reverse_iterator: addition, subtraction operators {{{

template <typename Iter1, typename Iter2>
typename reverse_iterator<Iter1>::difference_type operator-(
    const reverse_iterator<Iter1>& x,
    const reverse_iterator<Iter2>& y) {
  return (y.base() - x.base());
}

template <typename Iterator>
reverse_iterator<Iterator> operator+(
    typename reverse_iterator<Iterator>::difference_type n,
    const reverse_iterator<Iterator>& x) {
  return (reverse_iterator<Iterator>(x.base() - n));
}

// reverse_iterator: addition, subtraction operators }}}

// reverse iterator }}}

// Obsolete {{{

// back_insert_iterator class {{{

// template <typename Container>
// class back_insert_iterator
//     : public iterator<output_iterator_tag, void, void, void, void> {
//  protected:
//   Container* container;

//  public:
//   typedef Container container_type;

//   explicit back_insert_iterator(Container& x) : container(&x) {}

//   back_insert_iterator& operator=(typename Container::const_reference value)
//   {
//     container->push_back(value);
//     return (*this);
//   }

//   back_insert_iterator& operator*(void) { return (*this); }

//   back_insert_iterator& operator++(void) { return (*this); }

//   back_insert_iterator operator++(int) { return (*this); }
// };

// back_insert_iterator class }}}

// template <typename Container>
// back_insert_iterator<Container> back_inserter(Container& x) {
//   return (back_insert_iterator<Container>(x));
// }

// front_insert_iterator class {{{

// template <typename Container>
// class front_insert_iterator
//     : public iterator<output_iterator_tag, void, void, void, void> {
//  protected:
//   Container* container;

//  public:
//   typedef Container container_type;

//   explicit front_insert_iterator(Container& x) : container(&x) {}

//   front_insert_iterator& operator=(typename Container::const_reference&
//   value) {
//     container->push_front(value);
//     return (*this);
//   }

//   front_insert_iterator& operator*(void) { return (*this); }

//   front_insert_iterator& operator++(void) { return (*this); }

//   front_insert_iterator operator++(int) { return (*this); }
// };

// front_insert_iterator class }}}

// template <typename Container>
// front_insert_iterator<Container> front_inserter(Container& x) {
//   return (front_insert_iterator<Container>(x));
// }

// insert_iterator class {{{

// template <typename Container>
// class insert_iterator
//     : public iterator<output_iterator_tag, void, void, void, void> {
//  protected:
//   Container* container;
//   typename Container::iterator iter;

//  public:
//   typedef Container container_type;

//   insert_iterator(Container& x, typename Container::iterator i)
//       : container(&x), iter(&i) {}

//   insert_iterator& operator=(const typename Container::const_reference value)
//   {
//     iter = container->insert(iter, value);
//     ++iter;
//     return (*this);
//   }

//   insert_iterator& operator*(void) { return (*this); }

//   insert_iterator& operator++(void) { return (*this); }

//   insert_iterator& operator++(int) { return (*this); }
// };

// insert_iterator class }}}

// template <typename Container, typename Iterator>
// insert_iterator<Container> inserter(Container& x, Iterator i) {
//   return insert_iterator<Container>(x, typename Container::iterator(i));
// }

// Obsolete }}}

template <typename T1, typename T2>
void constructObject_(T1* p, const T2& value) {
  // new (static_cast<void*>(p)) T1(value);
  new (p) T1(value);
}

template <typename T>
void constructObject_(T* p) {
  // new (static_cast<void*>(p)) T();
  new (p) T();
}

// forward declaration
template <typename T>
void destructObject_(T* p);

template <typename ForwardIter>
typename ft::enable_if<
    !ft::is_trivially_destructible<
        typename ft::iterator_traits<ForwardIter>::value_type>::value,
    void>::type
__destroy_aux(ForwardIter first, ForwardIter last) {
  for (; first != last; ++first)
    ft::destructObject_(&*first);
}

template <typename ForwardIter>
typename ft::enable_if<
    ft::is_trivially_destructible<
        typename ft::iterator_traits<ForwardIter>::value_type>::value,
    void>::type
__destroy_aux(ForwardIter, ForwardIter) {
}

template <typename T>
void destructObject_(T* p) {
  p->~T();
}

template <typename ForwardIter>
void destructObject_(ForwardIter first, ForwardIter last) {
  // typedef typename ft::iterator_traits<ForwardIter>::value_type value_type;
  // typedef typename ft::is_trivially_destructible<value_type>
  //     has_trivial_destructor;

  ft::__destroy_aux<ForwardIter>(first, last);
}

}  // namespace ft

#endif  // FT_CONTAINERS_ITERATOR_HPP
