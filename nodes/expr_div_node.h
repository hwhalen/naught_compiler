#ifndef _EXPR_DIV_NODE_H
#define _EXPR_DIV_NODE_H

#include <iostream>
#include <fstream>

#include "expr_node.h"

using std::ostream;
using std::ofstream;

class expr_div_node : public expr_node {
  public:
  expr_div_node(expr_node *left, expr_node *right) {
      this->left = left;
      this->right = right;
    }
  
  string evaluate(ofstream file, int *curr_id, int *tab_width) {
    string leftVal = left->evaluate(file, curr_id, tab_width);
    string rightVal = right->evaluate(file, curr_id, tab_width);
    (*curr_id)++;
    file << "int tempDiv" << *curr_id << " = ";
    file << leftVal << " / " << rightVal << ";\n";
    std::stringstream sstm;
    sstm << "tempDiv" << *curr_id;
    return sstm.str();
  }

  private:
    expr_node *left;
    expr_node *right;
    int result;
};
#endif // _EXPR_DIV_NODE_H
