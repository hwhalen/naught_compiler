#ifndef _BLOCK_NODE_H
#define _BLOCK_NODE_H

#include <iostream>
#include <vector>
#include <fstream>

#include "vardecl_node.h"
#include "stmt_node.h"

using std::ostream;
using std::vector;

class block_node {
  public:
    block_node(vector<vardecl_node *> v, vector<stmt_node *> s) {
      var_decs = v;
      stmts = s;
    }

    void evaluate(std::ofstream &file) {
      file << "{";
      for (size_t i = 0; i < var_decs.size(); i++) {
        (var_decs[i])->evaluate(file);
      }
      for (size_t i = 0; i < stmts.size(); i++) {
        (stmts[i])->evaluate(file);
      }
      file << "}";
    }

    friend ostream& operator<<(ostream &os, const block_node &obj) {
      return (obj.printHelper(os));
    }

  private:
    vector<vardecl_node *> var_decs;
    vector<stmt_node *> stmts;

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
