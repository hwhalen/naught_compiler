#ifndef _ID_NODE_H
#define _ID_NODE_H

#include <iostream>
#include <string>

#include "term_node.h"

using std::ostream;

class id_node : public term_node {
  public:
    id_node(string id) {
      ID = id;
    }

    void set_type(string type) {
      this->type = type;
    }

    void setVal(int val) {
      value = val;
    }

  private:
    string ID;
    string type;
    int value;
    
    ostream& printHelper(ostream &os) const {
      os << type;
      os << " " << ID;
      return os;
    }
};

#endif // _ID_NODE_H
