#include <deque>
#include <iostream>
#include <string>

#include "test.hpp"

int
main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Usage: ./test seed" << std::endl;
    std::cerr << "Provide a seed please" << std::endl;
    std::cerr << "Count value:" << COUNT << std::endl;
    return 1;
  }
  const int seed = atoi(argv[1]);
  srand(seed);

  TEST<int>();
  TEST<NormalClass<int> >();
  try {
    TEST<AssignException<int> >();
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }
  try {
    TEST<CopyException<int> >();
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }

#if defined __APPLE__
#  ifndef SANITIZE
  std::cout << "=====Test Leaks=====" << std::endl;
  system("leaks $PPID | grep 'leaked' | cut -f 2 -d ':'");
#  endif
#endif
  return (0);
}
