#ifndef _VARDECL_ASSIGNMENT_NODE_H
#define _VARDECL_ASSIGNMENT_NODE_H

#include <string>
#include <fstream>
#include <map>

#include "vardecl_node.h"
#include "expr_node.h"

using std::string;
using std::pair;

class vardecl_assignment_node : public vardecl_node {
  public:
    vardecl_assignment_node(string &t, string &i, bool e, expr_node *v) : vardecl_node(t, i, e) {
      if (t == "string") {
        type = "char *";
      } else if (t == "pointer") {
        type = "int32_t*";
      } else {
        type = "int32_t";
      }
      value = v;
  }

    void evaluate(std::ofstream &file, int *curr_id, int *tab_width, std::map<string, string> *symbol_table) {
      (*symbol_table)[ID] = type;
      pair<string, string> *tempVal = value->evaluate(file, curr_id, tab_width, symbol_table);
      insert_tabbing(file, *tab_width);
      if (external) {
        file << "external ";
      }
      if(type == "char *") {
        file << "nstring " << ID << "nString;\n";
        insert_tabbing(file, *tab_width);
        file << ID << "nString.len = strlen(" << tempVal->first << ");\n";
        insert_tabbing(file, *tab_width);
        file << ID << "nString.str = (char *) malloc("; 
        file << ID << "nString.len + 1" << ");\n";
        insert_tabbing(file, *tab_width);
        file << "strcpy(" << ID << "nString.str, " << tempVal->first << ");\n";
        insert_tabbing(file, *tab_width);
        file << type << " " << ID << " = " << ID << "nString.str;\n";
      } else {
        file << type << " ";
        file << ID << " = ";
        file << tempVal->first;
        file << ";\n";
      }
    }

  protected:
    void insert_tabbing(ofstream& file, int tab_width) {
      for (int i = 0; i < tab_width; i++) {
        file << "  ";
      }
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
