#ifndef _VARDECL_NODE_H
#define _VARDECL_NODE_H

#include <string>

#include "expr_node.h"

using std::string;

class vardecl_node {
  public:
    vardecl_node(string t, string i, bool e) {
      external = e;
      type = t;
      ID = i;
    }

    void set_payload(expr_node *v) {
      value = v;
    }
    
    friend ostream& operator<<(ostream &os, const vardecl_node &obj) {
      return (obj.printHelper(os));
    }

  private:
    bool external;
    string type;
    string ID;
    expr_node *value;

    virtual ostream& printHelper(ostream &os) const {
      os << "external=" << external;
      os << ", type=" << type;
      os << ", ID=" << ID;
      os << ", and value=" << *value;
      return os;
    }
};
#endif // _VARDECL_NODE_H
