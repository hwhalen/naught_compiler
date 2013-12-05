#ifndef _EXPR_DIV_NODE_H
#define _EXPR_DIV_NODE_H

#include <iostream>
#include <fstream>
#include <map>

#include "expr_node.h"

using std::ostream;
using std::ofstream;

class expr_div_node : public expr_node {
  public:
  expr_div_node(expr_node *left, expr_node *right) {
      this->left = left;
      this->right = right;
  }
  
  ~expr_div_node() {
    delete left;
    delete right;
  }

  pair<string, string> *evaluate(ofstream file, int *curr_id, int *tab_width, std::map<string, string> *symbol_table) {
    pair<string, string> *leftVal = left->evaluate(file, curr_id, tab_width, symbol_table);
    pair<string, string> * rightVal = right->evaluate(file, curr_id, tab_width, symbol_table);
    (*curr_id)++;
    file << "int32_t tempDiv" << *curr_id << " = ";
    file << leftVal->first << " / " << rightVal->first << ";\n";
    std::stringstream sstm;
    sstm << "tempDiv" << *curr_id;
    string type = leftVal->second;
    delete leftVal;
    delete rightVal;

    return new pair<string, string>(sstm.str(), type);
  }

  private:
    expr_node *left;
    expr_node *right;
    int result;
};
#endif // _EXPR_DIV_NODE_H
