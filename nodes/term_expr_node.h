// Jordan Heier
// Hunter Whalen

#ifndef _TERM_EXPR_H
#define _TERM_EXPR_H

#include <iostream>
#include <fstream>
#include <map>

#include "term_node.h"

using std::ostream;
using std::ofstream;

// This class stores a term expression
class term_expr_node : public term_node{
  public:
    term_expr_node(expr_node *v) {
      value = v;
    }

    // Turn the term into a valid C term
    pair<string, string> *evaluate(ofstream& file, int *curr_id, int *tab_width,
                                   std::map<string, string> *symbol_table) {
      pair<string, string> *paren_val = 
          value->evaluate(file, curr_id, tab_width, symbol_table);
      file << "(" << paren_val->first;    
      file << ")";

      string ID = paren_value->first
      string type = paren_val->second;
      delete paren_val;
      return new pair<string, string>(ID, type);
    }

  private:
    expr_node *value;

    // Print useful information about the term expression
    ostream& printHelper(ostream &os) const {
      os << "value=" << *value;
      return os;
    }
};
#endif // _TERM_EXPR_H
