#ifndef _TERM_FUNCTION_NODE_H
#define _TERM_FUNCTION_NODE_H

#include <iostream>
#include <string>
#include <map>

#include "term_node.h"

using std::ostream;

class term_function_node : public term_node {
  public:
    term_function_node(string &i, vector<expr_node *> &a) {
      ID = i;
      arguments = a;
    }

    pair<string, string> *evaluate(ofstream& file, int *curr_id, int *tab_width, std::map<string, string> *symbol_table) {
      string result = ID + "(";
      if (arguments.size() > 0) {
        for (size_t i = 0; i < arguments.size() - 1; i++) {
          string arg_temp = arguments[i]->evaluate(file, curr_id, tab_width, symbol_table)->first;
          result += arg_temp + ", ";
        }
        pair<string, string> *arg_temp = arguments[arguments.size() - 1]->evaluate(file, curr_id, tab_width, symbol_table);
        result += arg_temp->first;
      }
      result += ")";
      std::map<string, string>::iterator it;
      it = symbol_table->find(ID);
      if (it != symbol_table->end()) {
        return new pair<string, string>(result, it->second);
      } else {
        return new pair<string, string>(result, "unknown");
      }
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
