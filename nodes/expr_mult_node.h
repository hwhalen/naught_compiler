#ifndef _EXPR_MULT_NODE_H
#define _EXPR_MULT_NODE_H

#include <iostream>
#include <fstream>

#include "expr_node.h"

using std::ostream;

class expr_mult_node : public expr_node {
  public:
    expr_mult_node(expr_node *left, expr_node *right) {
      this->left = left;
      this->right = right;
    }
  
    void evaluate(ofstream &file, int *curr_id) {
      left->evaluate(file, curr_id);
      file << " * ";
      right->evaluate(file, curr_id);
    }

  private:
    expr_node *left;
    expr_node *right;
    int result;
};
#endif // _EXPR_MULT_NODE_H
