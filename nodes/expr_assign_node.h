#ifndef _EXPR_ASSIGN_NODE_H
#define _EXPR_ASSIGN_NODE_H

#include <iostream>
#include <fstream>

#include "expr_node.h"
#include "term_node.h"

using std::ostream;
using std::ofstream;

class expr_assign_node : public expr_node {
  public:
    expr_assign_node(term_node *left, expr_node *right) {
      this->left = left;
      this->right = right;
    }

    pair<string, string> *evaluate(ofstream& file, int *curr_id, int *tab_width, std::map<string, string> *symbol_table) {
      pair<string, string> *temp_left = left->evaluate(file, curr_id, tab_width, symbol_table);
      pair<string, string> *temp_right = right->evaluate(file, curr_id, tab_width, symbol_table);
      for (int i = 0; i < *tab_width; i++) {
        file << "  ";
      }
      file << temp_left->first << " = ";
      file << temp_right->first << ";\n";
      return new pair<string, string>(temp_left->first, temp_left->second);;
    }

  private:
    term_node *left;
    expr_node *right;

    virtual ostream& printHelper(ostream &os) const {
      os << "left=" << *left;
      os << " assigned right=" << *right;
      return os;
    }
};
#endif // _EXPR_ASSIGN_NODE_H
