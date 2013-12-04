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
  
    string evaluate(ofstream& file, int *curr_id, bool print) {
      //temp_count++;
      
      string leftTemp = left->evaluate(file, curr_id, false);
      string rightTemp = right->evaluate(file, curr_id, false);
      
      file << "  tempAdd = " << leftTemp << " + " << rightTemp << ";\n";  
      return "tempAdd";
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
