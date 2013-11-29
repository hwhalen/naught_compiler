#ifndef _EXPR_ADD_NODE_H
#define _EXPR_ADD_NODE_H

#include <iostream>

#include "expr_node.h"

using std::ostream;

class expr_add_node : public expr_node {
  public:
  expr_add_node(expr_node *left, expr_node *right) {
      std::cout << "expr_add_node created" << std::endl;
      this->left = left;
      this->right = right;
    }

    friend ostream& operator<<(ostream &os, const expr_add_node &obj) {
      os << *left;
      os << " + ";
      os << *right;
      return os;
    }

  private:
    const expr_node *left;
    const expr_node *right;
    ostream& printHelper(ostream &os) const{
      return os;
    }
};
#endif // _EXPR_ADD_NODE_H
