// Jordan Heier
// Hunter Whalen

#ifndef _EXPR_ASSIGN_NODE_H
#define _EXPR_ASSIGN_NODE_H

#include <iostream>
#include <fstream>

#include "expr_node.h"
#include "term_node.h"

using std::ostream;
using std::ofstream;

// This class represents an expression assignment
class expr_assign_node : public expr_node {
  public:
  // Construct a new expr_assign_node with a left term and right expression
    expr_assign_node(term_node *left, expr_node *right) {
      this->left = left;
      this->right = right;
    }  

    // Turn the expr assignment into a C file. Returns a pair with the 
    // ID and the type.
    pair<string, string> *evaluate(ofstream& file, int *curr_id, int *tab_width,
                                   std::map<string, string> *symbol_table) {
      pair<string, string> *temp_left = 
          left->evaluate(file, curr_id, tab_width, symbol_table);
      pair<string, string> *temp_right = 
          right->evaluate(file, curr_id, tab_width, symbol_table);

      // Type check
      if(temp_left->second != temp_right->second) {
        std::cerr << "ERROR: type mismatch" << std::endl;
        exit(1);
      }

      // Indent proper amount
      for (int i = 0; i < *tab_width; i++) {
        file << "  ";
      }

      // Format as C
      file << temp_left->first << " = ";
      file << temp_right->first << ";\n";

      string id = temp_left->first;
      string type = temp_left->second;
      delete temp_left;
      delete temp_right;
      return new pair<string, string>(id, type);
    }

  private:
    term_node *left;
    expr_node *right;

    // Print useful info on the expression assignment
    virtual ostream& printHelper(ostream &os) const {
      os << "left=" << *left;
      os << " assigned right=" << *right;
      return os;
    }
};
#endif // _EXPR_ASSIGN_NODE_H
