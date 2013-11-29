#ifndef _EXPR_ADD_NODE_H
#define _EXPR_ADD_NODE_H

#include <iostream>

#include "expr_node.h"

using std::ostream;

class expr_add_node : public expr_node {
  public:
  expr_add_node(expr_node &left, expr_node &right) {
      std::cout << "expr_add_node created" << std::endl;
      this->left = left;
      this->right = right;
    }
  
    int evaluate() {
      return left.evaluate() + right.evaluate();
    }

  private:
    expr_node left;
    expr_node right;
};
#endif // _EXPR_ADD_NODE_H
