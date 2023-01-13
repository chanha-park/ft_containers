#include <deque>
#include <iostream>
#include <string>

#ifdef STD
#  include <map>
#  include <stack>
#  include <vector>
#  define NAMESPACE std
#  define FILENAME "std_output.txt"
#else
#  include "map.hpp"
#  include "stack.hpp"
#  include "vector.hpp"
#  define NAMESPACE ft
#  define FILENAME "ft_output.txt"
#endif

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "test.hpp"

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

  int fd = open(FILENAME, O_WRONLY | O_CREAT | O_TRUNC, 0664);
  dup2(fd, STDOUT_FILENO);
  close(fd);

  TEST_VECTOR();
  TEST_STACK();
  TEST_MAP();
  TEST_SET();
  TEST_OTHERS();

#if defined __APPLE__
  system("leaks $PPID");
#endif
  return (0);
}
