#ifndef _TERM_NODE_H
#define _TERM_NODE_H

#include <iostream>

#include "expr_node.h"

using std::ostream;

// parent class for term
class term_node : public expr_node {
  public:
    term_node() {
    }

    friend ostream& operator<<(ostream &os, const term_node &obj) {
      return (obj.printHelper(os));
    }

    int evaluate() {
      return value;
    }
    
    virtual void setVal(int v) {
      value = v;
    }

  private:
    ostream& printHelper(ostream &os) const{
      return os;
    }
};
#endif // _TERM_NODE_H
