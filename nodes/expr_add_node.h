#ifndef _EXPR_ADD_NODE_H
#define _EXPR_ADD_NODE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

#include "expr_node.h"

using std::ostream;
using std::ofstream;
using std::endl;
using std::stringstream;
using std::pair;

class expr_add_node : public expr_node {
  public:
    expr_add_node(expr_node *l, expr_node *r) {
      left = l;
      right = r;
    }
  
    pair<string, string> *evaluate(ofstream& file, int *curr_id, int *tab_width, std::map<string, string> *symbol_table) {
      pair<string, string> *leftTemp = left->evaluate(file, curr_id, tab_width, symbol_table);
      pair<string, string> *rightTemp = right->evaluate(file, curr_id, tab_width, symbol_table);

      (*curr_id)++;
      if(leftTemp->second == "char *") {
        // Initializes a new nstring, sets its len field and 
        // mallocs space for its string.
        insert_tabbing(file, *tab_width);
        file << "nstring tempAdd" << *curr_id << "nString;\n";
        insert_tabbing(file, *tab_width);
        file << "tempAdd" << *curr_id << "nString.len = ";
        file << "strlen(" << leftTemp->first << ") + strlen(" << rightTemp->first;
        file << ");\n";
        insert_tabbing(file, *tab_width);
        file << "tempAdd" << *curr_id;
        file << "nString.str = (char *) malloc(tempAdd" << *curr_id << "nString";
        file << ".len + 1);\n";
        insert_tabbing(file, *tab_width);
        file << "strcpy(tempAdd" << *curr_id << "nString.str, "; 
        file << leftTemp->first << ");\n";
        insert_tabbing(file, *tab_width);
        file << "strcpy(tempAdd" << *curr_id << "nString.str + strlen(";
        file << leftTemp->first << "), " << rightTemp->first << ");\n";
        insert_tabbing(file, *tab_width);
        file << "char * tempAdd" << *curr_id << " = ";
        file << "tempAdd" << *curr_id << "nString.str;\n";
      } else {
        insert_tabbing(file, *tab_width);
        file << "int32_t tempAdd" << *curr_id << " = ";
        file << leftTemp->first << " + " << rightTemp->first << ";\n";
      }
      std::stringstream sstm;
      sstm << "tempAdd" << *curr_id;
      pair<string, string> *return_val = new pair<string, string>(sstm.str(), leftTemp->second);
      return return_val;
    }

  private:
    expr_node *left;
    expr_node *right;

    virtual ostream& printHelper(ostream &os) const {
      os << "left=" << *left;
      os << " plus right=" << *right;
      return os;
    }
};
#endif // _EXPR_ADD_NODE_H
