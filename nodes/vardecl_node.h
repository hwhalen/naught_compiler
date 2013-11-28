#ifndef _VARDECL_NODE_H
#define _VARDECL_NODE_H

class vardecl_node {
  public:
    vardecl_node(string type, string ID, bool external) {
      external = external;
      type = type;
      ID = ID;
    }

  private:
    bool external;
    string type;
    string ID;

};
#endif // _VARDECL_NODE_H
