// Jordan Heier
// Hunter Whalen

#ifndef _EXPR_MULT_NODE_H
#define _EXPR_MULT_NODE_H

#include <iostream>
#include <fstream>
#include <map>

#include "expr_node.h"

using std::ostream;

// This class represents a multiplication expression
class expr_mult_node : public expr_node {
  public:
    expr_mult_node(expr_node *left, expr_node *right) {
      this->left = left;
      this->right = right;
    }

    // Turns the multiplication expression into a valid C expression
    pair<string, string> *evaluate(ofstream &file, int *curr_id, int *tab_width,
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

      // Indent
      for (int i = 0; i < *tab_width; i++) {
        file << "  ";
      }

      (*curr_id)++;
      file << "int32_t tempMult" << *curr_id << " = " << temp_left->first;
      file << " * " << temp_right->first << ";\n";  
      std::stringstream sstm;
      sstm << "tempMult" << *curr_id;
      string type = temp_left->second;

      delete temp_left;
      delete temp_left;
      return new pair<string, string>(sstm.str(), type);
    }

  private:
    expr_node *left;
    expr_node *right;
    int result;

    // Print useful info on the multiplication
    virtual ostream& printHelper(ostream &os) const {
      os << "left=" << *left;
      os << " mult right=" << *right;
      return os;
    }
};
#endif // _EXPR_MULT_NODE_H
