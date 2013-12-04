#ifndef _PARAM_NODE_H
#define _PARAM_NODE_H

#include <string>
#include <iostream>
#include <vector>
#include <fstream>

using std::string;
using std::ostream;
using std::vector;
using std::ofstream;

class param_node {
  public:
    param_node(string t, string i) {
      if (t == "pointer") {
        type = "int32_t*";
      } else if (t == "string") {
        type = "char*";
      } else {
        type = "int32_t";
      }
      ID = i;
    }

    friend ostream& operator<<(ostream &os, const param_node &obj) {
      return (obj.printHelper(os));
    }

    void evaluate(ofstream &file) {
      file << type << " " << ID;
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

