#ifndef _EXPR_TERNARY_NODE_H
#define _EXPR_TERNARY_NODE_H

#include <iostream>
#include <fstream>

#include "expr_node.h"

using std::ostream;
using std::ofstream;

class expr_ternary_node : public expr_node {
  public:
    expr_ternary_node(expr_node *t, expr_node *ot, expr_node *of) {
      test = t;
      on_true = ot;
      on_false = of;
    }

    void evaluate(ofstream& file) {
      file << "(";
      test->evaluate(file);
      file << ") ? (";
      on_true->evaluate(file);
      file << ") : (";
      on_false->evaluate(file);
      file << ")";
    }

  private:
    expr_node *test;
    expr_node *on_true;
    expr_node *on_false;

    virtual ostream& printHelper(ostream &os) const {
      os << "test=" << *test;
      os << ", on_true=" << *on_true;
      os << " and on_false=" << *on_false;
      return os;
    }
};
#endif // _EXPR_TERNARY_NODE_H