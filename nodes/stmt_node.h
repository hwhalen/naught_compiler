#ifndef _STMT_NODE_H
#define _STMT_NODE_H

#include <iostream>

using std::ostream;

class stmt_node {
  public:
    stmt_node(expr_node *expr) {
      std::cout << "stmt_node created with value " << *expr <<  std::endl;
      this->expr = expr;
    }


    friend ostream& operator<<(ostream &os, const stmt_node &obj) {
      os << *obj.expr;
      os << ";";
      return os;
    }
  private:
    expr_node *expr;
    virtual ostream& printHelper(ostream &os) const {
      return os;
    }
}; 

#endif // _STMT_NODE_H
