// Jordan Heier
// Hunter Whalen

#ifndef _TERM_UNARY_H
#define _TERM_UNARY_H

#include <iostream>
#include <fstream>
#include <map>

#include "term_node.h"

using std::ostream;
using std::ofstream;

enum Unary_Type {PRINT, ADDRESSOF, DEREFERENCE};

// This class represents a unary expression on a term
class term_unary_node : public term_node{
  public: 
  // Contstructs a unary node that stores the type of unary expression and
  // the term it is applied to
    term_unary_node(Unary_Type t, term_node *o) {
      type = t;
      other = o;
    }

    // Turns the unary expression into a C unary expression
    pair<string, string> *evaluate(ofstream& file, int *curr_id, int *tab_width,
                                   std::map<string, string> *symbol_table) {
      pair<string, string> *temp = 
          other->evaluate(file, curr_id, tab_width, symbol_table);

      string type = temp->second;
      string ID = temp->first;
      delete temp;
      // Pick type of unary operator and format to C
      switch (type) {
        case PRINT:
          for (int i = 0; i < *tab_width; i++) {
            file << "  ";
          }
          if (type == "string") {
            file << "printf(\"%p\\n\", (void*) " << ID << ");\n";
          } else if (type == "pointer") {
            file << "printf(" << ID << ".str);\n";
          } else { // type is int
            file << "printf(\"%\" PRIu32 \"\\n\", " << ID << ");\n";
          }
          return new pair<string, string>(ID, type);
        case ADDRESSOF:
          ID = "&" + ID;
          return new pair<string, string>(ID, type);
        default: //DEREFERENCE
          ID = "*" + ID;
          return new pair<string, string>(ID, type);
      }
    }

  private:
    Unary_Type type;
    term_node *other;

    // Print useful info on the unary expression
    ostream& printHelper(ostream &os) const {
      os << "type=" << type;
      os << " and other=" << *other;
      return os;
    }
};
#endif // _TERM_UNARY_H
