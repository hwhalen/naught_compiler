// Jordan Heier
// Hunter Whalen

#ifndef _EXPR_NODE_H
#define _EXPR_NODE_H

#include <iostream>
#include <fstream>
#include <typeinfo>

using std::ostream;
using std::ofstream;
using std::type_info;
using std::pair;

// Parent class of all expressions and terms, should never actually 
// be used
class expr_node {
  public:
    expr_node() {
    }
   
    virtual ~expr_node() {
    }

    friend ostream& operator<<(ostream&os, const expr_node &obj) {
      return obj.printHelper(os);
    }
    
    virtual pair<string, string> *evaluate(ofstream& file, int *curr_id, 
                              int *tab_width, std::map<string, string> *symbol_table) {

      std::cout << "expr_node evaluate is called with "; 
      std::cout << *tab_width << std::endl;
      return nullptr;
    }

  protected:
    void insert_tabbing(ofstream& file, int tab_width) {
      for (int i = 0; i < tab_width; i++) {
        file << "  ";
      }
    }

  private:
    virtual ostream& printHelper(ostream &os) const {
      return os;
    }
};

#endif // _EXPR_NODE_H
