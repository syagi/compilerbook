%{
enum { INT = 1, ID, NUM, COMMA, EQ, EX, SEMI, ERROR };
node *lval;
%}
%%
int            { return INT; }
[a-z][a-z0-9]* { lval = newTVar(strdup(yytext));
                 return ID; }
0|[1-9][0-9]*  { lval = newTInt(strtol(yytext,NULL,10));
                 return NUM; }
","            { return COMMA; }
"="            { return EQ; }
"!"            { return EX; }
";"            { return SEMI; }
" "|"_n"|"_t"  { }
"/*"[a-z0-9 ]*"*/" { }
.              { return ERROR; }
%%
int yywrap(){ return 1; }

