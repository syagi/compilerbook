#include<stdio.h>

typedef struct _node {
  int label;
  int type;
  char *name;
  int ival;
  float fval;
  struct _node *left;
  struct _node *right;
} node;

enum{ TINT, TFLOAT};
enum{ TProgram, TDAISeq, TDecl,
      TInput, TAssign,
      TPrintSeq, TPrint, TNewline, 
      TAdd, TSub, TMul, TDiv, TVar, TInt, TFloat };

void print(node *np);
void print2(node *np, int d);
void printSp(int d);
char *getType(node *np);
char *getType2(node *np);
char *getType3(node *np);

// body
void print(node *np){ print2(np,0); }
void print2(node *np, int d) {
  if( np==NULL ){
    printSp(d); printf("->NULL\n");
  }
  else {
    switch(np->label) {
      case TProgram:
        printSp(d);
        printf("->TProgram\n");
        print2(np->left, d+2);
        print2(np->right, d+2);
        break;
    case TDAISeq:
        printSp(d);
        printf("->TDAISeq\n");
        print2(np->left, d+2);
        print2(np->right, d+2);
        break;
    case TDecl:
        printSp(d);
        printf("->TDecl(%s,%s)\n", getType(np),np->name);
        print2(np->left, d+2);
        break;
    case TAssign:
        printSp(d);
        printf("->TAssign(%s,%s)\n", getType2(np),np->name);
        print2(np->right, d+2);
        break;
    case TInput:
        printSp(d);
        printf("->TInput(%s,%s)\n", getType2(np),np->name);
        break;
    case TPrintSeq:
        printSp(d);
        printf("->TPrintSeq\n");
        print2(np->left, d+2);
        print2(np->right, d+2);
        break;
    case TPrint:
        printSp(d);
        printf("->TPrint(%s)\n", getType3(np));
        print2(np->left, d+2);
        break;
    case TNewline:
        printSp(d);
        printf("->TNewline\n");
        break;
    case TAdd:
        printSp(d);
        printf("->TAdd(%s)\n", getType3(np));
        print2(np->left, d+2);
        print2(np->right, d+2);
        break;
    case TSub:
        printSp(d);
        printf("->TSub(%s)\n", getType3(np));
        print2(np->left, d+2);
        print2(np->right, d+2);
        break;
    case TMul:
        printSp(d);
        printf("->TMul(%s)\n", getType3(np));
        print2(np->left, d+2);
        print2(np->right, d+2);
        break;
    case TDiv:
        printSp(d);
        printf("->TDiv(%s)\n", getType3(np));
        print2(np->left, d+2);
        print2(np->right, d+2);
        break;
    case TVar:
        printSp(d);
        printf("->TVar(%s, %s)\n", getType2(np), np->name);
        break;
    case TInt:
        printSp(d);
        printf("->TInt(%s, %i)\n", np->name, np->ival);
        break;
    case TFloat:
        printSp(d);
        printf("->TFloat(%s, %f)\n", np->name, np->fval);
        break;
    default:
        printf("Error");
    }
  }
}

char *getType(node *np){
  switch (np->type){
    case TINT:
      return "I";
    case TFLOAT:
      return "F";
    default:
      return "?";
  }
}

char *getType2(node *np){
  return "not implemented";
}

char *getType3(node *np){
  return "not implemented";
}

void printSp(int d) {
  while( d > 0 ){
    printf(" ");
    d--;
  }
}

int main(int argc, char** argv){
  node tfloat = { TFloat, 0, NULL, 0, 0.1, NULL, NULL};
  node tint2 = { TInt, 0, NULL, 2, 0, NULL, NULL};
  node tint  = { TInt, 0, NULL, 1, 0, NULL, NULL};
  node tdec3 = { TDecl, TFLOAT, "dotone", 0, 0, &tfloat, NULL};
  node tdec2 = { TDecl, TINT, "two", 0, 0, &tint2, NULL};
  node tdec1 = { TDecl, TINT, "one", 0, 0, &tint, NULL};
  node tdai2 = { TDAISeq, 0,NULL,0,0, &tdec3, NULL};
  node tdai  = { TDAISeq, 0,NULL,0,0, &tdec2, &tdai2};
  node tpro  = { TProgram, 0,NULL,0,0, &tdec1, &tdai};

  print( &tpro);
  return 0;
}
