// Jordan Heier
// Hunter Whalen

#ifndef _EXPR_DIV_NODE_H
#define _EXPR_DIV_NODE_H

#include <iostream>
#include <fstream>
#include <map>

#include "expr_node.h"

using std::ostream;
using std::ofstream;

// This class represents a division expression
class expr_div_node : public expr_node {
  public:

  // Construct new expr_div_node, where left is the top, and right is the
  // bottom of the division expression
  expr_div_node(expr_node *left, expr_node *right) {
      this->left = left;
      this->right = right;
  }
 
  // Turn the division expression into a valid C statement. Return a pair
  // where the first element stores the temp variable name and the second
  // element stores the type
  pair<string, string> *evaluate(ofstream file, int *curr_id, int *tab_width, 
                                 std::map<string, string> *symbol_table) {
    pair<string, string> *leftVal =
        left->evaluate(file, curr_id, tab_width, symbol_table);
    pair<string, string> * rightVal = 
        right->evaluate(file, curr_id, tab_width, symbol_table);

    // Type check
    if(leftVal->second != rightVal->second && 
         leftVal->second != "unknown" && rightVal->second != "unknown") {
      std::cerr << "ERROR: type mismatch" << std::endl;
      exit(1);
    }

    (*curr_id)++;
    file << "int32_t tempDiv" << *curr_id << " = ";
    file << leftVal->first << " / " << rightVal->first << ";\n";
    std::stringstream sstm;
    sstm << "tempDiv" << *curr_id;
    string type = leftVal->second;
    delete leftVal;
    delete rightVal;

    return new pair<string, string>(sstm.str(), type);
  }

  private:
    expr_node *left;
    expr_node *right;
    int result;
};
#endif // _EXPR_DIV_NODE_H
