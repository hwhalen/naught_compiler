// Jordan Heier
// Hunter Whalen

#ifndef _BLOCK_NODE_H
#define _BLOCK_NODE_H

#include <iostream>
#include <vector>
#include <fstream>

#include "vardecl_node.h"
#include "stmt_node.h"

using std::ostream;
using std::vector;

// This class represents a whole block of code
class block_node {
  public:
  // Construct new block_node with variable declarations and statements
    block_node(vector<vardecl_node *> v, vector<stmt_node *> s) {
      var_decs = v;
      stmts = s;
    }

    friend ostream& operator<<(ostream &os, const block_node &obj) {
      return (obj.printHelper(os));
    }

    // Turns the block into valid C code
    void evaluate(ofstream &file, int *curr_id, int *tab_width,
                  std::map<string, string> *symbol_table) {
      file << " {\n";
      // Have the variable declarations turn themselves into C code
      for(size_t i = 0; i < var_decs.size(); i++) {
        var_decs[i]->evaluate(file, curr_id, tab_width, symbol_table);
      }
      // Have the statments turn themselves into C code
      for(size_t i = 0; i < stmts.size(); i++) {
        stmts[i]->evaluate(file, curr_id, tab_width, symbol_table);
      }
      file << "}";
    }

  private:
    vector<vardecl_node *> var_decs;
    vector<stmt_node *> stmts;

    // Print useful information about the block
    virtual ostream& printHelper(ostream &os) const {
      os << "var_decs={";
      for (size_t i = 0; i < var_decs.size(); i++) {
        os << *(var_decs[i]);
      }
      os << "} and stmts={";
      for (size_t i = 0; i < stmts.size(); i++) {
        os << *(stmts[i]);
      }
      os << "}";
      return os;
    }
};
#endif // _BLOCK_NODE_H
