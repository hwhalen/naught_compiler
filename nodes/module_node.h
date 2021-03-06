// Jordan Heier
// Hunter Whalen

#ifndef _MODULE_NODE_H
#define _MODULE_NODE_H

#include <vector>
#include <string>
#include <iostream>
#include <map>

#include "funcdecl_node.h"
#include "vardecl_node.h"
#include "funcdef_node.h"

using std::ostream;
using std::vector;
using std::string;
using std::ofstream;

// This class represents an entire module. It is the head of the AST
class module_node {
  public:
  // Constructs the module node which consists of a function declaration list,
  // a variable declaration list (globals), and a function definition list.
    module_node(vector<funcdecl_node *> *fdl, vector<vardecl_node *> *vdl, 
                vector<funcdef_node *> *l) {
      func_decl_list = *fdl;
      var_decl_list = *vdl;
      func_def_list = *l;
    }

    // Prints useful information about the module
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

    // Turns the module into a valid C file
    void evaluate(ofstream& file){
      file << "#include <inttypes.h>" << std::endl;
      file << "#include <stdio.h>" << std::endl;
      file << "#include <string.h>" << std::endl;
      file << "#include <stdlib.h>" << std::endl;
      file << "\ntypedef struct nstring_st {\n";
      file << "  int32_t    len;\n";
      file << "  char       *str;\n";
      file << "} nstring;\n" << std::endl;

      int *curr_id = new int(0);
      int *tab_width = new int(0);
      std::map<string, string> *symbol_table = new std::map<string, string>();

      // Process all elements of the module
      for (size_t i = 0; i < func_decl_list.size(); i++) {
        func_decl_list[i]->evaluate(file, symbol_table);
      }
      for (size_t i = 0; i < var_decl_list.size(); i++) {
        var_decl_list[i]->evaluate(file, curr_id, tab_width, symbol_table);
      }
      for (size_t i = 0; i < func_def_list.size(); i++) {
        (func_def_list[i])->evaluate(file, curr_id, tab_width, symbol_table);
      }

      delete curr_id;
      delete tab_width;
      delete symbol_table;
    }

  private:
    vector<funcdecl_node *> func_decl_list;
    vector<vardecl_node *> var_decl_list;
    vector<funcdef_node *> func_def_list;
};
#endif // _MODULE_NODE_H
