%{
  enum { COM=1, BIN, DEC, ERROR };
%}
%%
","     { return COM; }
[01]+b  { return BIN; }
[0-9]+d { return DEC; }
.    { return ERROR; }
%%
int yywrap(void) { return 1; }
int main(void) {
  int t;
  while ((t = yylex()) != 0) {
    printf( "number = %d, string = '%s'\n", t, yytext);
  }
}
