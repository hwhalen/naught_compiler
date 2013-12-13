// Jordan Heier
// Hunter Whalen

#ifndef _EXPR_TERNARY_NODE_H
#define _EXPR_TERNARY_NODE_H

#include <iostream>
#include <fstream>
#include <map>

#include "expr_node.h"

using std::ostream;

// This class represents a ternary expression
class expr_ternary_node : public expr_node {
  public:
    expr_ternary_node(expr_node *t, expr_node *ot, expr_node *of) {
      test = t;
      on_true = ot;
      on_false = of;
    }

    // Turn the ternary expression into a valid C expression
    pair<string, string> *evaluate(ostream& file, int *curr_id, int *tab_width,
                                   std::map<string, string> *symbol_table) {
      pair<string, string> *ifVal = 
          test->evaluate(file, curr_id, tab_width, symbol_table);
      // pass in dummy ofstream in order to get the type of return value
      std::stringstream then_stream;
      std::stringstream else_stream;
      (*tab_width)++;
      pair<string, string> *thenVal =  
          on_true->evaluate(then_stream, curr_id, tab_width, symbol_table);
      pair<string, string> *elseVal = 
          on_false->evaluate(else_stream, curr_id, tab_width, symbol_table);
      (*tab_width)--;
  
      (*curr_id)++;
      insert_tabbing(file, *tab_width);
      file << thenVal->second << " ternaryTemp" << *curr_id << ";" << endl;      
      insert_tabbing(file, *tab_width);
      file << "if (" << ifVal->first << ") {" << endl;
      file << then_stream.str();
      insert_tabbing(file, *tab_width + 1);
      file << "ternaryTemp" << *curr_id << " = " << thenVal->first << ";" << endl;
      insert_tabbing(file, *tab_width);
      file << "} else {" << endl;
      file << else_stream.str();
      insert_tabbing(file, *tab_width + 1);
      file << "ternaryTemp" << *curr_id << " = " << elseVal->first << ";" << endl;
      insert_tabbing(file, *tab_width);
      file << "}" << endl;
      std::stringstream return_sstm;
      return_sstm << "ternaryTemp" << *curr_id;
      return new pair<string, string>(return_sstm.str(), thenVal->second);
    }

  private:
    expr_node *test;
    expr_node *on_true;
    expr_node *on_false;

    // Print useful information on the ternary
    virtual ostream& printHelper(ostream &os) const {
      os << "test=" << *test;
      os << ", on_true=" << *on_true;
      os << " and on_false=" << *on_false;
      return os;
    }
};
#endif // _EXPR_TERNARY_NODE_H
