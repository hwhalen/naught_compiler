#ifndef _LITERAL_H
#define _LITERAL_H

#include <iostream>
#include <fstream>

#include "term_node.h"

using std::ostream;
using std::ofstream;

template <typename T>
class literal_node : public term_node{
  public:
    literal_node(T v) {
      value = v;
    }

    void evaluate(ofstream& file) {
      file << value << std::endl;
    }

  private:
    T value;
    ostream& printHelper(ostream &os) const {
      os << value;
      return os;
    }
};
#endif // _LITERAL_H
