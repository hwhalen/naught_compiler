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
         os << obj.param_list[i] << " ";
      }
      os << "}, and block=(" << obj.block << ")";
      return os;
    }

    void evaluate(ofstream &file) {
      file << "int " << ID;
      file << "(";
      if (param_list.size() != 0) {
        for(size_t i = 0; i < param_list.size() - 1; i++) {
          param_list[i].evaluate(file);
          file << ", ";
        }
        param_list[param_list.size() - 1].evaluate(file);
      }
      file << ") ";
      block.evaluate(file); 
    }

  private:
    string ID;
    vector<param_node> param_list;
    block_node block;
};
#endif // _FUNCDEF_NODE_H
