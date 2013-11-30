#ifndef _FUNCDEF_NODE_H
#define _FUNCDEF_NODE_H

#include <string>
#include <iostream>
#include <vector>

#include "param_node.h"
#include "block_node.h"

using std::string;
using std::ostream;
using std::vector;

class funcdef_node {
  public:
    funcdef_node(string id, vector<param_node> l, block_node b) : block(b){
      ID = id;
      param_list = l;
    }

    friend ostream& operator<<(ostream &os, const funcdef_node &obj) {
      os << "id=" << obj.ID;
      os << ", param_list={";
      for (size_t i = 0; i < obj.param_list.size(); i++) {
        os << obj.param_list[i];
      }
      os << "}, and block=(" << obj.block << ")";
      return os;
    }

  private:
    string ID;
    vector<param_node> param_list;
    block_node block;
};
#endif // _MODULE_NODE_H
