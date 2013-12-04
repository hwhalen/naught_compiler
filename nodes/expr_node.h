#ifndef _EXPR_NODE_H
#define _EXPR_NODE_H

#include <iostream>
#include <fstream>

using std::ostream;
using std::ofstream;

// parent class for term
class expr_node {
  public:
    static int temp_count;
    expr_node() {
    }

    friend ostream& operator<<(ostream&os, const expr_node &obj) {
      return obj.printHelper(os);
    }
    
    virtual string evaluate(ofstream& file, int *curr_id, bool print) {
      std::cout << "expr_node evaluate is called" << std::endl;
      return NULL;
    }

  private:
    virtual ostream& printHelper(ostream &os) const {
      return os;
    }
};

#endif // _EXPR_NODE_H
