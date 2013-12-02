#ifndef _TERM_EXPR_H
#define _TERM_EXPR_H

#include <iostream>
#include <fstream>

#include "term_node.h"

using std::ostream;
using std::ofstream;

class term_expr_node : public term_node{
  public:
    term_expr_node(expr_node *v) {
      value = v;
    }

    void evaluate(ofstream& file) {
      file << "(";
      value->evaluate(file);
      file << ")";
    }

  private:
    expr_node *value;

    ostream& printHelper(ostream &os) const {
      os << "value=" << *value;
      return os;
    }
};
#endif // _TERM_EXPR_H
