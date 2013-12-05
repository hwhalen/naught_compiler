#ifndef _EXPR_MULT_NODE_H
#define _EXPR_MULT_NODE_H

#include <iostream>
#include <fstream>
#include <map>

#include "expr_node.h"

using std::ostream;

class expr_mult_node : public expr_node {
  public:
    expr_mult_node(expr_node *left, expr_node *right) {
      this->left = left;
      this->right = right;
    }
  
    ~expr_mult_node() {
      delete left;
      delete right;
    }

    pair<string, string> *evaluate(ofstream &file, int *curr_id, int *tab_width, std::map<string, string> *symbol_table) {
      pair<string, string> *leftTemp = left->evaluate(file, curr_id, tab_width, symbol_table);
      pair<string, string> * rightTemp = right->evaluate(file, curr_id, tab_width, symbol_table);
      for (int i = 0; i < *tab_width; i++) {
        file << "  ";
      }
      (*curr_id)++;
      file << "int32_t tempMult" << *curr_id << " = " << leftTemp->first << " * " << rightTemp->first << ";\n";  
      std::stringstream sstm;
      sstm << "tempMult" << *curr_id;
      string type = leftTemp->second;
      delete leftTemp;
      return new pair<string, string>(sstm.str(), type);
    }

  private:
    expr_node *left;
    expr_node *right;
    int result;

    virtual ostream& printHelper(ostream &os) const {
      os << "left=" << *left;
      os << " mult right=" << *right;
      return os;
    }
};
#endif // _EXPR_MULT_NODE_H
