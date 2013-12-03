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

    void evaluate(ofstream& file) {
      file << ID << "(";
      if (arguments.size() > 0) {
        for (size_t i = 0; i < arguments.size() - 1; i++) {
          arguments[i]->evaluate(file);
          file << ", ";
        }
        arguments[arguments.size() - 1]->evaluate(file);
      }
      file << ")";
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
