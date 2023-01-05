base_node__*
erase_and_rebalance__(base_node__* const __z,
                      _Rb_tree_node_base*& __header) throw() {
  base_node__*& __root = __header->parent;
  base_node__*& __leftmost = __header->left;
  base_node__*& __rightmost = __header->right;
  base_node__* __y = __z;
  base_node__* __x = 0;
  base_node__* __x_parent = 0;

  if (__y->left == 0)        // __z has at most one non-null child. y == z.
    __x = __y->right;        // __x might be null.
  else if (__y->right == 0)  // __z has exactly one non-null child. y == z.
    __x = __y->left;         // __x is not null.
  else {                     // __z has two non-null children.  Set __y to
    __y = __y->right;        //   __z's successor.  __x might be null.
    while (__y->left != 0)
      __y = __y->left;
    __x = __y->right;
  }

  if (__y != __z) {  // relink y in place of z.  y is z's successor

    __z->left->parent = __y;
    __y->left = __z->left;

    if (__y != __z->right) {
      __x_parent = __y->parent;
      if (__x)
        __x->parent = __y->parent;
      __y->parent->left = __x;  // __y must be a child of left
      __y->right = __z->right;
      __z->right->parent = __y;

    } else {
      __x_parent = __y;
    }

    if (__root == __z)
      __root = __y;
    else if (__z->parent->left == __z)
      __z->parent->left = __y;
    else
      __z->parent->right = __y;

    __y->parent = __z->parent;
    std::swap(__y->color, __z->color);
    __y = __z;
    // __y now points to node to be actually deleted

  } else {  // __y == __z

    __x_parent = __y->parent;
    if (__x)
      __x->parent = __y->parent;

    if (__root == __z)
      __root = __x;
    else if (__z->parent->left == __z)
      __z->parent->left = __x;
    else
      __z->parent->right = __x;

    if (__leftmost == __z) {
      if (__z->right == 0)  // __z->left must be null also
        __leftmost = __z->parent;
      // makes __leftmost == _M_header if __z == __root
      else
        __leftmost = base_node__::_S_minimum(__x);
    }

    if (__rightmost == __z) {
      if (__z->left == 0)  // __z->right must be null also
        __rightmost = __z->parent;
      // makes __rightmost == _M_header if __z == __root
      else  // __x == __z->left
        __rightmost = base_node__::_S_maximum(__x);
    }
  }

  if (__y->color != red__) {
    while (__x != __root && (__x == 0 || __x->color == black__))

      if (__x == __x_parent->left) {
        base_node__* __w = __x_parent->right;
        if (__w->color == red__) {
          __w->color = black__;
          __x_parent->color = red__;
          rotate_left__(__x_parent, __root);
          __w = __x_parent->right;
        }

        if ((__w->left == 0 || __w->left->color == black__)
            && (__w->right == 0 || __w->right->color == black__)) {
          __w->color = red__;
          __x = __x_parent;
          __x_parent = __x_parent->parent;

        } else {
          if (__w->right == 0 || __w->right->color == black__) {
            __w->left->color = black__;
            __w->color = red__;
            rotate_right__(__w, __root);
            __w = __x_parent->right;
          }
          __w->color = __x_parent->color;
          __x_parent->color = black__;

          if (__w->right)
            __w->right->color = black__;

          rotate_left__(__x_parent, __root);
          break;
        }

      } else {  // same as above, with right <-> left.

        base_node__* __w = __x_parent->left;
        if (__w->color == red__) {
          __w->color = black__;
          __x_parent->color = red__;
          rotate_right__(__x_parent, __root);
          __w = __x_parent->left;
        }
        if ((__w->right == 0 || __w->right->color == black__)
            && (__w->left == 0 || __w->left->color == black__)) {
          __w->color = red__;
          __x = __x_parent;
          __x_parent = __x_parent->parent;

        } else {
          if (__w->left == 0 || __w->left->color == black__) {
            __w->right->color = black__;
            __w->color = red__;
            rotate_left__(__w, __root);
            __w = __x_parent->left;
          }
          __w->color = __x_parent->color;
          __x_parent->color = black__;

          if (__w->left)
            __w->left->color = black__;

          rotate_right__(__x_parent, __root);
          break;
        }
      }

    if (__x)
      __x->color = black__;
  }
  return __y;
}
