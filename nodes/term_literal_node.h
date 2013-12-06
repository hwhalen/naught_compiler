// Jordan Heier
// Hunter Whalen

#ifndef _TERM_LITERAL_H
#define _TERM_LITERAL_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

#include "term_node.h"

using std::ostream;
using std::ofstream;
using std::pair;

// This class represents a literal term (string or int)
template <typename T>
class term_literal_node : public term_node{
  public:
    term_literal_node(T v, string t) {
      value = v;
      type = t;
    }

    // Return the a pair of the value (since it is a literal) and the type
    pair<string, string> *evaluate(ofstream& file, int *curr_id, int *tab_width,
                                   std::map<string, string> *symbol_table) {
      std::string s;
      std::stringstream out;
      out << value;
      s = out.str();
      return new pair<string, string>(s, type);
    }

  private:
    T value;
    string type;

    // Print useful information about the literal
    ostream& printHelper(ostream &os) const {
      os << value;
      return os;
    }
};
#endif // _TERM_LITERAL_H
