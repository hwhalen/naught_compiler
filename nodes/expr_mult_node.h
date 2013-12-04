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
  
    string evaluate(ofstream &file, int *curr_id, int *tab_width) {
      string leftTemp = left->evaluate(file, curr_id, tab_width);
      string rightTemp = right->evaluate(file, curr_id, tab_width);
      for (int i = 0; i < *tab_width; i++) {
        file << "  ";
      }
      (*curr_id)++;
      file << "tempMult" << *curr_id << " = " << leftTemp << " * " << rightTemp << ";\n";  
      std::stringstream sstm;
      sstm << "tempMult" << *curr_id;
      return sstm.str();
    }

  private:
    expr_node *left;
    expr_node *right;
    int result;

    virtual ostream& printHelper(ostream &os) const {
      os << "left=" << *left;
      os << " mult right=" << *right;
      return os;
    }
};
#endif // _EXPR_MULT_NODE_H
