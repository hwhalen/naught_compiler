#ifndef _MODULE_NODE_H
#define _MODULE_NODE_H

#include <vector>
#include <string>
#include <iostream>

#include "funcdecl_node.h"
#include "vardecl_node.h"
#include "funcdef_node.h"

using std::ostream;
using std::vector;
using std::string;
using std::ofstream;

class module_node {
  public:
    module_node(vector<funcdecl_node *> *fdl, vector<vardecl_node *> *vdl, vector<funcdef_node *> *l) {
      func_decl_list = *fdl;
      var_decl_list = *vdl;
      func_def_list = *l;
    }

    friend ostream& operator<<(ostream &os, const module_node &obj) {
      os << "func_decl_list={";
      for (size_t i = 0; i < obj.func_decl_list.size(); i++) {
        os << "(" << *(obj.func_decl_list[i]) << ")";
      }
      os << "}";
      os << "var_decl_list={";
      for (size_t i = 0; i < obj.var_decl_list.size(); i++) {
        os << "(" << *(obj.var_decl_list[i]) << ")";
      }
      os << "}";
      os << "func_def_list={";
      for (size_t i = 0; i < obj.func_def_list.size(); i++) {
        os << "(" << *(obj.func_def_list[i]) << ")";
      }
      os << "}";
      return os;
    }

    void evaluate(ofstream& file){
      file << "#include <stdint.h>" << std::endl;
      for (size_t i = 0; i < func_decl_list.size(); i++) {
        func_decl_list[i]->evaluate(file);
      }
      for (size_t i = 0; i < var_decl_list.size(); i++) {
        var_decl_list[i]->evaluate(file);
      }
      for (size_t i = 0; i < func_def_list.size(); i++) {
        func_def_list[i]->evaluate(file);
      }
    }

  private:
    vector<funcdecl_node *> func_decl_list;
    vector<vardecl_node *> var_decl_list;
    vector<funcdef_node *> func_def_list;
};
#endif // _MODULE_NODE_H
