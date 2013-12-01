#ifndef _INT_LITERAL_H
#define _INT_LITERAL_H

#include <iostream>
#include <fstream>

#include "term_node.h"

using std::ostream;
using std::ofstream;

class int_literal_node : public term_node{
  public:
    int_literal_node(int v) {
      value = v;
    }

    void evaluate(ofstream& file) {
      file << value << std::endl;
    }

  private:
    int value;
    ostream& printHelper(ostream &os) const {
      os << value;
      return os;
    }
};
#endif // _INT_LITERAL_H
