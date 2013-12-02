%{
 #define YY_NO_UNPUT

 #include <iostream>
 #include <string>
 #include <stdexcept>
 #include <vector>
 using namespace std;


 int yyerror(char *s);

 #include "StrUtil.h"
 #include "nodes/funcdecl_node.h"
 #include "nodes/module_node.h"
 #include "nodes/funcdef_node.h"
 #include "nodes/param_node.h"
 #include "nodes/expr_node.h"
 #include "nodes/stmt_node.h"
 #include "nodes/expr_add_node.h"
 #include "nodes/expr_sub_node.h"
 #include "nodes/expr_mult_node.h"
 #include "nodes/expr_div_node.h"
 #include "nodes/term_node.h"
 #include "nodes/term_id_node.h"
 #include "nodes/term_unary_node.h"
 #include "parser.hh"
%}

digit       [0-9]
char        [a-zA-Z_]
nmchar      [a-zA-Z0-9_]
hexdigit    [0-9a-fA-F]
ident       {char}{nmchar}*
number      {digit}+

%%

"#".*        { /* ignore single line comments. */ }
";"          { yylval.string_val = new StrUtil(yytext); return SEMI; }
","          { yylval.string_val = new StrUtil(yytext); return COMMA; }
"="          { yylval.string_val = new StrUtil(yytext); return ASSIGN; }
"+"          { yylval.string_val = new StrUtil(yytext); return ADD; }
"*"          { yylval.string_val = new StrUtil(yytext); return STAR; }
"-"          { yylval.string_val = new StrUtil(yytext); return SUB; }
"/"          { yylval.string_val = new StrUtil(yytext); return DIV; }
"?"          { yylval.string_val = new StrUtil(yytext); return QUESTION; }
":"          { yylval.string_val = new StrUtil(yytext); return COLON; }
"("          { yylval.string_val = new StrUtil(yytext); return LPAREN; }
")"          { yylval.string_val = new StrUtil(yytext); return RPAREN; }
"{"          { yylval.string_val = new StrUtil(yytext); return LCBRACE; }
"}"          { yylval.string_val = new StrUtil(yytext); return RCBRACE; }
"extern"     { yylval.string_val = new StrUtil(yytext); return EXTERN; }
"sfunction"  { yylval.string_val = new StrUtil(yytext); return SFUNCTION; }
"function"   { yylval.string_val = new StrUtil(yytext); return FUNCTION; }
"return"     { yylval.string_val = new StrUtil(yytext); return RETURN; }
"print"      { Unary_Type *t = new Unary_Type(PRINT);
               yylval.unary = t;
               return UNARY_OP; }
"&"          { Unary_Type *t = new Unary_Type(ADDRESSOF);
               yylval.unary = t;
               return UNARY_OP; }
"@"          { Unary_Type *t = new Unary_Type(DEREFERENCE);
               yylval.unary = t;
               return UNARY_OP; }
"int"        { yylval.string_val = new StrUtil(yytext); return TYPE; }
"string"     { yylval.string_val = new StrUtil(yytext); return TYPE; }
"pointer"    { yylval.string_val = new StrUtil(yytext); return TYPE; }
\"[^\"]*\"   { yylval.string_literal = new string(yytext);
               return STRING_LITERAL; }
{number}     { int *int_value = new int(atoi(yytext));
               yylval.int_literal = int_value;
               return INT_LITERAL; }
{ident}      { yylval.string_val = new StrUtil(yytext); return ID; }
[ \t\r\f]    { /* ignore white space. */ }
[\n]         { yylineno++; }
.            { runtime_error e(string("Lexer: Line ") + to_string(yylineno) + 
                       ": Illegal character: " + yytext);
               throw e;
             }
