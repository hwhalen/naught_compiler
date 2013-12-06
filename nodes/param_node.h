// Jordan Heier
// Hunter Whalen

#ifndef _PARAM_NODE_H
#define _PARAM_NODE_H

#include <string>
#include <iostream>
#include <vector>
#include <fstream>

using std::string;
using std::ostream;
using std::vector;
using std::ofstream;

// This class represents one parameter
class param_node {
  public:
  // Construct a param node that stores its type and ID
    param_node(string t, string i) {
      if (t == "pointer") {
        type = "int32_t *";
      } else if (t == "string") {
        type = "char *";
      } else {
        type = "int32_t";
      }
      ID = i;
    }

    // Print useful info about the parameter
    friend ostream& operator<<(ostream &os, const param_node &obj) {
      return (obj.printHelper(os));
    }

    // Turn the parameter into C notation
    void evaluate(ofstream &file) {
      file << type << " " << ID;
    }

  private:
    string type;
    string ID;

    // Print useful info about the parameter
    virtual ostream& printHelper(ostream &os) const {
      os << type;
      os << " " << ID;
      return os;
    }
};
#endif // _PARAM_NODE_H

