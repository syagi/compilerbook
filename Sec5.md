# 5.1
```
1: Program -> Inputs Outputs
2: Inputs -> Input
3: Inputs -> Inputs Input
4: Outputs -> ε
5: Outputs -> Outputs Output
6: Input -> INPUT VAR
7: Output -> OUTPUT VAR
8: Exp -> VAR
9: Exp -> Exp PLUS VAR

"input"  { return INPUT; }
"output" { return OUTPUT; }
"+"      { return PLUS; }
[a-zA-Z] { return VAR; }
[" "|"¥n"|"¥t"]+  {}
.        { return ERROR; }
```

## a
```
input X input Y output X+Y
```

順に解釈すると

```
INPUT VAR INPUT VAR OUTPUT VAR PLUS VAR
INPUT VAR INPUT VAR OUTPUT Exp PLUS VAR
INPUT VAR INPUT VAR OUTPUT Exp
INPUT VAR INPUT VAR Output
INPUT VAR INPUT VAR Outputs Output # ε があったとみなす
INPUT VAR INPUT VAR Outputs
INPUT VAR Input Outputs
Input Input Outputs
Inputs Input Outputs
Inputs Outputs
Program
```

## b
```
input X, Y; output X+Y;
```

, が ERROR となるので正しくない


## c
```
input A1 input A2 output A1+A2
```

A1, A2 が VARVAR となるため正しくない

## d
```
input a input a
```

```
INPUT VAR INPUT VAR
INPUT VAR INPUT VAR Outputs
INPUT VAR Input Outputs
Input Input Outputs
Inputs Input Outputs
Inputs Outputs
Program
```

## e
```
INPUT X OUTPUT X
```

lex に "INPUT" "OUTPUT" を食わせてもERROR

## f
```
input a output a+10
```

10をVARに出来ないので正しくない

## g
```
input a output b+c+d
```

```
INPUT VAR OUTPUT VAR PLUS VAR PLUS VAR
INPUT VAR OUTPUT Exp PLUS VAR PLUS VAR
INPUT VAR OUTPUT Exp PLUS VAR
INPUT VAR OUTPUT Exp
INPUT VAR Outputs # Output -> Outputs は省略
Inputs Outputs    # Input -> Inputs は省略
Program
```


# 5.2

```
1: A -> NUM
2: A -> B C
3: B -> ID
4: C -> C ID
5: D -> NUM
6: D -> B D
```

## (1)
A -> NUM  があるため、 D -> NUM は文の導出に寄与しない。  
よって問題文の文法は簡約ではない。

簡約に直すと
```
1: A -> NUM
2: A -> B C
3: B -> ID
4: C -> C ID
5: D -> B A
```

## (2)
D -> NUM  があるため、 A -> NUM は文の導出に寄与しない。  
よって問題文の文法は簡約ではない。

簡約に直すと
```
1: A -> B C
2: B -> ID
3: C -> C ID
4: D -> NUM
5: D -> B D
```

## (3)


# 5.3
```
1: Exp -> Term ADD Exp
2: Exp -> Term SUB Exp
3: Exp -> Term
4: Term -> Factor MUL Term
5: Term -> Factor DIV Term
6: Term -> Factor
```

差分は Term Exp の順序と、Term Factor の順序。  
これにより、　左結合ではなく右結合になる。


# 5.4
規則8を
```
8: Factor -> SUB NUM
9: Factor -> NUM
10: Factor -> LPAR Exp RPAR # もとの規則9
```
に書き換える
```
   Exp
    |
  Factor
 ___|__
 |     |
 |     |
SUB   NUM
```
