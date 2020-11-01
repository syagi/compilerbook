%% 
int                  { return INT; } 
float                { return FLOAT; } 
[a-z][a-z0-9]*       { yylval = newTVar(strdup(yytext));
                       return ID; } 
0|[1-9][0-9]*        { yylval = newTInt(strtol(yytext,NULL,10));
                       return NUM; } 
([0-9]+"."[0-9]*)|([0-9]*"."[0-9]+) { 
                       yylval = newTFloat(strtof(yytext,NULL));
                       return REAL; } 
","                  { return COMMA; } 
"="                  { return EQ; } 
"!"                  { return EX; } 
"?"                  { return QU; } 
";"                  { return SEMI; } 
"+"                  { return ADD; } 
"-"                  { return SUB; } 
"*"                  { return MUL; } 
"/"                  { return DIV; } 
"("                  { return LPAR; } 
")"                { return RPAR; } 
"_n"|" "|"_t"      { } 
"/*"[a-z0-9 ]*"*/" { } 
.                  { return ERROR; } 
%% 
int yywrap(){ return 1; } 

