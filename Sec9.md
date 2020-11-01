# 9.1
 9-1.c 参照
 実行結果
 ```
 ->TProgram
  ->TDecl(I,one)
    ->TInt((null), 1)
  ->TDAISeq
    ->TDecl(I,two)
      ->TInt((null), 2)
    ->TDAISeq
      ->TDecl(F,dotone)
        ->TFloat((null), 0.100000)
      ->NULL
  ```

# 9.2
ファイルは 9-2 配下

|file|説明|
|:--|:--|
|fig9-9.h|図9.9, 9.4|
|fig9-9.c|図9.9の実装|
|fig9-10.l|図9.10|
|fig9-12.c|図9.11,9.12,9.13|
|9-1.h| 問題9.1|

これらを以下の手順でコンパイルする
```
lex fig9-10.l
gcc -c fig9-9.c
gcc -c 9-1.c
gcc -c fig9-12.c
gcc fig9-9.o 9-1.o fig9-12.o
```

# 9.3
ファイルは 9-3 配下

```
lex fig9-14.l
yacc fig9-16.y
gcc -c y.tab.c
```
ただし、 y.tab.c のコンパイルがうまく行かない
回避手段を失念...

# 9.4


# 9.5
