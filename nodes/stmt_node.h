// Jordan Heier
// Hunter Whalen

#ifndef _STMT_NODE_H
#define _STMT_NODE_H

#include <iostream>
#include <fstream>
#include <map>

#include "expr_node.h"

using std::ostream;
using std::ofstream;
using std::pair;

// This class represents a single statement
class stmt_node {
  public:
  // Construct a new statement node that stores its expression and whether or
  // not it is a return statement
    stmt_node(expr_node *expr, bool r) {
      this->expr = expr;
      should_return = r;
    }

    // Turn the statement into a valid C statement and place in file
    void evaluate(ofstream &file, int *curr_id, int *tab_width, 
                  std::map<string, string> *symbol_table) {
      pair<string, string> *expr_temp = 
        expr->evaluate(file, curr_id, tab_width, symbol_table);

      // Indent line
      for (int i = 0; i < *tab_width; i++) {
        file << "  ";
      }

      if (should_return) file << "return ";
      file << expr_temp->first << ";" << std::endl;
      delete expr_temp;
    }

    // Print useful information about the statement
    friend ostream& operator<<(ostream &os, const stmt_node &obj) {
      os << *obj.expr;
      os << ";";
      return os;
    }

  private:
    bool should_return;
    expr_node *expr;

    // Print useful info about the statement
    virtual ostream& printHelper(ostream &os) const {
      return os;
    }
}; 

#endif // _STMT_NODE_H
