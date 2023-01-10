// #include <__tree>
#include <iostream>
// #include <map>
#include <string>
#include "../tree__.hpp"
#include "../vector.hpp"

typedef ft::rb_tree__<int,
                      ft::pair<int, char>,
                      ft::functor_first__<ft::pair<int, char> >,
                      std::less<int> >
    tree_t;

void
print_verify(const tree_t& tr) {
  if (tr.verify_tree__())
    std::cout << "RBTree OK" << std::endl << std::endl;
  else
    std::cout << "RBTree KO" << std::endl << std::endl;
}

void
f(void) {
  tree_t tr;
  tree_t::iterator it;
  tree_t::const_iterator cit;
  tree_t::reverse_iterator rit;
  tree_t::const_reverse_iterator crit;

  (void)tr;
  (void)it;
  (void)cit;
  (void)rit;
  (void)crit;

  tr.insert_unique(ft::make_pair(3, 'c'));
  tr.insert_unique(ft::make_pair(9, 'c'));
  tr.insert_unique(ft::make_pair(0, 'c'));
  it = tr.begin();
  ++it;
  --it;
  it++;
  it--;
  tr.insert_hint_unique(it, ft::make_pair(1, 'c'));
  ft::vector<ft::pair<int, char> > vec;
  for (int i = 0; i < 10; ++i) {
    vec.push_back(ft::make_pair(200 - i, i + 100));
  }

  tr.insert_range_unique(vec.begin(), vec.end());

  print_verify(tr);

  tr.insert_unique(ft::make_pair(100, 'd'));
  tr.insert_unique(ft::make_pair(100, 'd'));

  print_verify(tr);

  // for (crit = tr.rbegin(); crit != tr.rend(); ++crit) {
  //   std::cout << crit->first << std::endl;
  // }

  for (it = tr.begin(); it != tr.end(); ++it) {
    if (it->first % 2 == 0) {
      tr.erase(it);
      print_verify(tr);
      it = tr.begin();
    }
  }

  for (rit = tr.rbegin(); rit != tr.rend(); ++rit) {
    std::cout << rit->first << std::endl;
  }

  print_verify(tr);

  for (it = tr.begin(); it != tr.end(); ++it) {
    tr.erase(it);
  }
  print_verify(tr);
}

int
main(void) {
  f();
  system("leaks $PPID");
  return (0);
}
