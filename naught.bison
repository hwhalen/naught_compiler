%{
#define YY_NO_UNPUT

#include <iostream>
#include <string>
#include <memory>
#include <cstring>

#include "yy.h"
#include "StrUtil.h"
#include "module_node.h"
#include "int_literal_node.h"
#include "param_node.h"
#include "expr_node.h"


using namespace std;

extern int _WANT_DEBUG;

extern module_node *AST;


%}

/***************************************
 * These are the union of the data types
 * that are associated with AST nodes.
 * They should all be pointers.
 * The C++ type is the first entry.
 * The second entry is a symbolic
 * name used later in this file.
 ***************************************/
%union {
  StrUtil*              string_val;
  module_node*          module;
  term_node*            term;
  string*               int_literal;
  vector<funcdef_node>* func_def_vec;
  funcdef_node*         func_def;
  string*               id;
  vector<param_node>*   param_vec;
  param_node*           param;
  string*               type;
  expr_node*            expr;
}

/***********************************************************************
 * The order of these next few lines sets operator precedence, which is
 * important to correct operation of the parser.  Don't change them.
 ***********************************************************************/
%right <string_val> ASSIGN
%right <string_val> COLON QUESTION
%left <string_val> ADD SUB
%left <string_val> STAR DIV
%right <string_val> UNARY_OP
/*********************************************************
 * Okay, that's it -- after this order doesn't matter
 *********************************************************/

/**********************************************************
 * Here (and in the precedence/associativity declarations 
 * above, we're defining symbols that can be returned by
 * the lexer. 
 **********************************************************/

%token <string_val> LCBRACE RCBRACE RPAREN LPAREN SEMI COMMA EXTERN FUNCTION SFUNCTION RETURN

%token <type> TYPE
%token <string_val> STRING_LITERAL
%token <int_literal> INT_LITERAL
%token <id> ID

/**********************************************************
 * Now we're defining the type associated with nodes
 * corresponding to non-terminals.
 **********************************************************/

%type <module> module
%type <func_def> funcdef
%type <string_val> block
%type <string_val> vardecl
%type <string_val> funcdecl
%type <expr> expr
%type <term> term
%type <string_val> stmt

%type <string_val> stmt_list
%type <string_val> vardecl_list
%type <string_val> funcdecl_list
%type <param> param;
%type <param_vec> param_list;
%type <func_def_vec> funcdef_list
%type <string_val> arglist;

/*********************************************
 * This is the terminal symbol.  The entire
 * naught program should be reducable to this
 * symbol.
 *********************************************/
%start module

%%

/********************************************************
 * It will take a bit of study, but these rules are
 * the easiest to understand explanation of the grammar.
 ********************************************************/

module :
         funcdecl_list vardecl_list funcdef_list
          { AST = new module_node(); //new StrUtil(*$1 + *$2 + *$3);
            $$ = AST;
            cout << *$$ << "funcecllist vardeclist funcdeflist -> module " << endl;
          }
        |              vardecl_list funcdef_list
          { AST = new module_node(); //StrUtil(*$1 + *$2);
            $$ = AST;
            cout << *$$ << "vardecllist funcdeflist -> module " << endl;
          }
        | funcdecl_list             funcdef_list
          { AST = new module_node(); //StrUtil(*$1 + *$2);
            $$ = AST;
            cout << *$$ << "funcdecllist and funcdeflist -> module " << endl;
          }
        |                            funcdef_list
          { AST = new module_node(*$1); //new StrUtil(*$1);
            $$ = AST;
            cout << *$$ << "funcdeflist -> module " << endl;
          }
        | funcdecl_list vardecl_list
          { AST = new module_node(); //StrUtil(*$1 + *$2);
            $$ = AST;
            cout << *$$ << "funcdecllist vardecllist -> module " << endl;
          }
        |              vardecl_list
          { AST = new module_node(); //StrUtil(*$1);
            $$ = AST;
            cout << *$$ << "vardecllist -> module " << endl;
          }
        | funcdecl_list             
          { AST = new module_node(); //StrUtil(*$1);
            $$ = AST;
            cout << *$$ << "funcdecllist -> module " << endl;
          }
        |
          { AST = new module_node(); //StrUtil(string());
            $$ = AST;
            cout << *$$ << "nothing -> module " << endl;
          }
        ;

funcdecl_list :
          funcdecl_list funcdecl SEMI
          { $$ = new StrUtil(*$1 + *$2 + *$3);
            cout << *$$ << " -> funcdecl_list " << endl;
          }
        | funcdecl SEMI
          { $$ = new StrUtil(*$1 + *$2);
            cout << *$$ << " -> funcdecl_list " << endl;
          }
       ;
 
funcdecl :
          FUNCTION ID LPAREN param_list RPAREN
          { $$ = new StrUtil(*$1 + *$2 +*$3 +*$5);
            cout << *$$ << " -> funcdecl " << endl;
          }
        | FUNCTION ID LPAREN  RPAREN
          { $$ = new StrUtil(*$1 + *$2 +*$3 +*$4);
            cout << *$$ << " -> funcdecl " << endl;
          }
        | SFUNCTION ID LPAREN param_list RPAREN
          { $$ = new StrUtil(*$1 + *$2 +*$3 +*$5);
            cout << *$$ << " -> funcdecl " << endl;
          }
        | SFUNCTION ID LPAREN  RPAREN
          { $$ = new StrUtil(*$1 + *$2 +*$3 +*$4);
            cout << *$$ << " -> funcdecl " << endl;
          }
	;


vardecl_list : 
          vardecl_list vardecl SEMI
          { $$ = new StrUtil(*$1 + *$2 +*$3);
            cout << *$$ << " -> vardecl_list " << endl;
          }
        | vardecl SEMI
          { $$ = new StrUtil(*$1 + *$2);
            cout << *$$ << " -> vardecl_list " << endl;
          }
        ;

vardecl : 
         TYPE ID
          { $$ = new StrUtil(*$1 + *$2);
            cout << *$$ << " -> vardecl " << endl;
          }
       | TYPE ID ASSIGN expr
          { $$ = new StrUtil(*$3);
            cout << *$$ << " -> vardecl " << endl;
          }
       | EXTERN TYPE ID  /* extern variable */
          { $$ = new StrUtil(*$1);
            cout << *$$ << " -> vardecl " << endl;
          }
       ;


funcdef_list :
         funcdef
          { *$$ = vector<funcdef_node>(1, *$1); }
       | funcdef_list funcdef
          { $1->push_back(*$2); 
            $$ = $1;
          }
        ;

funcdef :
	  FUNCTION ID LPAREN param_list RPAREN block
          { $$ = new funcdef_node(*$2, *$4);
            cout << "function " << *$2 << " with parameters -> funcdef " << endl;
          }
        | FUNCTION ID LPAREN RPAREN block
          { $$ = new funcdef_node(*$2);
            cout << "function " << *$2 << " with no parameters -> funcdef " << endl;
          }
	| SFUNCTION ID LPAREN param_list RPAREN block
          { $$ = new funcdef_node(*$2, *$4);
            cout << "sfunction " << *$2 << " -> funcdef " << endl;
          }
        | SFUNCTION ID LPAREN RPAREN block
          { $$ = new funcdef_node(*$2);
            cout << "sfunction " << *$2 << " -> funcdef " << endl;
          }
        ;

param_list : 
          param_list COMMA param
          { $1->push_back(*$3);
            $$ = $1;
          }
        | param
          { *$$ = vector<param_node>(1, *$1); }
        ;

param :
         TYPE ID
          { $$ = new param_node(*$1, *$2);
            cout << "type: " << *$1 << " and ID: " << *$2 << "-> param " << endl;
          }
        ;

block : 
	  LCBRACE vardecl_list stmt_list RCBRACE
          { $$ = new StrUtil(*$1 + *$2 + *$3 + *$4);
            cout << *$$ << " -> block " << endl;
          }
	| LCBRACE              stmt_list RCBRACE
          { $$ = new StrUtil(*$1 + *$2 + *$3);
            cout << *$$ << " -> block " << endl;
          }
	| LCBRACE vardecl_list           RCBRACE
          { $$ = new StrUtil(*$1 + *$2 + *$3);
            cout << *$$ << " -> block " << endl;
          }
        | LCBRACE RCBRACE
          { $$ = new StrUtil(*$1 + *$2);
            cout << *$$ << " -> block " << endl;
          }
        ;

stmt_list :
          stmt_list stmt
          { $$ = new StrUtil(*$1 + *$2);
            cout << *$$ << " -> stmt_list " << endl;
          }
        | stmt
          { $$ = new StrUtil(*$1);
            cout << *$$ << " -> stmt_list " << endl;
          }
       ;

stmt : 
         expr SEMI
          { $$ = new StrUtil(*$2);
            cout << *$1 << "; -> stmt " << endl;
          }
       | RETURN expr SEMI
          { $$ = new StrUtil(*$1 + *$3);
            cout << "return " << *$2 << "; -> stmt " << endl;
          }
     ;

expr : 
        expr ADD expr
        { $$ = new expr_node();
          cout << *$$ << " -> expr" << endl;
        }
      | expr SUB expr
        { $$ = new expr_node();
          cout << *$$ << " -> expr" << endl;
        }
      | expr STAR expr
        { $$ = new expr_node();
          cout << *$$ << " -> expr" << endl;
        }
      | expr DIV expr
        { $$ = new expr_node();
          cout << *$$ << " -> expr" << endl;
        }
      | term  ASSIGN expr
        { $$ = new expr_node();
          cout << *$$ << " -> expr" << endl;
        }
      | expr QUESTION expr COLON expr
        { $$ = new expr_node();
          cout << *$$ << " -> expr" << endl;
        }
      | term
        { $$ = $1;
          cout << *$1 << " -> expr" << endl;
        }
      ;

term :
        STRING_LITERAL
        { $$ = new term_node();
          cout << *$$ << " -> term" << endl;
        }
      | INT_LITERAL
        { int temp = atoi((*$1).c_str());
          int_literal_node* temp1 = new int_literal_node(temp);
          $$ = temp1;
          cout << *$$ << " -> term" << endl;
        }
      | ID
        { $$ = new term_node();
          cout << *$$ << " -> term" << endl;
        }
      | LPAREN expr RPAREN
       { $$ = new term_node();
         cout << *$$ << " -> term" << endl;
        }
      | UNARY_OP term
        { $$ = new term_node();
          cout << *$$ << " -> term" << endl;
        }
      | ID LPAREN arglist RPAREN  /* function call */
       { $$ = new term_node();
         cout << *$$ << " -> term" << endl;
       }
      | ID LPAREN RPAREN  /* function call */
       { $$ = new term_node();
         cout << *$$ << " -> term" << endl;
       }
      ;

arglist :
        expr
        { $$ = new StrUtil("expression");
          cout << *$$ << " -> arglist" << endl;
        }
      | arglist COMMA expr
        { $$ = new StrUtil( *$1 + *$2);
        cout << *$$ << " -> arglist" << endl;
        }
      ;

%%
