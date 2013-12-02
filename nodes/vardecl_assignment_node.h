#ifndef _VARDECL_ASSIGNMENT_NODE_H
#define _VARDECL_ASSIGNMENT_NODE_H

#include <string>
#include <fstream>

#include "vardecl_node.h"
#include "expr_node.h"

using std::string;

class vardecl_assignment_node : public vardecl_node {
  public:
    vardecl_assignment_node(string t, string i, bool e, expr_node *v) : vardecl_node(t, i, e) {
      value = v;
    }

    void evaluate(std::ofstream file) {
      if (external) {
        file << "external ";
      }
      file << type << " ";
      file << ID << " = ";
      value->evaluate(file);
    }

  private:
    expr_node *value;

    virtual ostream& printHelper(ostream &os) const {
      os << "external=" << external;
      os << ", type=" << type;
      os << ", ID=" << ID;
      os << " and value=" << *value;
      return os;
    }
};
#endif // _VARDECL_ASSIGNMENT_NODE_H