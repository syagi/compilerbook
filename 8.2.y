%token ID NUM ADD SUB MUL DIV LPAR RPAR ERROR;

%%
Exp : Exp ADD Term {}
    | Exp SUB Term {}
    | Term {}
Term : Term MUL Factor {}
     | Term DIV Factor {}
     | Factor {}
Factor : ID {}
       | NUM {}
       | LPAR Exp RPAR

%%
#include "lex.yy.c"
int main () {
  if(!yyparse()) printf("successfully ended\n");
}
int yyerror (char *s) { printf("%s\n",s); }
