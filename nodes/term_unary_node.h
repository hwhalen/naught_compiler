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

    pair<string, string> *evaluate(ofstream& file, int *curr_id, int *tab_width) {
      pair<string, string> *temp = other->evaluate(file, curr_id, tab_width);
      switch (type) {
        case PRINT:
          for (int i = 0; i < *tab_width; i++) {
            file << "  ";
          }
          if (temp->second == "string") {
            file << "printf(\"%p\\n\", (void*) " << temp->first << ");\n";
          } else if (temp->second == "pointer") {
            file << "printf(" << temp->first << ".str);\n";
          } else { // type is int
            file << "printf(\"%\" PRIu32 \"\\n\", " << temp->first << ");\n";
          }
          return new pair<string, string>(temp->first, temp->second);
        case ADDRESSOF:
          temp->first = "&" + temp->first;
          return new pair<string, string>(temp->first, temp->second);
        default: //DEREFERENCE
          temp->first = "*" + temp->first;
          return new pair<string, string>(temp->first, temp->second);
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
