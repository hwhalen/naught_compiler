#ifndef _EXPR_NODE_H
#define _EXPR_NODE_H

#include <iostream>
#include <fstream>

using std::ostream;
using std::ofstream;

// parent class for term
class expr_node {
  public:
    expr_node() {
    }

    friend ostream& operator<<(ostream&os, const expr_node &obj) {
      return obj.printHelper(os);
    }
    
    virtual void evaluate(ofstream& file) {
      std::cout << "expr_node evaluate is called" << endl;
    }

  private:
    virtual ostream& printHelper(ostream &os) const {
      return os;
    }
};

#endif // _EXPR_NODE_H
