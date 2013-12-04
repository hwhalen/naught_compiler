#ifndef _TERM_NODE_H
#define _TERM_NODE_H

#include <iostream>
#include <fstream>

#include "expr_node.h"

using std::ostream;
using std::ofstream;

// parent class for term
class term_node : public expr_node{
  public:
    term_node() {
    }

    friend ostream& operator<<(ostream &os, const term_node &obj) {
      return (obj.printHelper(os));
    }

    virtual pair<string, string> *evaluate(ofstream& file, int *curr_id, int *tab_width) {
      std::cout << "term_node evaluate called" << std::endl;
      return nullptr;
    }
    
  private:
    virtual ostream& printHelper(ostream &os) const{
      return os;
    }
};
#endif // _TERM_NODE_H
