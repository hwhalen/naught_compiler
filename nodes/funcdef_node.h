// Jordan Heier
// Hunter Whalen

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

// This class represents a function definition
class funcdef_node {
  public:
  // Construct a new funcdef node that stores its return type, parameters,
  // and the block that holds its content
    funcdef_node(const string &r, string &id, vector<param_node *> l,
                 block_node &b) : block(b){
      if (r == "pointer") {
        return_type = "int32_t *";
      } else if (r == "int") {
        return_type = "int32_t";
      } else if (r == "string") {
        return_type = "char *";
      }
      ID = id;
      param_list = l;
    }

  // Print useful information about the function
    friend ostream& operator<<(ostream &os, const funcdef_node &obj) {
      os << "return_type=" << obj.return_type;
      os << ", id=" << obj.ID;
      os << ", param_list={";
      for (size_t i = 0; i < obj.param_list.size(); i++) {
         os << obj.param_list[i] << " ";
      }
      os << "}, and block=(" << obj.block << ")";
      return os;
    }

    // Turn the function into a valid C funtion
    void evaluate(ofstream &file, int *curr_id, int *tab_width, 
                  std::map<string, string> *symbol_table) {

      file << return_type << " " << ID;
      file << "(";

      // Process parameters
      if (param_list.size() != 0) {
        for(size_t i = 0; i < param_list.size() - 1; i++) {
          (param_list[i])->evaluate(file);
          file << ", ";
        }
        (param_list[param_list.size() - 1])->evaluate(file);
      }

      file << ")";

      // Process the block
      block.evaluate(file, curr_id, tab_width, symbol_table);
      file << std::endl;
    }

  private:
    string return_type;
    string ID;
    vector<param_node *> param_list;
    block_node block;
};
#endif // _FUNCDEF_NODE_H
