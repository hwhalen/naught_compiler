// Jordan Heier
// Hunter Whalen

#ifndef _FUNCDECL_NODE_H
#define _FUNCDECL_NODE_H

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <map>

#include "param_node.h"

using std::string;
using std::ostream;
using std::vector;

// This class represents a function declaration
class funcdecl_node {
  public:
    funcdecl_node(string r, string id, vector<param_node *> l){
      if (r == "pointer") {
        return_type = "int32*";
      } else if (r == "string") {
        return_type = "char *";
      } else {
        return_type = "int32_t";
      }
      ID = id;
      param_list = l;
    }

    // Turn the function declaration into a valid C funtion declaration
    void evaluate(std::ofstream &file, std::map<string, string> *symbol_table) {
      (*symbol_table)[ID] = return_type;
      file << return_type << " ";
      file << ID << " (";
      if (param_list.size() > 0) {
        for (size_t i = 0; i < param_list.size() - 1; i++) {
          (param_list[i])->evaluate(file);
          file << ", ";
        }
        (param_list[param_list.size() - 1])->evaluate(file);
      }
      file << ");" << std::endl;
    }

    // Print useful information about the function declaration
    friend ostream& operator<<(ostream &os, const funcdecl_node &obj) {
      os << "return_type=" << obj.return_type;
      os << ", id=" << obj.ID;
      os << ", param_list={";
      for (size_t i = 0; i < obj.param_list.size(); i++) {
        os << obj.param_list[i];
      }
      return os;
    }

  private:
    string return_type;
    string ID;
    vector<param_node *> param_list;
};
#endif // _FUNCDECL_NODE_H
