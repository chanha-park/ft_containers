/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 19:09:39 by chanhpar          #+#    #+#             */
/*   Updated: 2022/12/17 02:01:09 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_MAP_HPP

#include <functional>
#include <memory>
#include "iterator.hpp"
#include "utility.hpp"

namespace ft {

template <typename Key,
          typename T,
          typename Compare = std::less<Key>,
          typename Allocator = std::allocator<ft::pair<const Key, T> > >
class map {
 public:
  typedef Key key_type;
  typedef T mapped_type;
  typedef typename ft::pair<const key_type, mapped_type> value_type;
  typedef Compare key_compare;
  typedef Allocator allocator_type;

  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef typename Allocator::pointer pointer;
  typedef typename Allocator::const_pointer const_pointer;

  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;

  // typedef implementation-defined                   iterator;
  // typedef implementation-defined                   const_iterator;
  // typedef ft::reverse_iterator<iterator>          reverse_iterator;
  // typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;

  class value_compare :
      public std::binary_function<value_type, value_type, bool> {
   private:
    // friend class map; // why?
   protected:
    key_compare comp;

    // protected ctor
    value_compare(key_compare c) : comp(c) {
    }

   public:
    typedef bool result_type;
    typedef value_type first_argument_type;
    typedef value_type second_argument_type;

    result_type
    operator()(const value_type& x, const value_type& y) const {
      return (comp(x.first, y.first));
    }
  };

 private:
 protected:
 public:
};

}  // namespace ft

#endif  // FT_CONTAINERS_MAP_HPP
