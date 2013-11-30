#ifndef _FUNCDECL_NODE_H
#define _FUNCDECL_NODE_H

#include <string>
#include <iostream>
#include <vector>

#include "param_node.h"

using std::string;
using std::ostream;
using std::vector;

class funcdecl_node {
  public:
    funcdecl_node(string id, vector<param_node> l){
      ID = id;
      param_list = l;
    }

    friend ostream& operator<<(ostream &os, const funcdecl_node &obj) {
      os << "id=" << obj.ID;
      os << ", param_list={";
      for (size_t i = 0; i < obj.param_list.size(); i++) {
        os << obj.param_list[i];
      }
      return os;
    }

  private:
    string ID;
    vector<param_node> param_list;
};
#endif // _FUNCDECL_NODE_H
