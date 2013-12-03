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

    void evaluate(ofstream& file) {
      switch(type){
        case PRINT:       file << "print "; break;
        case ADDRESSOF:   file << "&"; break;
        case DEREFERENCE: file << "*"; break;
      }
      other->evaluate(file);
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
