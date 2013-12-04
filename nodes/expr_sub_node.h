#ifndef _EXPR_SUB_NODE_H
#define _EXPR_SUB_NODE_H

#include <iostream>
#include <fstream>

#include "expr_node.h"

using std::ostream;
using std::ofstream;
class expr_sub_node : public expr_node {
  public:
  expr_sub_node(expr_node *left, expr_node *right) {
      this->left = left;
      this->right = right;
    }
  
    void evaluate(ofstream& file, int *curr_id) {
      left->evaluate(file, curr_id);
      file << " - ";
      right->evaluate(file, curr_id);
    }

  private:
    expr_node *left;
    expr_node *right;
};
#endif // _EXPR_ADD_NODE_H
