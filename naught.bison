%{
#define YY_NO_UNPUT

#include <iostream>
#include <string>
#include <memory>
#include <cstring>
#include <vector>

#include "yy.h"
#include "nodes/module_node.h"
#include "nodes/funcdecl_node.h"
#include "nodes/vardecl_node.h"
#include "nodes/vardecl_assignment_node.h"
#include "nodes/param_node.h"
#include "nodes/stmt_node.h"
#include "nodes/expr_node.h"
#include "nodes/expr_add_node.h"
#include "nodes/expr_sub_node.h"
#include "nodes/expr_mult_node.h"
#include "nodes/expr_div_node.h"
#include "nodes/expr_assign_node.h"
#include "nodes/expr_ternary_node.h"
#include "nodes/term_literal_node.h"
#include "nodes/term_unary_node.h"
#include "nodes/term_id_node.h"
#include "nodes/term_expr_node.h"
#include "nodes/term_function_node.h"

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
  module_node*              module;
  term_node*                term;
  string*                   string_literal;
  int*                      int_literal;
  vector<funcdef_node *>*   func_def_vec;
  funcdef_node*             func_def;
  string*                   id;
  vector<param_node>*       param_vec;
  param_node*               param;
  string*                   type;
  expr_node*                expr;
  stmt_node*                stmt;
  vector<stmt_node *>*      stmt_vec;
  block_node*               block;
  vardecl_node*             vardecl;
  vector<vardecl_node *>*   vardecl_vec;
  vector<expr_node *>*      arg_list;
  funcdecl_node*            funcdecl;
  vector<funcdecl_node *>*  funcdecl_list;
  Unary_Type*               unary;
}

/***********************************************************************
 * The order of these next few lines sets operator precedence, which is
 * important to correct operation of the parser.  Don't change them.
 ***********************************************************************/
%right <string_literal> ASSIGN
%right <string_literal> COLON QUESTION
%left <string_literal> ADD SUB
%left <string_literal> STAR DIV
%right <unary> UNARY_OP
/*********************************************************
 * Okay, that's it -- after this order doesn't matter
 *********************************************************/

/**********************************************************
 * Here (and in the precedence/associativity declarations 
 * above, we're defining symbols that can be returned by
 * the lexer. 
 **********************************************************/

%token <string_literal> LCBRACE RCBRACE RPAREN LPAREN SEMI COMMA EXTERN FUNCTION SFUNCTION RETURN

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
          { AST = new module_node($1, $2, $3);
            $$ = AST;
          }
        |              vardecl_list funcdef_list
          { AST = new module_node(new vector<funcdecl_node *>(), $1, $2);
            $$ = AST;
          }
        | funcdecl_list             funcdef_list
          { AST = new module_node($1, new vector<vardecl_node *>(), $2);
            $$ = AST;
          }
        |                            funcdef_list
          { AST = new module_node(new vector<funcdecl_node *>(), new vector<vardecl_node *>(), $1);
            $$ = AST;
          }
        | funcdecl_list vardecl_list
          { AST = new module_node($1, $2, new vector<funcdef_node *>());
            $$ = AST;
          }
        |              vardecl_list
          { AST = new module_node(new vector<funcdecl_node *>(), $1, new vector<funcdef_node *>());
            $$ = AST;
          }
        | funcdecl_list             
          { AST = new module_node($1, new vector<vardecl_node *>(), new vector<funcdef_node *>());
            $$ = AST;
          }
        |
          { AST = new module_node(new vector<funcdecl_node *>(), new vector<vardecl_node *>(), new vector<funcdef_node *>());
            $$ = AST;
          }
        ;

funcdecl_list :
          funcdecl_list funcdecl SEMI
          { $1->push_back($2);
            $$ = $1;
          }
        | funcdecl SEMI
          { $$ = new vector<funcdecl_node *>(1, $1); }
       ;
 
funcdecl :
          FUNCTION ID LPAREN param_list RPAREN
          { $$ = new funcdecl_node("int", *$2, *$4); }
        | FUNCTION ID LPAREN  RPAREN
          { vector<param_node>* empty = new vector<param_node>();
            $$ = new funcdecl_node("int", *$2, *empty);
          }
        | SFUNCTION ID LPAREN param_list RPAREN
          { $$ = new funcdecl_node("string", *$2, *$4); }
        | SFUNCTION ID LPAREN  RPAREN
          { vector<param_node>* empty = new vector<param_node>();
            $$ = new funcdecl_node("string", *$2, *empty);
          }
	;


vardecl_list : 
          vardecl_list vardecl SEMI
          { $1->push_back($2);
            $$ = $1;
          }
        | vardecl SEMI
          { $$ = new vector<vardecl_node *>(1, $1); }
        ;

vardecl : 
         TYPE ID
          { $$ = new vardecl_node(*$1, *$2, false); }
       | TYPE ID ASSIGN expr
          { $$ = new vardecl_assignment_node(*$1, *$2, false, $4); }
       | EXTERN TYPE ID  /* extern variable */
          { $$ = new vardecl_node(*$2, *$3, true); }
       ;


funcdef_list :
         funcdef
          { $$ = new vector<funcdef_node *>(1, $1); }
       | funcdef_list funcdef
          { $1->push_back($2); 
            $$ = $1;
          }
        ;

funcdef :
	  FUNCTION ID LPAREN param_list RPAREN block
          { $$ = new funcdef_node("int", *$2, *$4, *$6); }
        | FUNCTION ID LPAREN RPAREN block
          { vector<param_node> *empty_list = new vector<param_node>();
            $$ = new funcdef_node("int", *$2, *empty_list, *$5);
          }
	| SFUNCTION ID LPAREN param_list RPAREN block
          { $$ = new funcdef_node("string", *$2, *$4, *$6); }
        | SFUNCTION ID LPAREN RPAREN block
          { vector<param_node> *empty_list = new vector<param_node>();
            $$ = new funcdef_node("string", *$2, *empty_list, *$5);
          }
        ;

param_list : 
          param_list COMMA param
          { $1->push_back(*$3);
            $$ = $1;
          }
        | param
          { $$ = new vector<param_node>(1, *$1); }
        ;

param :
         TYPE ID
          { $$ = new param_node(*$1, *$2); }
        ;

block : 
	  LCBRACE vardecl_list stmt_list RCBRACE
          { $$ = new block_node(*$2, *$3); }
	| LCBRACE              stmt_list RCBRACE
          { vector<vardecl_node *> *empty_list = new vector<vardecl_node*>();
            $$ = new block_node(*empty_list, *$2);
          }
	| LCBRACE vardecl_list           RCBRACE
          { vector<stmt_node *> *empty_list = new vector<stmt_node*>();
            $$ = new block_node(*$2, *empty_list);
          }
        | LCBRACE RCBRACE
          { vector<vardecl_node *>  *empty_list1 = new vector<vardecl_node*>();
            vector<stmt_node *>     *empty_list2 = new vector<stmt_node*>();
            $$ = new block_node(*empty_list1, *empty_list2);
          }
        ;

stmt_list :
          stmt_list stmt
          { $$ = $1;
            $$->push_back($2);
          }
        | stmt
          { $$ = new vector<stmt_node *>();
            $$->push_back($1);
          }
       ;

stmt : 
         expr SEMI
          { $$ = new stmt_node($1, false); }
       | RETURN expr SEMI
          { $$ = new stmt_node($2, true); }
     ;

expr : 
        expr ADD expr
        { $$ = new expr_add_node($1, $3); }
      | expr SUB expr
        { $$ = new expr_sub_node($1, $3); }
      | expr STAR expr
        { $$ = new expr_mult_node($1, $3); }
      | expr DIV expr
        { $$ = new expr_div_node($1, $3); }
      | term  ASSIGN expr
        { $$ = new expr_assign_node($1, $3); }
      | expr QUESTION expr COLON expr
        { $$ = new expr_ternary_node($1, $3, $5); }
      | term
        { $$ = $1; }
      ;

term :
        STRING_LITERAL
        { $$ = new term_literal_node<string>(*$1); }
      | INT_LITERAL
        { $$ = new term_literal_node<int>(*$1); }
      | ID
        { $$ = new term_id_node(*$1); }
      | LPAREN expr RPAREN
       { $$ = new term_expr_node($2); }
      | UNARY_OP term
        { $$ = new term_unary_node(*$1, $2); }
      | ID LPAREN arglist RPAREN  /* function call */
       { $$ = new term_function_node(*$1, *$3); }
      | ID LPAREN RPAREN  /* function call */
       { vector<expr_node *> *empty_vec = new vector<expr_node *>();
         string i = *$1;
         $$ = new term_function_node(*$1, *empty_vec);
       }
      ;

arglist :
        expr
        { $$ = new vector<expr_node *>(1, $1); }
      | arglist COMMA expr
        { $1->push_back($3);
          $$ = $1;
        }
      ;

%%
