#ifndef _TERM_ID_NODE_H
#define _TERM_ID_NODE_H

#include <iostream>
#include <string>

#include "term_node.h"

using std::ostream;

class term_id_node : public term_node {
  public:
    term_id_node(string id) {
      ID = id;
    }

    pair<string, string> *evaluate(ofstream& file, int *curr_id, int *tab_width) {
      return new pair<string, string>(ID, "unknown");;
    }

  private:
    string ID;
    
    ostream& printHelper(ostream &os) const {
      os << "ID=" << ID;
      return os;
    }
};

#endif // _TERM_ID_NODE_H
