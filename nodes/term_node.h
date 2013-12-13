// Jordan Heier
// Hunter Whalen

#ifndef _TERM_NODE_H
#define _TERM_NODE_H

#include <iostream>
#include <fstream>

#include "expr_node.h"

using std::ostream;
using std::ofstream;

// Parent class for term nodes, should never actually be used
class term_node : public expr_node{
  public:
    term_node() {
    }

    friend ostream& operator<<(ostream &os, const term_node &obj) {
      return (obj.printHelper(os));
    }

    // Method that will be overwriten by child nodes to turn into a 
    // C file
    virtual pair<string, string> *evaluate(ostream& file, int *curr_id, 
                                           int *tab_width, std::map<string, string> *symbol_table) {
      std::cout << "term_node evaluate called" << std::endl;
      return nullptr;
    }
    
  private:
    // Will be overwritten by children to print valid information about the
    // terms
    virtual ostream& printHelper(ostream &os) const{
      return os;
    }
};
#endif // _TERM_NODE_H
