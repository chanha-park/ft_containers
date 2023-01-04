// #include <__tree>
#include <iostream>
#include <map>
#include <string>
#include "../tree__.hpp"

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
}

int
main(void) {
  f();
  system("leaks $PPID");
  return (0);
}
