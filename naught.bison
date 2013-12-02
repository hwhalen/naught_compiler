%{
#define YY_NO_UNPUT

#include <iostream>
#include <string>
#include <memory>
#include <cstring>
#include <vector>

#include "yy.h"
#include "StrUtil.h"
#include "nodes/module_node.h"
#include "nodes/funcdecl_node.h"
#include "nodes/param_node.h"
#include "nodes/stmt_node.h"
#include "nodes/expr_node.h"
#include "nodes/expr_add_node.h"
#include "nodes/expr_sub_node.h"
#include "nodes/expr_mult_node.h"
#include "nodes/expr_div_node.h"
#include "nodes/expr_assign_node.h"
#include "nodes/term_literal_node.h"
#include "nodes/term_unary_node.h"
#include "nodes/term_id_node.h"

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
  StrUtil*                string_val;
  module_node*            module;
  term_node*              term;
  string*                 string_literal;
  int*                    int_literal;
  vector<funcdef_node>*   func_def_vec;
  funcdef_node*           func_def;
  string*                 id;
  vector<param_node>*     param_vec;
  param_node*             param;
  string*                 type;
  expr_node*              expr;
  stmt_node*              stmt;
  vector<stmt_node>*      stmt_vec;
  block_node*             block;
  vardecl_node*           vardecl;
  vector<vardecl_node>*   vardecl_vec;
  vector<expr_node>*      arg_list;
  funcdecl_node*          funcdecl;
  vector<funcdecl_node>*  funcdecl_list;
  Unary_Type*             unary;
}

/***********************************************************************
 * The order of these next few lines sets operator precedence, which is
 * important to correct operation of the parser.  Don't change them.
 ***********************************************************************/
%right <string_val> ASSIGN
%right <string_val> COLON QUESTION
%left <string_val> ADD SUB
%left <string_val> STAR DIV
%right <unary> UNARY_OP
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
%token <string_literal> STRING_LITERAL
%token <int_literal> INT_LITERAL
%token <id> ID

/**********************************************************
 * Now we're defining the type associated with nodes
 * corresponding to non-terminals.
 **********************************************************/

%type <module> module
%type <func_def> funcdef
%type <block> block
%type <vardecl> vardecl
%type <funcdecl> funcdecl
%type <expr> expr
%type <term> term
%type <stmt> stmt

%type <stmt_vec> stmt_list
%type <vardecl_vec> vardecl_list
%type <funcdecl_list> funcdecl_list
%type <param> param;
%type <param_vec> param_list;
%type <func_def_vec> funcdef_list
%type <arg_list> arglist;

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
          { AST = new module_node();
            $$ = AST;
            cout << *$$ << "funcecllist vardeclist funcdeflist -> module " << endl;
          }
        |              vardecl_list funcdef_list
          { AST = new module_node();
            $$ = AST;
            cout << *$$ << "vardecllist funcdeflist -> module " << endl;
          }
        | funcdecl_list             funcdef_list
          { AST = new module_node();
            $$ = AST;
            cout << *$$ << "funcdecllist and funcdeflist -> module " << endl;
          }
        |                            funcdef_list
          { AST = new module_node(*$1);
            $$ = AST;
            cout << *$$ << " -> module " << endl;
          }
        | funcdecl_list vardecl_list
          { AST = new module_node();
            $$ = AST;
            cout << *$$ << "funcdecllist vardecllist -> module " << endl;
          }
        |              vardecl_list
          { AST = new module_node();
            $$ = AST;
            cout << *$$ << "vardecllist -> module " << endl;
          }
        | funcdecl_list             
          { AST = new module_node();
            $$ = AST;
            cout << *$$ << "funcdecllist -> module " << endl;
          }
        |
          { AST = new module_node();
            $$ = AST;
            cout << *$$ << "nothing -> module " << endl;
          }
        ;

funcdecl_list :
          funcdecl_list funcdecl SEMI
          { $1->push_back(*$2);
            $$ = $1;
            cout << " -> funcdecl_list " << endl;
          }
        | funcdecl SEMI
          { $$ = new vector<funcdecl_node>(1, *$1);
            cout << " -> funcdecl_list " << endl;
          }
       ;
 
funcdecl :
          FUNCTION ID LPAREN param_list RPAREN
          { $$ = new funcdecl_node(*$2, *$4);
            cout << *$$ << " -> funcdecl " << endl;
          }
        | FUNCTION ID LPAREN  RPAREN
          { vector<param_node>* empty = new vector<param_node>();
            $$ = new funcdecl_node(*$2, *empty);
            cout << *$$ << " -> funcdecl " << endl;
          }
        | SFUNCTION ID LPAREN param_list RPAREN
          { $$ = new funcdecl_node(*$2, *$4);
            cout << *$$ << " -> funcdecl " << endl;
          }
        | SFUNCTION ID LPAREN  RPAREN
          { vector<param_node>* empty = new vector<param_node>();
            $$ = new funcdecl_node(*$2, *empty);
            cout << *$$ << " -> funcdecl " << endl;
          }
	;


vardecl_list : 
          vardecl_list vardecl SEMI
          { $1->push_back(*$2);
            $$ = $1;
          }
        | vardecl SEMI
          { $$ = new vector<vardecl_node>(1, *$1); }
        ;

vardecl : 
         TYPE ID
          { $$ = new vardecl_node(*$1, *$2, false);
            cout << *$$ << " -> vardecl" << endl;
          }
       | TYPE ID ASSIGN expr
          { $$ = new vardecl_node(*$1, *$2, false);
            $$->set_payload($4);
            cout << *$$ << " -> vardecl" << endl;
          }
       | EXTERN TYPE ID  /* extern variable */
          { $$ = new vardecl_node(*$2, *$3, true);
            cout << *$$ << " ->vardecl" << endl;
          }
       ;


funcdef_list :
         funcdef
          { $$ = new vector<funcdef_node>(1, *$1); }
       | funcdef_list funcdef
          { $1->push_back(*$2); 
            $$ = $1;
          }
        ;

funcdef :
	  FUNCTION ID LPAREN param_list RPAREN block
          { $$ = new funcdef_node(*$2, *$4, *$6);
            cout << "function " << *$2 << " with parameters -> funcdef " << endl;
          }
        | FUNCTION ID LPAREN RPAREN block
          { vector<param_node> *empty_list = new vector<param_node>();
            $$ = new funcdef_node(*$2, *empty_list, *$5);
            cout << *$$ << " -> funcdef " << endl;
          }
	| SFUNCTION ID LPAREN param_list RPAREN block
          { $$ = new funcdef_node(*$2, *$4, *$6);
            cout << "sfunction " << *$2 << " -> funcdef " << endl;
          }
        | SFUNCTION ID LPAREN RPAREN block
          { vector<param_node> *empty_list = new vector<param_node>();
            $$ = new funcdef_node(*$2, *empty_list, *$5);
            cout << "sfunction " << *$2 << " -> funcdef " << endl;
          }
        ;

param_list : 
          param_list COMMA param
          { $1->push_back(*$3);
            $$ = $1;
            cout << "recursive param works" << endl;
          }
        | param
          { *$$ = vector<param_node>(1, *$1); 
            cout << "base case param works" << endl;
          }
        ;

param :
         TYPE ID
          { $$ = new param_node(*$1, *$2);
            cout << "type: " << *$1 << " and ID: " << *$2 << "-> param " << endl;
          }
        ;

block : 
	  LCBRACE vardecl_list stmt_list RCBRACE
          { $$ = new block_node(*$2, *$3);
            cout << *$$ << " -> block " << endl;
          }
	| LCBRACE              stmt_list RCBRACE
          { vector<vardecl_node> *empty_list = new vector<vardecl_node>();
            $$ = new block_node(*empty_list, *$2);
            cout << *$$ << " -> block " << endl;
          }
	| LCBRACE vardecl_list           RCBRACE
          { vector<stmt_node> *empty_list = new vector<stmt_node>();
            $$ = new block_node(*$2, *empty_list);
            cout << *$$ << " -> block " << endl;
          }
        | LCBRACE RCBRACE
          { vector<vardecl_node>  *empty_list1 = new vector<vardecl_node>();
            vector<stmt_node>     *empty_list2 = new vector<stmt_node>();
            $$ = new block_node(*empty_list1, *empty_list2);
            cout << *$$ << " -> block " << endl;
          }
        ;

stmt_list :
          stmt_list stmt
          { $$ = $1;
            $$->push_back(*$2);
            cout <<  " -> stmt_list " << endl;
          }
        | stmt
          { $$ = new vector<stmt_node>();
            $$->push_back(*$1);
            cout << *$1 << " -> stmt_list " << endl;
          }
       ;

stmt : 
         expr SEMI
          { $$ = new stmt_node($1);
            cout << *$$ << " -> stmt " << endl;
          }
       | RETURN expr SEMI
          { $$ = new stmt_node($2);
            cout << "return " << *$$ << " -> stmt " << endl;
          }
     ;

expr : 
        expr ADD expr
        { $$ = new expr_add_node($1, $3);
          cout << *$$ << " -> expr" << endl;
        }
      | expr SUB expr
        { $$ = new expr_sub_node($1, $3);
          cout << *$$ << " -> expr" << endl;
        }
      | expr STAR expr
        { $$ = new expr_mult_node($1, $3);
          cout << *$$ << " -> expr" << endl;
        }
      | expr DIV expr
        { $$ = new expr_div_node($1, $3);
          cout << *$$ << " -> expr" << endl;
        }
      | term  ASSIGN expr
        { $$ = new expr_assign_node($1, $3);
          cout << *$$ << " -> expr" << endl;
        }
      | expr QUESTION expr COLON expr
        { $$ = new expr_node();
          cout << *$$ << " -> expr" << endl;
        }
      | term
        { $$ = $1;
          cout << *$$ << " -> expr" << endl;
        }
      ;

term :
        STRING_LITERAL
        { $$ = new term_literal_node<string>(*$1);
          cout << *$$ << " -> term" << endl;
        }
      | INT_LITERAL
        { $$ = new term_literal_node<int>(*$1);
          cout << *$$ << " -> term" << endl;
        }
      | ID
        { $$ = new term_id_node(*$1);
          cout << *$$ << " -> term" << endl;
        }
      | LPAREN expr RPAREN
       { $$ = new term_node();
         cout << *$$ << " -> term" << endl;
        }
      | UNARY_OP term
        { $$ = new term_unary_node(*$1, $2);
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
        { $$ = new vector<expr_node>(1, *$1);
          cout << *$1 << " -> arglist" << endl;
        }
      | arglist COMMA expr
        { $1->push_back(*$3);
          $$ = $1;
          cout << " -> arglist" << endl;
        }
      ;

%%
