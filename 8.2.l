%{
%}
%%
[a-z][a-z0-9]* {return ID;}
0|[1-9][0-9]*  {return NUM;}
"+"   {return ADD;}
"-"   {return SUB;}
"*"   {return MUL;}
"/"   {return DIV;}
"("   {return LPAR;}
")"   {return RPAR;}
"\n"|" "|"\t"   { }
"/*"[a-z0-9]*"*/" { }
.     {return ERROR;}
%%
int yywrap(void){ return 1; }
