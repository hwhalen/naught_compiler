#ifndef _TERM_FUNCTION_NODE_H
#define _TERM_FUNCTION_NODE_H

#include <iostream>
#include <string>

#include "term_node.h"

using std::ostream;

class term_function_node : public term_node {
  public:
    term_function_node(string &i, vector<expr_node *> &a) {
      ID = i;
      arguments = a;
    }

    string evaluate(ofstream& file, int *curr_id, int *tab_width) {
      string result = ID + "(";
      if (arguments.size() > 0) {
        for (size_t i = 0; i < arguments.size() - 1; i++) {
          string arg_temp = arguments[i]->evaluate(file, curr_id, tab_width);
          result += arg_temp + ", ";
        }
        result += arguments[arguments.size() - 1]->evaluate(file, curr_id, tab_width);
      }
      result += ")";
      return result;
    }

  private:
    string ID;
    vector<expr_node *> arguments;

    ostream& printHelper(ostream &os) const {
      os << "(ID=" << ID << " and arguments={";
      if (arguments.size() > 0) {
        for (size_t i = 0; i < arguments.size() - 1; i++) {
          os << *arguments[i] << ", ";
        }
        os << *arguments[arguments.size() - 1];
      }
      os << "})";
      return os;
    }
};

#endif // _TERM_FUNCTION_NODE_H 
