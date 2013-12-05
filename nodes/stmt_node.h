#ifndef _STMT_NODE_H
#define _STMT_NODE_H

#include <iostream>
#include <fstream>
#include <map>

#include "expr_node.h"

using std::ostream;
using std::ofstream;
using std::pair;

class stmt_node {
  public:
    stmt_node(expr_node *expr, bool r) {
      this->expr = expr;
      should_return = r;
    }

    void evaluate(ofstream &file, int *curr_id, int *tab_width, std::map<string, string> *symbol_table) {
      pair<string, string> *expr_temp = expr->evaluate(file, curr_id, tab_width, symbol_table);
      for (int i = 0; i < *tab_width; i++) {
        file << "  ";
      }
      if (should_return) {
        file << "return ";
      }
      file << expr_temp->first << ";" << std::endl;
    }

    friend ostream& operator<<(ostream &os, const stmt_node &obj) {
      os << *obj.expr;
      os << ";";
      return os;
    }

  private:
    bool should_return;
    expr_node *expr;
    virtual ostream& printHelper(ostream &os) const {
      return os;
    }
}; 

#endif // _STMT_NODE_H
