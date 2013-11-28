#ifndef _MODULE_NODE_H
#define _MODULE_NODE_H

#include <vector>
#include <string>
#include <iostream>

#include "funcdef_node.h"

using std::ostream;
using std::vector;
using std::string;

class module_node {
  public:
    module_node() {
      std::cout << "created new module_node" << std::endl;
    }

    module_node(vector<funcdef_node> l) {
      function_def_node_list = l;
      std::cout << "created new module_node with funcdef list" << std::endl;
    }

    friend ostream& operator<<(ostream &os, const module_node &obj) {
      return os;
    }

  private:
    vector<funcdef_node> function_def_node_list;
};
#endif // _MODULE_NODE_H
