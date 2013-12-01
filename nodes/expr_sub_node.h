#ifndef _EXPR_SUB_NODE_H
#define _EXPR_SUB_NODE_H

#include <iostream>

#include "expr_node.h"

using std::ostream;

class expr_sub_node : public expr_node {
  public:
  expr_sub_node(expr_node &left, expr_node &right) {
      this->left = left;
      this->right = right;
    }
  
    int evaluate() {
      result = left.evaluate() - right.evaluate();
      return result;
    }

  private:
    expr_node left;
    expr_node right;
    int result;
};
#endif // _EXPR_ADD_NODE_H
