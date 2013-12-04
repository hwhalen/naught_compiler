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

    string evaluate(ofstream& file, int *curr_id, bool print) {
      string expr = right->evaluate(file, curr_id, false);
      file << "  ";
      left->evaluate(file, curr_id, true);
      file << " = ";
      file << expr;
      return "";
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
