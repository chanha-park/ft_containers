// #include <__tree>
#include <iostream>
#include <map>
#include <string>
#include "../tree__.hpp"

int
main(void) {
  ft::rb_tree__<int,
                ft::pair<int, std::string>,
                ft::functor_first__<ft::pair<int, std::string> >,
                std::less<int> >
      tr;
  ft::rb_tree__<int,
                ft::pair<int, std::string>,
                ft::functor_first__<ft::pair<int, std::string> >,
                std::less<int> >::iterator it;
  ft::rb_tree__<int,
                ft::pair<int, std::string>,
                ft::functor_first__<ft::pair<int, std::string> >,
                std::less<int> >::const_iterator cit;
  ft::rb_tree__<int,
                ft::pair<int, std::string>,
                ft::functor_first__<ft::pair<int, std::string> >,
                std::less<int> >::reverse_iterator rit;
  ft::rb_tree__<int,
                ft::pair<int, std::string>,
                ft::functor_first__<ft::pair<int, std::string> >,
                std::less<int> >::const_reverse_iterator crit;
  (void)tr;
  (void)it;
  (void)cit;
  (void)rit;
  (void)crit;
  // ++it;
  return (0);
}
