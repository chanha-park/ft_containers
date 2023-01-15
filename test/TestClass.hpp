/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestClass.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:28:24 by chanhpar          #+#    #+#             */
/*   Updated: 2023/01/16 02:09:17 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_TEST_CLASS_HPP
#define FT_CONTAINERS_TEST_CLASS_HPP

#include <iostream>
#include <stdexcept>

#define EXCEPTION_COUNT 2000

template <typename T>
struct NormalClass {
  T value;

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

  bool
  operator==(const NormalClass& other) const {
    return (this->value == other.value);
  }

  bool
  operator<(const NormalClass& other) const {
    return (this->value < other.value);
  }
};

template <typename T>
std::ostream&
operator<<(std::ostream& os, const NormalClass<T>& x) {
  os << x.value;
  return (os);
}

template <typename T>
struct AssignException {
  static int counter;
  T* ptr;

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
    if (counter == EXCEPTION_COUNT)
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

  bool
  operator==(const AssignException& other) const {
    return (*this->ptr == *other.ptr);
  }

  bool
  operator<(const AssignException& other) const {
    return (*this->ptr < *other.ptr);
  }
};

template <typename T>
int AssignException<T>::counter = 0;

template <typename T>
std::ostream&
operator<<(std::ostream& os, const AssignException<T>& x) {
  os << *x.ptr;
  return (os);
}

template <typename T>
struct CopyException {
  static int counter;
  T* ptr;

  CopyException(T val) : ptr(new T) {
    *ptr = val;
    ++counter;
  }

  CopyException(const CopyException& other) {
    if (counter == EXCEPTION_COUNT)
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

  bool
  operator==(const CopyException& other) const {
    return (*this->ptr == *other.ptr);
  }

  bool
  operator<(const CopyException& other) const {
    return (*this->ptr < *other.ptr);
  }
};

template <typename T>
int CopyException<T>::counter = 0;

template <typename T>
std::ostream&
operator<<(std::ostream& os, const CopyException<T>& x) {
  os << *x.ptr;
  return (os);
}

#endif  // FT_CONTAINERS_TEST_CLASS_HPP
