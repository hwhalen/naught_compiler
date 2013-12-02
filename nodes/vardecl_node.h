#ifndef _VARDECL_NODE_H
#define _VARDECL_NODE_H

#include <string>
#include <fstream>

#include "expr_node.h"

using std::string;

class vardecl_node {
  public:
    vardecl_node(string t, string i, bool e) {
      external = e;
      type = t;
      ID = i;
    }

    void evaluate(std::ofstream &file) {
      if (external) {
        file << "external ";
      }
      file << type << " ";
      file << ID;
    }

    friend ostream& operator<<(ostream &os, const vardecl_node &obj) {
      return (obj.printHelper(os));
    }

  protected:
    bool external;
    string type;
    string ID;

  private:
    virtual ostream& printHelper(ostream &os) const {
      os << "external=" << external;
      os << ", type=" << type;
      os << " and  ID=" << ID;
      return os;
    }
};
#endif // _VARDECL_NODE_H
