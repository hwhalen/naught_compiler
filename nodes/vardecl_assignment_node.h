#ifndef _VARDECL_ASSIGNMENT_NODE_H
#define _VARDECL_ASSIGNMENT_NODE_H

#include <string>
#include <fstream>

#include "vardecl_node.h"
#include "expr_node.h"

using std::string;

class vardecl_assignment_node : public vardecl_node {
  public:
    vardecl_assignment_node(string &t, string &i, bool e, expr_node *v) : vardecl_node(t, i, e) {
      if (t == "string") {
        type = "char*";
      } else if (t == "pointer") {
        type = "int32_t*";
      } else {
        type = "int32_t";
      }
      value = v;
    }


    void evaluate(std::ofstream &file, int *curr_id) {
      string tempVal = value->evaluate(file, curr_id, false);
      file << "  ";
      if (external) {
        file << "external ";
      }
      file << type << " ";
      file << ID << " = ";
      file << tempVal;
      file << ";\n";
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
