%{
  enum {INT=1, FLOAT, ID, NUM, REAL, COMMA, EQ, EX,
        QU, SEMI, ADD, SUB, MUL, DIV, LPAR, RPAR, ERROR };
%}
%%
int   { return INT; }
float { return FLOAT; }
[a-z][a-z0-9]* { return ID; }
0|[1-9][0-9]*  { return NUM; }
([0-9]+"."[0-9]*)|([0-9]*"."[0-9]+) { return REAL; }
","  { return COMMA; }
"="  { return EQ; }
"!"  { return EX; }
"?"  { return QU; }
";"  { return SEMI; }
"+"  { return ADD; }
"-"  { return SUB; }
"*"  { return MUL; }
"/"  { return DIV; }
"("  { return LPAR; }
")"  { return RPAR; }
"\n"|" "|"\t"     { }
"/*"[a-z0-9]*"*/" { }
.    { return ERROR; }
%%
int yywrap(void) { return 1; }
int main(void) {
  int t;
  while ((t = yylex()) != 0) {
    printf( "number = %d, string = '%s'\n", t, yytext);
  }
}
