#ifndef _STMT_NODE_H
#define _STMT_NODE_H

#include <iostream>
#include <fstream>

#include "expr_node.h"

using std::ostream;
using std::ofstream;

class stmt_node {
  public:
    stmt_node(expr_node *expr, bool r) {
      this->expr = expr;
      should_return = r;
    }

    void evaluate(ofstream &file) {
      if (should_return) {
        file << "  return ";
      }
      expr->evaluate(file);
      file << ";" << std::endl;
    }

    friend ostream& operator<<(ostream &os, const stmt_node &obj) {
      os << *obj.expr;
      os << ";";
      return os;
    }

  private:
    bool should_return;
    expr_node *expr;
    virtual ostream& printHelper(ostream &os) const {
      return os;
    }
}; 

#endif // _STMT_NODE_H
