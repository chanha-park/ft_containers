// #include <__tree>
#include <iostream>
// #include <map>
#include <string>
#include "../tree__.hpp"
#include "../vector.hpp"

void
f(void) {
  ft::rb_tree__<int,
                ft::pair<int, char>,
                ft::functor_first__<ft::pair<int, char> >,
                std::less<int> >
      tr;
  ft::rb_tree__<int,
                ft::pair<int, char>,
                ft::functor_first__<ft::pair<int, char> >,
                std::less<int> >::iterator it;
  ft::rb_tree__<int,
                ft::pair<int, char>,
                ft::functor_first__<ft::pair<int, char> >,
                std::less<int> >::const_iterator cit;
  ft::rb_tree__<int,
                ft::pair<int, char>,
                ft::functor_first__<ft::pair<int, char> >,
                std::less<int> >::reverse_iterator rit;
  ft::rb_tree__<int,
                ft::pair<int, char>,
                ft::functor_first__<ft::pair<int, char> >,
                std::less<int> >::const_reverse_iterator crit;
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
  tr.insert_unique(ft::make_pair(100, 'd'));
  tr.insert_unique(ft::make_pair(100, 'd'));
  // for (crit = tr.rbegin(); crit != tr.rend(); ++crit) {
  //   std::cout << crit->first << std::endl;
  // }

  for (rit = tr.rbegin(); rit != tr.rend(); ++rit) {
    std::cout << rit->first << std::endl;
  }

  if (tr.verify_tree__())
    std::cout << "RBTree OK" << std::endl;
  else
    std::cout << "RBTree KO" << std::endl;
}

int
main(void) {
  f();
  system("leaks $PPID");
  return (0);
}
