#ifndef _STMT_NODE_H
#define _STMT_NODE_H

#include <iostream>

using std::ostream;

class stmt_node {
  public:
    stmt_node(expr_node *expr) {
      this->expr = expr;
    }


    friend ostream& operator<<(ostream &os, const stmt_node &obj) {
      return os << obj.expr;
    }
  private:
    expr_node *expr;
    virtual ostream& printHelper(ostream &os) const {
      return os;
    }
}; 

#endif // _STMT_NODE_H
