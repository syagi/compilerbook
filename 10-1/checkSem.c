#include <stdio.h>
#include <stdlib.h>
#include "fig9-9.h"
#include "fig10-1.h"

void checkSem(node* np){
    if(np == NULL) return;
    switch(np->label){
    case TDecl:
        putVar(np->name,np->type);
        break;
    case TInput: case TVar:
        getType(np->name);
        break;
    case TAssign:
        getType(np->name);
        checkSem(np->left);
        break;
    case TPrint:
        checkSem(np->left);
        break;
    case TProgram:
    case TDeAsInSeq:
    case TPrintSeq:
    case TAdd:
    case TSub:
    case TMul:
    case TDiv:
        checkSem(np->left);
        checkSem(np->right);
    }
}

