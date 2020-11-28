# 10.1

表10.1と表10.3をひとつにまとめて実装する。
ただし、checkSemとinsertTypeを再帰呼び出しする部分は、ひとつにまとめた関数（cSiT)を呼ぶ

コードは 10-1.c

|label|case|
|:--|:--|
|TProgram| cSiT(np->left); <br> cSiT(np->right);|
|TDAISeq|  cSiT(np->left); <br> cSiT(np->right);|
|TDecl| putVar(np->name, np->type); <br> np->left = castType(np->left,np->type) |
|TAssgin| np->type = getType(np->name); <br> cSiT(np->left); <br> np->left = castType|
|TInput| np->type = getType(np->name);|
|TPrintSeq| cSiT(np->left); <br> cSiT(np->right);|
|TPrint| cSiT(np->left); <br> np->type = np->left->type; |
|TNewline| |
|TAdd| 後述|
|TSub| 後述|
|TMul| 後述|
|TDiv| 後述|
|TVar| np->type = getType(np->name); |
|TInt||
|TFloat||

```
cSiT(np->left);
cSiT(np->right);
if(np->left->type == np->right->type) {
  np->type = np->left->type;
} else {
  np->left = castType(np->left,TFLOAT);
  np->right = castType(np->right,TFLOAT);
  np->type = TFLOAT;
}
```
