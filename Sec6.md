# 6.1
```EX EoF```
が呼ばれた場合

1. main から Z() が呼ばれる  
1. Z() が Stmt() を呼び EX が eat() に渡される
1. eat() は  tok と EX を比較し、一致するので advance() する  
1. Stmt() が次に Exp() を呼び、 NUM が eat() に渡される
1. eat() は tok と NUM を比較するが、 このとき tok は EoF なので、error() が呼ばれる

```NUM NUM EoF```
が呼ばれた場合

前述 3 の時点で、 tokがNUMなので、error()

# 6.2
|構文規則|Directorの定義|Director集合|
|----|----|----|
|Z -> A EoF| First(A EoF) | {NUM, EoF} |
|A -> SEMI| First(SEMI) | {SEMI} |
|A -> B C| First(B C) | {NUM, SEMI, EoF} |
|B -> ε| First(ε) ∪ Follow(B) | {NUM, SEMI, EoF} |
|C -> B| First(B) ∪ FOllow(C) | {NUM, Eof} |
|C -> A NUM| First(A NUM) | {NUM, SEMI} |

||NUM|SEMI|EoF|
|-|---|---|---|
|Z|Z -> A EoF| |Z -> A EoF|
|A|A -> B C| A -> SEMI, A-> B C | A -> B C|
|B|B -> ε|B -> ε|B -> ε|
|C|C -> B, C -> A NUM| C -> A NUM| C -> B|

表に衝突があるため、下向き構文解析ではない。


# 6.3

| |nullable|First |Follow |
|-|--|--|--|
|Exp|false|{ID, NUM, LPAR}|{RPAR, EoF}|
|Exp2|true|{ADD, SUB}|{RPAR, EoF}|
|Term|false|{ID, NUM, LPAR}|{ADD, SUB, RPAR, EoF}|
|Term2|true|{MUL, DIV}|{ADD, SUB, RPAR, EoF}|
|Factor|false|{ID, NUM, LPAR}|{ADD, SUB, MUL, DIV, EoF}


| |Director |
|-|-|
| Z → Exp Eof              | {ID, NUM, LPAR}|
| Exp → Term Exp2          | {ID, NUM, LPAR}
| Exp2 → ADD Term Exp2     | {ADD}
| Exp2 → SUB Term Exp2     | {SUB}
| Exp2 → ε                | {RPAR, EoF}
| Term → Factor Term2      | {ID, NUM, LPAR}
| Term2 → MUL Factor Term2 | {MUL}
| Term2 → DIV Factor Term2 | {DIV}
| Term2 → ε               | {ADD, SUB, RPAR, EoF}
| Factor → ID              | {ID}
| Factor → NUM             | {NUM}
| Factor → LPAR Exp RPAR   | {LPAR}

| |ID|NUM|ADD|SUB|MUL|DIV|LPAR|RPAR|EoF|
|-|--|---|---|---|---|---|----|----|---|
|Z|Z → Exp Eof|Z → Exp Eof|||||Z → Exp Eof|||
|Exp|Exp → Term Exp2|Exp → Term Exp2|||||Exp → Term Exp2|
|Exp2|||Exp2 → ADD Term Exp2|Exp2 → SUB Term Exp2 ||||Exp2 → ε |Exp2 → ε |
|Term|Term → Factor Term2|Term → Factor Term2|||||Term → Factor Term2|
|Term2|||Term2 → ε|Term2 → ε|Term2 → MUL Factor Term2|Term2 → DIV Factor Term2||Term2 → ε|Term2 → ε|
|Factor|Factor → ID|Factor → NUM|||||Factor → LPAR Exp RPAR|

```
void Z(){
  switch(tok){
    case ID:
    case NUM:
    case LPAR:
      Exp(); eOf();
      break;
    default:
      error();
  }
}

void Exp() {
  switch(tok){
    case ID:
    case NUM:
    case LPAR:
      Term(); Exp2();
      break;
    default:
      error();
  }
}

void Exp2() {
  switch(tok){
    case ADD:
      eat(ADD); Term(); Exp2();
      break;
    case SUB:
      eat(SUB); Term(); Exp2();
      break;
    case RPAR:
    case EoF:
      break();
    default:
      error();
  }
}

void Term(){
  switch(tok){
    case ID:
    case NUM:
    case LPAR:
      Term(); Factor(); Term2();
      break;
    default:
      error();
  }
}

void Term2(){
  switch(tok){
    case ADD:
    case SUB:
    case RPAR:
    case EoF:
      break;
    case MUL:
      eat(MUL); Factor(); Term2();
      break
    case DIV:
      eat(DIV); Factor(); Term2();
      break
    default:
      error();
}

void Factor(){
  switch(tok){
    case ID:
      eat(ID); break;
    case NUM:
      eat(NUM); break;
    case LPAR
      eat(LPAR); Exp(); eat(RPAR);
      break;
    default:
      error();
  }
}
```


# 6.4

Exp -> Exp ...  
の部分を直す

```
0: Z -> Exp Exp2
1: Exp2 -> ADD Exp
2: Exp2 -> SUB Exp
3: Exp2 -> MUL Exp
4: Exp2 -> DIV Exp
5: Exp2 -> ε
6: Exp -> ID
7: Exp -> NUM
8: Exp -> LPAR Exp RPAR
```
| |nullable|First |Follow |
|-|--|--|--|
|Exp|false| {ID, NUM, LPAR} | {RPAR, EoF}
|Exp2|true| {ADD, SUB, MUL, DIV}| {RPAR, EoF}

| |Director |
|-|-|
|0: Z -> Exp Exp2| {ID, NUM, LPAR}
|1: Exp2 -> ADD Exp| {ADD}
|2: Exp2 -> SUB Exp| {SUB}
|3: Exp2 -> MUL Exp| {MUL}
|4: Exp2 -> DIV Exp| {DIV}
|5: Exp2 -> ε| {RPAR, EoF}|
|6: Exp -> ID| {ID}
|7: Exp -> NUM| {NUM}
|8: Exp -> LPAR Exp RPAR| {LPAR}

| |ID|NUM|ADD|SUB|MUL|DIV|LPAR|RPAR|EoF|
|-|--|---|---|---|---|---|----|----|---|
|Z|Z -> Exp Exp2|Z -> Exp Exp2|||||Z -> Exp Exp2|
|Exp|Exp -> ID|Exp -> NUM|||||Exp -> LPAR Exp RPAR|
|Exp2|||Exp2 -> ADD Exp|Exp2 -> SUB Exp|Exp2 -> MUL Exp|Exp2 -> DIV Exp||Exp2 -> ε|Exp2 -> ε|

衝突がないので下向き構文解析可能

# 6.5

## (1)

```
0: Z -> Input EoF
1: Input -> Seq
2: Seq -> NUM Seq2
3: Seq2 -> Seq
4: Seq2 -> ε
```

## (2)

| |nullable|First |Follow |
|-|--|--|--|
|Input| false| {NUM} | {EoF}
|Seq| false| {NUM} | {EoF}
|Seq2| true| {NUM} | {EoF}

| |Director |
|-|-|
|0: Z -> Input EoF| {NUM}
|1: Input -> Seq| {NUM}
|2: Seq -> NUM Seq2| {NUM}
|3: Seq2 -> Seq| {NUM}
|4: Seq2 -> ε| {EoF}


| |NUM|EoF|
|-|---|---|
|Z|Z -> Input EoF||
|Input|Input -> Seq||
|Seq|Seq -> NUM Seq2||
|Seq2|Seq2 -> Seq|Seq2 -> ε|

# 6.6
図 6.14 で 関数呼び出ししていた箇所を全て push(関数ポインタ) とし、 入力の終端に至るまで pop と関数実行を繰り返せば、 再帰なしになる。

処理上は、戻りアドレスをスタックに積むか、呼出アドレスをスタックに積むか、の違いだが、この方法は、再帰呼び出しよりもスタックが深くならない・・・気がする。
