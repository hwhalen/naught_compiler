#ifndef _PARAM_NODE_H
#define _PARAM_NODE_H

#include <string>
#include <iostream>
#include <vector>

using std::string;
using std::ostream;
using std::vector;

class param_node {
  public:
    param_node(string t, string i) {
      type = t;
      ID = i;
    }

    friend ostream& operator<<(ostream &os, const param_node &obj) {
      return (obj.printHelper(os));
    }

  private:
    string type;
    string ID;

    virtual ostream& printHelper(ostream &os) const {
      os << type;
      os << " " << ID;
      return os;
    }
};
#endif // _PARAM_NODE_H

