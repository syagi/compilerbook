# 1-1

```
#include <stdio.h>

int main(){
  int a=1, b=2, c=3;
  int x;
  x = a*b+c;
  return x;
}
```

```assembly
.section	__TEXT,__text,regular,pure_instructions
.build_version macos, 10, 14	sdk_version 10, 15
.globl	_main                   ## -- Begin function main
.p2align	4, 0x90
_main:                                  ## @main
.cfi_startproc
## %bb.0:
pushq	%rbp
.cfi_def_cfa_offset 16
.cfi_offset %rbp, -16
movq	%rsp, %rbp
.cfi_def_cfa_register %rbp
movl	$0, -4(%rbp)
movl	$1, -8(%rbp)
movl	$2, -12(%rbp)
movl	$3, -16(%rbp)
movl	-8(%rbp), %eax
imull	-12(%rbp), %eax
addl	-16(%rbp), %eax
movl	%eax, -20(%rbp)
movl	-20(%rbp), %eax
popq	%rbp
retq
.cfi_endproc
                                      ## -- End function
```

# 1-2

## x86_64

```asm
main:
        push    rbp
        mov     rbp, rsp
        mov     DWORD PTR [rbp-4], 1
        mov     DWORD PTR [rbp-8], 2
        mov     DWORD PTR [rbp-12], 3
        mov     eax, DWORD PTR [rbp-4]
        imul    eax, DWORD PTR [rbp-8]
        mov     edx, eax
        mov     eax, DWORD PTR [rbp-12]
        add     eax, edx
        mov     DWORD PTR [rbp-16], eax
        mov     eax, DWORD PTR [rbp-16]
        pop     rbp
        ret
```



## ARM

```assembly
main:
        str     fp, [sp, #-4]!
        add     fp, sp, #0
        sub     sp, sp, #20
        mov     r3, #1
        str     r3, [fp, #-8]
        mov     r3, #2
        str     r3, [fp, #-12]
        mov     r3, #3
        str     r3, [fp, #-16]
        ldr     r3, [fp, #-8]
        ldr     r2, [fp, #-12]
        mul     r1, r2, r3
        ldr     r2, [fp, #-16]
        add     r3, r2, r1
        str     r3, [fp, #-20]
        ldr     r3, [fp, #-20]
        mov     r0, r3
        add     sp, fp, #0
        ldr     fp, [sp], #4
        bx      lr
```




# 1-3
https://dev.classmethod.jp/server-side/java/classfile-reading/

```
Classfile /Users/sin/compiler/Test.class
  Last modified 2020/02/22; size 446 bytes
  MD5 checksum 6307acc1644c34f44734c5552e476f8d
  Compiled from "Test.java"
class Test
  minor version: 0
  major version: 52
  flags: ACC_SUPER
Constant pool:
   #1 = Methodref          #5.#15         // java/lang/Object."<init>":()V
   #2 = Fieldref           #16.#17        // java/lang/System.out:Ljava/io/PrintStream;
   #3 = Methodref          #18.#19        // java/io/PrintStream.println:(F)V
   #4 = Class              #20            // Test
   #5 = Class              #21            // java/lang/Object
   #6 = Utf8               <init>
   #7 = Utf8               ()V
   #8 = Utf8               Code
   #9 = Utf8               LineNumberTable
  #10 = Utf8               main
  #11 = Utf8               ([Ljava/lang/String;)V
  #12 = Utf8               StackMapTable
  #13 = Utf8               SourceFile
  #14 = Utf8               Test.java
  #15 = NameAndType        #6:#7          // "<init>":()V
  #16 = Class              #22            // java/lang/System
  #17 = NameAndType        #23:#24        // out:Ljava/io/PrintStream;
  #18 = Class              #25            // java/io/PrintStream
  #19 = NameAndType        #26:#27        // println:(F)V
  #20 = Utf8               Test
  #21 = Utf8               java/lang/Object
  #22 = Utf8               java/lang/System
  #23 = Utf8               out
  #24 = Utf8               Ljava/io/PrintStream;
  #25 = Utf8               java/io/PrintStream
  #26 = Utf8               println
  #27 = Utf8               (F)V
{
  Test();
    descriptor: ()V
    flags:
    Code:
      stack=1, locals=1, args_size=1
         0: aload_0
         1: invokespecial #1                  // Method java/lang/Object."<init>":()V
         4: return
      LineNumberTable:
        line 1: 0

  public static void main(java.lang.String[]);
    descriptor: ([Ljava/lang/String;)V
    flags: ACC_PUBLIC, ACC_STATIC
    Code:
      stack=2, locals=3, args_size=1
         0: fconst_0
         1: fstore_1
         2: iconst_1
         3: istore_2
         4: iload_2
         5: bipush        10
         7: if_icmpgt     20
        10: fload_1
        11: fconst_1
        12: fadd
        13: fstore_1
        14: iinc          2, 1
        17: goto          4
        20: getstatic     #2                  // Field java/lang/System.out:Ljava/io/PrintStream;
        23: fload_1
        24: invokevirtual #3                  // Method java/io/PrintStream.println:(F)V
        27: return
      LineNumberTable:
        line 3: 0
        line 4: 2
        line 5: 10
        line 4: 14
        line 7: 20
        line 8: 27
      StackMapTable: number_of_entries = 2
        frame_type = 253 /* append */
          offset_delta = 4
          locals = [ float, int ]
        frame_type = 250 /* chop */
          offset_delta = 15
}
SourceFile: "Test.java"
```

# 1-4

SICPの問題にもあったが、インタプリタは逐一アセンブルするため、コンパイラのような最適化を行えない。

