#ifndef _EXPR_ADD_NODE_H
#define _EXPR_ADD_NODE_H

#include <iostream>
#include <fstream>
#include <sstream>

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
  
    pair<string, string> *evaluate(ofstream& file, int *curr_id, int *tab_width) {
      pair<string, string> *leftTemp = left->evaluate(file, curr_id, tab_width);
      pair<string, string> *rightTemp = right->evaluate(file, curr_id, tab_width);
      
      for (int i = 0; i < *tab_width; i++) {
        file << "  ";
      }
      (*curr_id)++;
      
      if(leftTemp->second == "nstring") {
        // Initializes a new nstring, sets its len field and 
	// mallocs space for its string.
        file << "nstring tempAdd" << *curr_id << ";\n";
        file << "tempAdd" << *curr_id << ".len = ";
        file << leftTemp->first << ".len" << " + " << rightTemp->first << ".len;\n";
        file << "tempAdd" << *curr_id << ".str = (char *) malloc(tempAdd" << *curr_id;
        file << ".len);\n";
      } else {
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
