#ifndef _MODULE_NODE_H
#define _MODULE_NODE_H

#include <vector>
#include <string>
#include <iostream>

#include "funcdef_node.h"

using std::ostream;
using std::vector;
using std::string;
using std::ofstream;

class module_node {
  public:
    module_node() {
      std::cout << "created empty module_node" << std::endl;
    }

    module_node(vector<funcdef_node> l) {
      function_def_node_list = l;
    }

    friend ostream& operator<<(ostream &os, const module_node &obj) {
      os << "function_def_list={";
      for (size_t i = 0; i < obj.function_def_node_list.size(); i++) {
        os << "(" << obj.function_def_node_list[i] << ")";
      }
      os << "}";
      return os;
    }

    void evaluate(ofstream& file){
      for(size_t i = 0; i < function_def_node_list.size(); i++) {
        function_def_node_list[i].evaluate(file);
      }
    }

  private:
    vector<funcdef_node> function_def_node_list;
};
#endif // _MODULE_NODE_H
