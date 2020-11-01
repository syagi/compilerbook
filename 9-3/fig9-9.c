#include <stdio.h>
#include <stdlib.h>
#include "fig9-9.h"

node *newnode(int label, int type, char *name, int ival, float fval, node *left, node *right){
    node* np = (node*) malloc(sizeof(node));
    np->label = label;
    np->type = type;
    np->name = name;
    np->ival = ival;
    np->fval = fval;
    np->left = left;
    np->right = right;
    return np;
}

node *newTProgram(node *left, node *right){ return newnode(TProgram,-1,NULL,0,0,left,right); }
node *newTDeAsInSeq(node *left, node *right){ return newnode(TDeAsInSeq,-1,NULL,0,0,left,right); }
node *newTDecl(char *name, int type, node *left){ return newnode(TDecl,type,name,0,0,left,NULL); }
node *newTAssign(char *name, node *left){ return newnode(TAssign,-1,name,0,0,left,NULL); }
node *newTInput(char *name){ return newnode(TInput,-1,name,0,0,NULL,NULL); }
node *newTPrintSeq(node *left, node *right){ return newnode(TPrintSeq,-1,NULL,0,0,left,right); }
node *newTPrint(node *left){ return newnode(TPrint,-1,NULL,0,0,left,NULL); }
node *newTNewline(){ return newnode(TNewline,-1,NULL,0,0,NULL,NULL); }
node *newTAdd(node *left, node *right){ return newnode(TAdd,-1,NULL,0,0,left,right); }
node *newTSub(node *left, node *right){ return newnode(TSub,-1,NULL,0,0,left,right); }
node *newTMul(node *left, node *right){ return newnode(TMul,-1,NULL,0,0,left,right); }
node *newTDiv(node *left, node *right){ return newnode(TDiv,-1,NULL,0,0,left,right); }
node *newTVar(char *name){ return newnode(TVar,-1,name,0,0,NULL,NULL); }
node *newTInt(int ival){ return newnode(TInt,TINT,NULL,ival,0,NULL,NULL); }
node *newTFloat(float fval){ return newnode(TFloat,TFLOAT,NULL,0,fval,NULL,NULL); }

node *append(node* ap, node* bp){
    if(ap == NULL) return bp;
    else{
        node* np = ap;
        while(np->right != NULL) np = np->right;
        np->right = bp;
        return ap;
    }
}

