#ifndef _EXPR_ADD_NODE_H
#define _EXPR_ADD_NODE_H

#include <iostream>

#include "expr_node.h"

using std::ostream;

class expr_add_node : public expr_node {
  public:
  expr_add_node(expr_node &left, expr_node &right) {
      this->left = left;
      this->right = right;
    }
  
    int evaluate() {
      value = left.evaluate() + right.evaluate();
      return value;
    }

  private:
    expr_node left;
    expr_node right;

    virtual ostream& printHelper(ostream &os) const {
      os << "left=" << left;
      os << " plus right=" << right;
      return os;
    }
};
#endif // _EXPR_ADD_NODE_H
