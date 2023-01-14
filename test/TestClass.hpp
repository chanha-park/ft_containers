/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestClass.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:28:24 by chanhpar          #+#    #+#             */
/*   Updated: 2023/01/14 16:53:08 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_TEST_CLASS_HPP
#define FT_CONTAINERS_TEST_CLASS_HPP

#include <stdexcept>

template <typename T>
class NormalClass {
  T value;

 public:
  NormalClass(T value) : value(value) {
  }

  const NormalClass&
  operator=(const NormalClass& other) {
    this->value = other.value;
    return (*this);
  }

  NormalClass(const NormalClass& other) : value(other.value) {
  }

  ~NormalClass(void) {
  }
};

template <typename T>
class AssignException {
  static int counter;
  T* ptr;

 public:
  AssignException(T val) : ptr(new T) {
    *ptr = val;
    ++counter;
  }

  AssignException(const AssignException& other) : ptr(new T) {
    *ptr = *(other.ptr);
    ++counter;
  }

  const AssignException&
  operator=(const AssignException& other) {
    if (counter == 20)
      throw(std::runtime_error("Error from Assignment"));

    delete ptr;
    ptr = new T;
    *ptr = *(other.ptr);
    ++counter;
    return (*this);
  }

  ~AssignException(void) {
    delete ptr;
  }
};

template <typename T>
class CopyException {
  static int counter;
  T* ptr;

 public:
  CopyException(void) : ptr(new T) {
    *ptr = 0;
    ++counter;
  }

  CopyException(const CopyException& other) {
    if (counter == 20)
      throw(std::runtime_error("Error from Copy Constructor"));
    ptr = new T;
    *ptr = *(other.ptr);
    ++counter;
  }

  const CopyException&
  operator=(const CopyException& other) {
    delete ptr;
    ptr = new T;
    *ptr = *(other.ptr);
    return (*this);
  }

  ~CopyException(void) {
    delete ptr;
  }
};

#endif  // FT_CONTAINERS_TEST_CLASS_HPP
