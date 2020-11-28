#include <stdio.h>
#include <stdlib.h>
#include "fig9-9.h"
#include "fig10-3.h"

node *newTI2F(node *left){ return newnode(TI2F,TFLOAT,NULL,0,0,left,NULL); }
node *newTF2I(node *left){ return newnode(TF2I,TINT,NULL,0,0,left,NULL); }

node *castType(node *np, int type){
    if(np->type != type){
        if(type == TINT) {
		printf("warning: assignment to `int' from `float'_n");
		return newTF2I(np);
        } else             return newTI2F(np);
    } else return np;
}

