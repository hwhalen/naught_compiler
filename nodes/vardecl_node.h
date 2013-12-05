#ifndef _VARDECL_NODE_H
#define _VARDECL_NODE_H

#include <string>
#include <fstream>
#include <map>

#include "expr_node.h"

using std::string;

class vardecl_node {
  public:
    vardecl_node(string &t, string &i, bool e) {
      external = e;
      if (t == "pointer") {
        type = "int32_t*";
      } else if (t == "int") {
        type = "int32_t";
      } else {
        type = "char *";
      }
      ID = i;
    }

    virtual void evaluate(std::ofstream &file, int *curr_id, int *tab_width, std::map<string, string> *symbol_table) {
      (*symbol_table)[ID] = type;
      for (int i = 0; i < *tab_width; i++) {
        file << "  ";
      }
      if (external) {
        file << "external ";
      }
      if(type == "char *") {
        file << "nstring " << ID << "nString;\n";
      }
      file << type << " ";
      file << ID << ";\n";
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
      os << " and ID=" << ID;
      return os;
    }
};
#endif // _VARDECL_NODE_H
