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

    string evaluate(ofstream& file, int *curr_id, int *tab_width) {
      string temp_left = left->evaluate(file, curr_id, tab_width);
      string temp_right = right->evaluate(file, curr_id, tab_width);
      for (int i = 0; i < *tab_width; i++) {
        file << "  ";
      }
      file << temp_left << " = ";
      file << temp_right << ";\n";
      return temp_left;
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
