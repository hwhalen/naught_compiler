#ifndef _TERM_ID_NODE_H
#define _TERM_ID_NODE_H

#include <iostream>
#include <string>

#include "term_node.h"

using std::ostream;

class term_id_node : public term_node {
  public:
    term_id_node(string id) {
      ID = id;
      value = 0;
    }

    void set_type(string type) {
      this->type = type;
    }

    void setVal(int val) {
      value = val;
    }
    
    int evaluate() {
      return value;
    }

  private:
    string ID;
    string type;
    int value;
    
    ostream& printHelper(ostream &os) const {
      os << type;
      os << " " << ID;
      os << " = " << value;
      return os;
    }
};

#endif // _TERM_ID_NODE_H
