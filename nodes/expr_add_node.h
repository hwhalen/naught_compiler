#ifndef _EXPR_ADD_NODE_H
#define _EXPR_ADD_NODE_H

#include <iostream>
#include <fstream>

#include "expr_node.h"

using std::ostream;
using std::ofstream;
using std::endl;

class expr_add_node : public expr_node {
  public:
    expr_add_node(expr_node *l, expr_node *r) {
      left = l;
      right = r;
    }
  
    void evaluate(ofstream& file, int *curr_id) {
      left->evaluate(file, curr_id);
      file << " + ";
      right->evaluate(file, curr_id);
    }

  private:
    expr_node *left;
    expr_node *right;

    virtual ostream& printHelper(ostream &os) const {
      os << "left=" << *left;
      os << " plus right=" << *right;
      return os;
    }
};
#endif // _EXPR_ADD_NODE_H
