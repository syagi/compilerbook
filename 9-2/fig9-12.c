#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fig9-9.h"
#include "9-1.h"
#include "lex.yy.c"

#define EoF 0

node *Z(void);
node *Program(void);
node *DeclStmts(void);
node *DeclStmts2(void);
node *DeclStmt(void);
node *VarDefs(void);
node *VarDefs2(void);
node *PrintStmts(void);
node *PrintStmt(void);
node *VarRefs(void);
node *VarRefs2(void);

void error(){ fprintf(stderr,"syntax error_n"); exit(1); }
int tok;
void advance(void){ tok = yylex(); }
node *eat(int t){ node *p = lval; if(tok == t) advance(); else error(); return p; }
void eOf(void){ if(tok != EoF) error(); } 

int main(){
    node *np;
    advance(); 
    np = Z();
    print(np);
}
node *Z(){
    node *np1;
    np1 = Program();
    eOf();
    return np1;
}
node *Program(void){
    node *np1,*np2;
    np1 = DeclStmts(); 
    np2 = PrintStmts();
    return 
      newTProgram(np1,
                  np2);
}
node *DeclStmts(void){ 
    node *np1,*np3;
    np1 = DeclStmt(); 
    eat(SEMI); 
    np3 = DeclStmts2();
    return 
      append(np1,np3);
}
node *DeclStmts2(void){ 
    node *np1;
    switch(tok){
    case EX:
    case EoF: 
        return NULL;
    case INT: 
        np1 = DeclStmts();
        return np1;
    default: error(); return NULL;
    }
}
node *DeclStmt(void){
    node *np2;
    eat(INT); 
    np2 = VarDefs();
    return np2;
}
node *VarDefs(void){
    node *np1,*np3,*np4;
    np1 = eat(ID);
    eat(EQ); 
    np3 = eat(NUM);
    np4 = VarDefs2();
    return 
      newTDeAsInSeq( 
        newTDecl(
          np1->name,
          TINT,
          np3),
        np4);
}
node *VarDefs2(void){ 
    node *np2,*np4,*np5;
    switch(tok){
    case COMMA:
        eat(COMMA); 
        np2 = eat(ID); 
        eat(EQ); 
        np4 = eat(NUM); 
        np5 = VarDefs2();
        return 
          newTDeAsInSeq( 
            newTDecl(
              np2->name,
              TINT,
              np4),
            np5);
    case SEMI: 
        return NULL;
    default: error(); return NULL;
    }
}
node *PrintStmts(void){ 
    node *np1,*np3;
    switch(tok){
    case EX: 
        np1 = PrintStmt(); 
        eat(SEMI); 
        np3 = PrintStmts(); 
        return 
          append(np1,np3);
    case EoF: 
        return NULL;
    default: error(); return NULL;
    }
}
node *PrintStmt(void){
    node *np2;
    eat(EX); 
    np2 = VarRefs(); 
    return 
      append(
        np2,
        newTPrintSeq( 
          newTNewline(),
          NULL));
}
node *VarRefs(void){
    node *np1,*np2;
    np1 = eat(ID); 
    np2 = VarRefs2();
    return 
      newTPrintSeq(
        newTPrint(np1),
        np2);
}
node *VarRefs2(void){
    node *np2,*np3;
    switch(tok){
    case COMMA: 
        eat(COMMA); 
        np2 = eat(ID); 
        np3 = VarRefs2();
        return 
          newTPrintSeq(
            newTPrint(np2),
            np3);
    case SEMI: 
        return NULL;
    default: error(); return NULL;
    }
}

