#ifndef _TERM_UNARY_H
#define _TERM_UNARY_H

#include <iostream>
#include <fstream>

#include "term_node.h"

using std::ostream;
using std::ofstream;

enum Unary_Type {PRINT, ADDRESSOF, DEREFERENCE};

class term_unary_node : public term_node{
  public:
    term_unary_node(Unary_Type t, term_node *o) {
      type = t;
      other = o;
    }

    string evaluate(ofstream& file, int *curr_id, int *tab_width) {
      string temp = other->evaluate(file, curr_id, tab_width);
      switch (type) {
        case PRINT:
          for (int i = 0; i < *tab_width; i++) {
            file << "  ";
          }
          file << "printf(" << temp << ");\n";
          return temp;
        case ADDRESSOF:
          temp = "&" + temp;
          return temp;
        default: //DEREFERENCE
          temp = "*" + temp;
          return temp;
      }
    }

  private:
    Unary_Type type;
    term_node *other;

    ostream& printHelper(ostream &os) const {
      os << "type=" << type;
      os << " and other=" << *other;
      return os;
    }
};
#endif // _TERM_UNARY_H
