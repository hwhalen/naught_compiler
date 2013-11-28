#ifndef _FUNCDEF_NODE_H
#define _FUNCDEF_NODE_H

#include <string>
#include <iostream>
#include <vector>

#include "param_node.h"

using std::string;
using std::ostream;
using std::vector;

class funcdef_node {
  public:
    funcdef_node(string id) {
      ID = id;
    }
    
    funcdef_node(string id, vector<param_node> l) {
      ID = id;
      param_list = l;
      std::cout << "created new funcdef_node" << std::endl;
    }

    friend ostream& operator<<(ostream &os, const funcdef_node &obj) {
      return os;
    }

  private:
    string ID;
    vector<param_node> param_list;
};
#endif // _MODULE_NODE_H
