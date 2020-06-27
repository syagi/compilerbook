%{
  enum { COM=1 ERROR };
%}
%%
","     { return COM; }
.    { return ERROR; }
%%
int yywrap(void) { return 1; }
int main(void) {
  int t;
  while ((t = yylex()) != 0) {
    printf( "number = %d, string = '%s'\n", t, yytext);
  }
}
