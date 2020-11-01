typedef struct _node {
    int           label;
    int           type;
    char          *name;
    int           ival;
    float         fval;
    struct _node *left;
    struct _node *right;
} node;

enum {TINT, TFLOAT };

enum { 
    TProgram,TDeAsInSeq,TDecl,TAssign,TInput,TPrintSeq,
    TPrint,TNewline,TAdd,TSub,TMul,TDiv,TVar,TInt,TFloat };

node *newTProgram(node *left, node *right);
node *newTDeAsInSeq(node *left, node *right);
node *newTDecl(char *name, int type, node *left);
node *newTAssign(char *name, node *left);
node *newTInput(char *name);
node *newTPrintSeq(node *left, node *right);
node *newTPrint(node *left);
node *newTNewline();
node *newTAdd(node *left, node *right);
node *newTSub(node *left, node *right);
node *newTMul(node *left, node *right);
node *newTDiv(node *left, node *right);
node *newTVar(char* name);
node *newTInt(int ival);
node *newTFloat(float fval);

node *append(node *a, node *b);

node *newnode(int label, int type, char *name, int ival, float fval, node *left, node *right);

