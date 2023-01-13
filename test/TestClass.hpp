/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testClass.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:28:24 by chanhpar          #+#    #+#             */
/*   Updated: 2023/01/13 16:34:09 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_TEST_CLASS_HPP
#define FT_CONTAINERS_TEST_CLASS_HPP

#include <stdexcept>

class NormalClass {
  int value;

 public:
  NormalClass(void) : value() {
  }

  NormalClass(int value) : value(value) {
  }

  const NormalClass&
  operator=(const NormalClass& other) {
    this->value = other.value;
    return (*this);
  }

  NormalClass(const NormalClass& other) : value(other.value) {
  }
};

class NoDefaultCtor {
  int value;

  NoDefaultCtor(void);

 public:
  NoDefaultCtor(int value) : value(value) {
  }

  const NoDefaultCtor&
  operator=(const NoDefaultCtor& other) {
    this->value = other.value;
    return (*this);
  }

  NoDefaultCtor(const NoDefaultCtor& other) : value(other.value) {
  }
};

class AssignException {
  static int counter;
  int* ptr;

 public:
  AssignException(void) : ptr(new int) {
    *ptr = 0;
    ++counter;
  }

  AssignException(const AssignException& other) {
    ptr = new int;
    *ptr = *(other.ptr);
    ++counter;
  }

  const AssignException&
  operator=(const AssignException& other) {
    if (counter == 20)
      throw(std::runtime_error("Error from Assignment"));

    delete ptr;
    ptr = new int;
    *ptr = *(other.ptr);
    ++counter;
    return (*this);
  }

  ~AssignException(void) {
    delete ptr;
  }
};

class CopyException {
  static int counter;
  int* ptr;

 public:
  CopyException(void) : ptr(new int) {
    *ptr = 0;
    ++counter;
  }

  CopyException(const CopyException& other) {
    if (counter == 20)
      throw(std::runtime_error("Error from Copy Constructor"));
    ptr = new int;
    *ptr = *(other.ptr);
    ++counter;
  }

  const CopyException&
  operator=(const CopyException& other) {
    delete ptr;
    ptr = new int;
    *ptr = *(other.ptr);
    return (*this);
  }

  ~CopyException(void) {
    delete ptr;
  }
};

#endif  // FT_CONTAINERS_TEST_CLASS_HPP
