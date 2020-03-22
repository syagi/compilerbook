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

## 少し重いコード
```
#include <stdio.h>

int main(void){
  int i;
  float sum = 0;
  for(i=0; i<=10; i++){
    sum += i;
    printf("%f\n",sum);
  }
}
```

### x86 gcc
```
.LC1:
        .string "%f\n"
main:
        push    rbp
        mov     rbp, rsp
        sub     rsp, 16
        pxor    xmm0, xmm0
        movss   DWORD PTR [rbp-8], xmm0
        mov     DWORD PTR [rbp-4], 0
        jmp     .L2
.L3:
        cvtsi2ss        xmm0, DWORD PTR [rbp-4]
        movss   xmm1, DWORD PTR [rbp-8]
        addss   xmm0, xmm1
        movss   DWORD PTR [rbp-8], xmm0
        cvtss2sd        xmm0, DWORD PTR [rbp-8]
        mov     edi, OFFSET FLAT:.LC1
        mov     eax, 1
        call    printf
        add     DWORD PTR [rbp-4], 1
.L2:
        cmp     DWORD PTR [rbp-4], 10
        jle     .L3
        mov     eax, 0
        leave
        ret
```

### arm
```
.LC0:
        .ascii  "%f\012\000"
main:
        push    {r4, fp, lr}
        add     fp, sp, #8
        sub     sp, sp, #12
        mov     r3, #0
        str     r3, [fp, #-20]    @ float
        mov     r3, #0
        str     r3, [fp, #-16]
        b       .L2
.L3:
        ldr     r0, [fp, #-16]
        bl      __aeabi_i2f
        mov     r3, r0
        mov     r1, r3
        ldr     r0, [fp, #-20]    @ float
        bl      __aeabi_fadd
        mov     r3, r0
        str     r3, [fp, #-20]    @ float
        ldr     r0, [fp, #-20]    @ float
        bl      __aeabi_f2d
        mov     r3, r0
        mov     r4, r1
        mov     r2, r3
        mov     r3, r4
        ldr     r0, .L5
        bl      printf
        ldr     r3, [fp, #-16]
        add     r3, r3, #1
        str     r3, [fp, #-16]
.L2:
        ldr     r3, [fp, #-16]
        cmp     r3, #10
        ble     .L3
        mov     r3, #0
        mov     r0, r3
        sub     sp, fp, #8
        pop     {r4, fp, pc}
.L5:
        .word   .LC0
```

### win
```
_DATA   SEGMENT
$SG4507 DB        '%f', 0aH, 00H
_DATA   ENDS
_DATA   SEGMENT
COMM    ?_OptionsStorage@?1??__local_stdio_printf_options@@9@9:QWORD                                                    ; `__local_stdio_printf_options'::`2'::_OptionsStorage
_DATA   ENDS

_sum$ = -8                                          ; size = 4
_i$ = -4                                                ; size = 4
_main   PROC
        push    ebp
        mov     ebp, esp
        sub     esp, 8
        xorps   xmm0, xmm0
        movss   DWORD PTR _sum$[ebp], xmm0
        mov     DWORD PTR _i$[ebp], 0
        jmp     SHORT $LN4@main
$LN2@main:
        mov     eax, DWORD PTR _i$[ebp]
        add     eax, 1
        mov     DWORD PTR _i$[ebp], eax
$LN4@main:
        cmp     DWORD PTR _i$[ebp], 10                    ; 0000000aH
        jg      SHORT $LN3@main
        cvtsi2ss xmm0, DWORD PTR _i$[ebp]
        addss   xmm0, DWORD PTR _sum$[ebp]
        movss   DWORD PTR _sum$[ebp], xmm0
        cvtss2sd xmm0, DWORD PTR _sum$[ebp]
        sub     esp, 8
        movsd   QWORD PTR [esp], xmm0
        push    OFFSET $SG4507
        call    _printf
        add     esp, 12                             ; 0000000cH
        jmp     SHORT $LN2@main
$LN3@main:
        xor     eax, eax
        mov     esp, ebp
        pop     ebp
        ret     0
_main   ENDP

___local_stdio_printf_options PROC                  ; COMDAT
        push    ebp
        mov     ebp, esp
        mov     eax, OFFSET ?_OptionsStorage@?1??__local_stdio_printf_options@@9@9 ; `__local_stdio_printf_options'::`2'::_OptionsStorage
        pop     ebp
        ret     0
___local_stdio_printf_options ENDP

__Stream$ = 8                                     ; size = 4
__Format$ = 12                                      ; size = 4
__Locale$ = 16                                      ; size = 4
__ArgList$ = 20                               ; size = 4
__vfprintf_l PROC                                 ; COMDAT
        push    ebp
        mov     ebp, esp
        mov     eax, DWORD PTR __ArgList$[ebp]
        push    eax
        mov     ecx, DWORD PTR __Locale$[ebp]
        push    ecx
        mov     edx, DWORD PTR __Format$[ebp]
        push    edx
        mov     eax, DWORD PTR __Stream$[ebp]
        push    eax
        call    ___local_stdio_printf_options
        mov     ecx, DWORD PTR [eax+4]
        push    ecx
        mov     edx, DWORD PTR [eax]
        push    edx
        call    ___stdio_common_vfprintf
        add     esp, 24                             ; 00000018H
        pop     ebp
        ret     0
__vfprintf_l ENDP

__Result$ = -8                                      ; size = 4
__ArgList$ = -4                               ; size = 4
__Format$ = 8                                     ; size = 4
_printf PROC                                          ; COMDAT
        push    ebp
        mov     ebp, esp
        sub     esp, 8
        lea     eax, DWORD PTR __Format$[ebp+4]
        mov     DWORD PTR __ArgList$[ebp], eax
        mov     ecx, DWORD PTR __ArgList$[ebp]
        push    ecx
        push    0
        mov     edx, DWORD PTR __Format$[ebp]
        push    edx
        push    1
        call    ___acrt_iob_func
        add     esp, 4
        push    eax
        call    __vfprintf_l
        add     esp, 16                             ; 00000010H
        mov     DWORD PTR __Result$[ebp], eax
        mov     DWORD PTR __ArgList$[ebp], 0
        mov     eax, DWORD PTR __Result$[ebp]
        mov     esp, ebp
        pop     ebp
        ret     0
_printf ENDP
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

