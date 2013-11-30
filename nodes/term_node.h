#ifndef _TERM_NODE_H
#define _TERM_NODE_H

#include <iostream>

#include "expr_node.h"

//using std::ostream;

// parent class for term
class term_node : public expr_node {
  public:
    term_node() {
    }

    friend ostream& operator<<(ostream &os, const term_node &obj) {
      return (obj.printHelper(os));
    }

    virtual int& evaluate() {
      return result;
    }

  private:
    int result = 0;
    ostream& printHelper(ostream &os) const{
      return os;
    }
};
#endif // _TERM_NODE_H
