# 4-1
入力
```
10b, 23d, 11, 03
```

## (1)

正規表現
```
","     { return COM; }
[01]+b  { return BIN; }
[0-9]+d { return DEC; }
[01]+   { return BIN; }
[0-9]+  { retrun DEC; }
.       { return ERR; }
```

トークン列
```
BIN COM DEC COM BIN COM DEC
```


## (2)

正規表現
```
","     { return COM; }
[01]+b  { return BIN; }
[0-9]+d { return DEC; }
[0-9]+  { retrun DEC; }
[01]+   { return BIN; }
.       { return ERR; }
```

トークン列
```
BIN COM DEC COM DEC COM DEC
```

# 4-2
lex記述
```
%{
  enum { COM=1, BIN, DEC, ERROR };
%}
%%
","     { return COM; }
[01]+b  { return BIN; }
[0-9]+d { return DEC; }
.    { return ERROR; }
%%
int yywrap(void) { return 1; }
int main(void) {
  int t;
  while ((t = yylex()) != 0) {
    printf( "number = %d, string = '%s'\n", t, yytext);
  }
}
```

flexの出力 は 4-2-1.yy.c に保存。
以下、トピックだけ解説

enum
```
    457   enum { COM=1, BIN, DEC, ERROR };
```

構文解析は 634行目 `YY_DECL` で実施。

YY_DECL の実態は yylex
```
    614 #define YY_DECL int yylex (void)
```
703行目、yy_find_action あたりから、 ↑ と ↓ の解釈を行う.

入力とパターンのマッチングは 716のswitch文。

```
709 yy_act = yy_accept[yy_current_state];
```
で得られた値に基づき解釈する。

yy_acceptは
```
static yyconst flex_int16_t yy_accept[14] =
    {   0,
        0,    0,    6,    4,    5,    1,    4,    4,    0,    0,
        2,    3,    0
    } ;
```
のような配列。
試しに COMのみの lex文 (4-2-2.l)を作ったところ、
```
static yyconst flex_int16_t yy_accept[8] =
    {   0,
        0,    0,    4,    2,    3,    1,    0
    } ;
```
となった。

解釈するパターンの数に依存して、要素数と数値が決まっているように見えるが、ルールが分からなかった。

（値は case文で使われるので、パターンの数 + 2 ぐらいになる様子）

最後にプログラム部
```
1750 int yywrap(void) { return 1; }
1751 int main(void) {
1752   int t;
1753   while ((t = yylex()) != 0) {
1754     printf( "number = %d, string = '%s'\n", t, yytext);
1755   }
1756 }
```
# 4-3

```
%{
  enum {INT=1, FLOAT, ID, NUM, REAL, ADD, DIV, COMMENT, ERROR };
%}
%%
"float" { return FLOAT; }
"int"   { return INT; }
[a-z][a-z0-9]* { return ID; }
[0-9][0-9]*  { return NUM; }
([0-9]+"."[0-9]*)|([0-9]*"."[0-9]+) { return REAL; }
"+"  { return ADD; }
"/"  { return DIV; }
"/*"[a-z0-9]*"*/" { return COMMENT; }
"\n"|" "|"\t"     { }
.    { return ERROR; }
%%
int yywrap(void) { return 1; }
int main(void) {
  int t;
  while ((t = yylex()) != 0) {
    printf( "number = %d, string = '%s'\n", t, yytext);
  }
}
```

テスト
```
./a.out
float
number = 2, string = 'float'
f
number = 3, string = 'f'
int
number = 1, string = 'int'
inta
number = 3, string = 'inta'
/
number = 7, string = '/'
/*ab*/
number = 8, string = '/*ab*/'
1
number = 4, string = '1'
01
number = 4, string = '01'
1.1
number = 5, string = '1.1'
00
number = 4, string = '00'
```

# 4-4

## (1)
手書き

## (2)

| 状態 | LF   | 入力列の状態 | 注釈                |
| ---- | ---- | ------------ | ---------------- |
| 1    | 0    | ↑↓aaaa       |                  |
| 2    | 2    | a↑↓aaa       |                  |
| 2    | 2    | a↑a↓aa       |                  |
| 2    | 2    | a↑aa↓a       |                  |
| 2    | 2    | a↑aaa↓       | ファイルの終点に到達 |
| 4    | 4    | a↑↓aaa       | a を ERROR と認識  |
| 1    | 0    | a↑↓aaa       |                  |
| 2    | 2    | aa↑↓aa       |                  |
| 2    | 2    | aa↑a↓a       |                  |
| 2    | 2   | aa↑aa↓       | ファイルの終点に到達 |
| 4    | 4    | aa↑↓aa       | a を ERROR と認識  |
| 1    | 0    | aa↑↓aa       |                  |
| 2    | 2    | aaa↑↓a       |                  |
| 2    | 2    | aaa↑a↓       | ファイルの終点に到達 |
| 4    | 4    | aaa↑↓a       | a を ERROR と認識  |
| 1    | 0    | aaa↑↓a       |                  |
| 2    | 2    | aaaa↑↓       | ファイルの終点に到達 |
| 4    | 4    | aaaa↑↓       | a を ERROR と認識  |


遷移回数は 4 + 3 + 2 + 1  = 22回

## (3)
n(n-1)/2
