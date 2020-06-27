%{
  enum {INT=1, FLOAT, ID, NUM, REAL, ADD, DIV, COMMENT, ERROR };
%}
%%
"float" { return FLOAT; }
"int"   { return INT; }
[a-z][a-z0-9]* { return ID; }
[0-9][0-9]*  { return NUM; }
([0-9]+"."[0-9]*)|([0-9]*"."[0-9]+) { return REAL; }
"+"  { return ADD; }
"/"  { return DIV; }
"/*"[a-z0-9]*"*/" { return COMMENT; }
"\n"|" "|"\t"     { }
.    { return ERROR; }
%%
int yywrap(void) { return 1; }
int main(void) {
  int t;
  while ((t = yylex()) != 0) {
    printf( "number = %d, string = '%s'\n", t, yytext);
  }
}
