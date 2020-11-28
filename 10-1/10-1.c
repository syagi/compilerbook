#include <stdio.h>
#include <stdlib.h>
#include "fig9-9.h"
#include "fig10-1.h"
#include "fig10-3.h"
void cSiT(node* np){
  if(np == NULL) return;
  switch(np->label){
    case TDecl:
      putVar(np->name,np->type);
      np->left = castType(np->left,np->type);
    case TInput: case TVar:
      np->type = getType(np->name);
      break;
    case TAssign:
      np->type = getType(np->name);
      cSiT(np->left);
      np->left = castType(np->left,np->type);
      break;
    case TPrint:
      cSiT(np->left);
      np->type = np->left->type;
      break;
    case TProgram:
    case TDeAsInSeq:
    case TPrintSeq:
      cSiT(np->left);
      cSiT(np->right);
      break;
    case TAdd:
    case TSub:
    case TMul:
    case TDiv:
      cSiT(np->left);
      cSiT(np->right);
      if(np->left->type == np->right->type) {
        np->type = np->left->type;
      } else {
        np->left = castType(np->left,TFLOAT);
        np->right = castType(np->right,TFLOAT);
        np->type = TFLOAT;
      }
  }
}
