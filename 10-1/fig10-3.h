enum {
	TI2F = TFloat+1,
	TF2I 
};

node *newTI2F(node *left);
node *newTF2I(node *left);
node *castType(node *np, int type);

