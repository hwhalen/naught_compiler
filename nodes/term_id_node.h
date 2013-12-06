// Jordan Heier
// Hunter Whalen

#ifndef _TERM_ID_NODE_H
#define _TERM_ID_NODE_H

#include <iostream>
#include <string>
#include <map>

#include "term_node.h"

using std::ostream;

// This class represents the ID of a variable
class term_id_node : public term_node {
  public:
    term_id_node(string id) {
      ID = id;
    }

    // Find the type of the ID and return a pair where the ID is the first
    // element and the type is the second element
    pair<string, string> *evaluate(ofstream& file, int *curr_id, int *tab_width,
                                   std::map<string, string> *symbol_table) {
      std::map<string, string>::iterator it;
      it = symbol_table->find(ID);
      if (it != symbol_table->end()) {
        return new pair<string, string>(ID, it->second);
      } else {
        return new pair<string, string>(ID, "unknown");
      }
    }

  private:
    string ID;
    
    ostream& printHelper(ostream &os) const {
      os << "ID=" << ID;
      return os;
    }
};

#endif // _TERM_ID_NODE_H
