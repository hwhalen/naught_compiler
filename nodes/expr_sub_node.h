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
  
  string evaluate(ofstream& file, int *curr_id, int *tab_width) {
    string leftVal = left->evaluate(file, curr_id, tab_width);
    string rightVal = right->evaluate(file, curr_id, tab_width);
    (*tab_width)++;
    file << "int tempSub" << *curr_id<< " = ";
    file << leftVal << " - " << rightVal << ";\n";
    std::stringstream sstm;
    sstm << "tempsub" << *curr_id;
    return sstm.str();
  }

  private:
    expr_node *left;
    expr_node *right;
};
#endif // _EXPR_ADD_NODE_H
