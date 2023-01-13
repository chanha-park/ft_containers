#include <deque>
#include <iostream>
#include <string>

#ifndef FT
#  include <map>
#  include <stack>
#  include <vector>
#  define NAMESPACE STD
#else
#  include "map.hpp"
#  include "stack.hpp"
#  include "vector.hpp"
#  define NAMESPACE FT
#endif

#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096

struct Buffer {
  int idx;
  char buff[BUFFER_SIZE];
};

#define COUNT (MAX_RAM / (int)sizeof(Buffer))

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

  // test_vector();
  // test_stack();
  // test_set();
  // test_map();

  return (0);
}
