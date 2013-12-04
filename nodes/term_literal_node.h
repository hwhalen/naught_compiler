#ifndef _TERM_LITERAL_H
#define _TERM_LITERAL_H

#include <iostream>
#include <fstream>
#include <sstream>

#include "term_node.h"

using std::ostream;
using std::ofstream;

template <typename T>
class term_literal_node : public term_node{
  public:
    term_literal_node(T v) {
      value = v;
    }

    string evaluate(ofstream& file, int *curr_id, bool print) {
      if(print) file << "  " << value;
      std::string s;
      std::stringstream out;
      out << value;
      s = out.str();
      return s;
    }

  private:
    T value;
    ostream& printHelper(ostream &os) const {
      os << value;
      return os;
    }
};
#endif // _TERM_LITERAL_H
