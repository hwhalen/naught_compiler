#ifndef _EXPR_SUB_NODE_H
#define _EXPR_SUB_NODE_H

#include <iostream>
#include <fstream>

#include "expr_node.h"

using std::ostream;
using std::ofstream;
using std::pair;

class expr_sub_node : public expr_node {
  public:
  expr_sub_node(expr_node *left, expr_node *right) {
      this->left = left;
      this->right = right;
    }
  
  pair<string, string> *evaluate(ofstream& file, int *curr_id, int *tab_width) {
    pair<string, string> *leftVal = left->evaluate(file, curr_id, tab_width);
    pair<string, string> *rightVal = right->evaluate(file, curr_id, tab_width);
    (*tab_width)++;
    file << "tempSub" << *curr_id<< " = ";
    file << leftVal->first << " - " << rightVal->first << ";\n";
    std::stringstream sstm;
    sstm << "tempsub" << *curr_id;
    return new pair<string, string>(sstm.str(), leftVal->second);;
  }

  private:
    expr_node *left;
    expr_node *right;
};
#endif // _EXPR_ADD_NODE_H
