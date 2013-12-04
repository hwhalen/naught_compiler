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
  
    string evaluate(ofstream &file, int *curr_id, bool print) {
      string leftTemp = left->evaluate(file, curr_id, false);
      string rightTemp = right->evaluate(file, curr_id, false);
      
      file << "  tempMult = " << leftTemp << " * " << rightTemp << ";\n";  
      return "tempMult";
    }

  private:
    expr_node *left;
    expr_node *right;
    int result;
};
#endif // _EXPR_MULT_NODE_H
