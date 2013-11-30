#ifndef _EXPR_NODE_H
#define _EXPR_NODE_H

#include <iostream>

using std::ostream;

// parent class for term
class expr_node {
  public:
    expr_node() {
    }

    friend ostream& operator<<(ostream&os, const expr_node &obj) {
      return obj.printHelper(os);
    }
    
    virtual int& evaluate() {
      std::cout << "this is called" << endl;
      return result;
    }

  private:
    int result = 0;
    virtual ostream& printHelper(ostream &os) const {
      return os;
    }
};

#endif // _EXPR_NODE_H
