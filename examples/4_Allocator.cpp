#include <cstdlib>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace example {

template <typename T>
struct SampleAllocator {
  typedef T value_type;
  typedef T* pointer;
  typedef const T* const_pointer;
  typedef T& reference;
  typedef const T& const_reference;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;

  template <typename U>
  struct rebind {
    typedef SampleAllocator<U> other;
  };

  SampleAllocator(void) throw() {
  }

  SampleAllocator(const SampleAllocator& other) throw() {
    (void)other;
  }

  template <typename U>
  SampleAllocator(const SampleAllocator<U>& other) throw() {
    (void)other;
  }

  pointer
  allocate(size_type n, const void* hint = NULL) {
    (void)hint;
    pointer tmp = static_cast<pointer>(std::malloc(n * sizeof(value_type)));
    if (tmp == NULL)
      throw(std::bad_alloc());
    return (tmp);
  }

  void
  deallocate(pointer p, size_type n) {
    (void)n;
    free(p);
  }

  size_type
  max_size(void) const throw() {
    return (std::numeric_limits<size_type>::max() / sizeof(value_type));
  }

  void
  construct(pointer p, const_reference val) {
    ::new (static_cast<void*>(p)) value_type(val);
  }

  void
  destroy(pointer p) {
    p->~T();
  }
};

template <typename T>
struct PseudoAllocator {
  typedef T value_type;
  typedef T* pointer;
  typedef const T* const_pointer;
  typedef T& reference;
  typedef const T& const_reference;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;

  template <typename U>
  struct rebind {
    typedef PseudoAllocator<U> other;
  };

  static const size_type LIMIT = 1000000;

  size_type idx;
  unsigned char space[LIMIT];
  unsigned char status[LIMIT >> 3];

  PseudoAllocator(void) throw() : idx(0), space(), status() {
  }

  PseudoAllocator(const PseudoAllocator& other) throw() :
      idx(0), space(), status() {
    (void)other;
  }

  template <typename U>
  PseudoAllocator(const PseudoAllocator<U>& other) throw() :
      idx(0), space(), status() {
    (void)other;
  }

  pointer
  allocate(size_type n, const void* hint = NULL) {
    (void)hint;
    if (LIMIT - idx < n * sizeof(value_type))
      throw(std::bad_alloc());
    pointer p = static_cast<pointer>(static_cast<void*>(&(space[idx])));
    idx += n * sizeof(value_type);
    return (p);
  }

  void
  deallocate(pointer p, size_type n) {
    (void)n;
    (void)p;
  }

  size_type
  max_size(void) const throw() {
    return (std::numeric_limits<size_type>::max() / sizeof(value_type));
  }

  void
  construct(pointer p, const_reference val) {
    ::new (static_cast<void*>(p)) value_type(val);
  }

  void
  destroy(pointer p) {
    p->~T();
  }
};

}  // namespace example

class A {
 public:
  int* ptr;

  A(void) : ptr(new int) {
    *ptr = 4;
  }

  A(const A& other) : ptr(new int) {
    *ptr = *other.ptr;
  }

  const A&
  operator=(const A& other) {
    *ptr = *other.ptr;
    return (*this);
  }

  ~A(void) {
    delete ptr;
  }
};

int
main(void) {
  {
    std::vector<A, example::SampleAllocator<int> > vec;
    std::map<int, int, std::less<int>, example::SampleAllocator<int> > m;
    for (int i = 0; i < 100; ++i) {
      vec.push_back(A());
      m.insert(std::make_pair(i, -i));
    }
  }
  {
    std::vector<A, example::PseudoAllocator<int> > vec;
    std::map<int, int, std::less<int>, example::PseudoAllocator<int> > m;
    for (int i = 0; i < 100; ++i) {
      vec.push_back(A());
      m.insert(std::make_pair(i, -i));
    }
  }
  return (0);
}
