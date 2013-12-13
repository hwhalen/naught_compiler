// Jordan Heier
// Hunter Whalen

#ifndef _EXPR_SUB_NODE_H
#define _EXPR_SUB_NODE_H

#include <iostream>
#include <fstream>
#include <map>

#include "expr_node.h"

using std::ostream;
using std::ofstream;
using std::pair;

// This class represents an expression subtraction
class expr_sub_node : public expr_node {
  public:
    expr_sub_node(expr_node *left, expr_node *right) {
      this->left = left;
      this->right = right;
    }

    // Turn the subtraction into a valid C expression
    pair<string, string> *evaluate(ostream& file, int *curr_id, int *tab_width,
                                 std::map<string, string> *symbol_table) {
      pair<string, string> *left_temp = 
          left->evaluate(file, curr_id, tab_width, symbol_table);
      pair<string, string> *right_temp = 
          right->evaluate(file, curr_id, tab_width, symbol_table);

      // Type check
      if(left_temp->second != right_temp->second && 
         left_temp->second != "unknown" && right_temp->second != "unknown") {
        std::cerr << "ERROR: type mismatch" << std::endl;
        exit(1);
      }

      (*tab_width)++;
      insert_tabbing(file, *tab_width);
      file << "int32_t tempSub" << *curr_id<< " = ";
      file << left_temp->first << " - " << right_temp->first << ";\n";
      std::stringstream sstm;
      sstm << "tempSub" << *curr_id;
      string type = left_temp->second;
    
      delete left_temp;
      delete right_temp;
      return new pair<string, string>(sstm.str(), type);
    }

  private:
    expr_node *left;
    expr_node *right;
};
#endif // _EXPR_ADD_NODE_H
