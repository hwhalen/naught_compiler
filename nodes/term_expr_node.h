#ifndef _TERM_EXPR_H
#define _TERM_EXPR_H

#include <iostream>
#include <fstream>
#include <map>

#include "term_node.h"

using std::ostream;
using std::ofstream;

class term_expr_node : public term_node{
  public:
    term_expr_node(expr_node *v) {
      value = v;
    }

    pair<string, string> *evaluate(ofstream& file, int *curr_id, int *tab_width, std::map<string, string> *symbol_table) {
      pair<string, string> *parenVal = value->evaluate(file, curr_id, tab_width, symbol_table);
      file << "(" << parenVal->first;    
      file << ")";
      return nullptr;
    }

  private:
    expr_node *value;

    ostream& printHelper(ostream &os) const {
      os << "value=" << *value;
      return os;
    }
};
#endif // _TERM_EXPR_H
