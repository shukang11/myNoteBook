#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

int token; // current token
int debug = 1;

// instructions
enum { LEA ,IMM ,JMP ,CALL,JZ  ,JNZ ,ENT ,ADJ ,LEV ,LI  ,LC  ,SI  ,SC  ,PUSH,
       OR  ,XOR ,AND ,EQ  ,NE  ,LT  ,GT  ,LE  ,GE  ,SHL ,SHR ,ADD ,SUB ,MUL ,DIV ,MOD ,
       OPEN,READ,CLOS,PRTF,MALC,MSET,MCMP,EXIT };

/*
+------------------+
|    stack   |     |      high address
|    ...     v     |
|                  |
|                  |
|                  |
|                  |
|    ...     ^     |
|    heap    |     |
+------------------+
| bss  segment     |
+------------------+
| data segment     |
+------------------+
| text segment     |      low address
+------------------+

*/
int *text, // text segment
    *data, // data segment
    *stack; // stack
int poolsize; // default size of text/data/stack

int *pc, *bp, *sp, ax, cycle; // virtual machine registers
// PC 程序计数器，它存放的是一个内存地址，该地址中存放着 下一条 要执行的计算机指令。
// SP 指针寄存器，永远指向当前的栈顶。注意的是由于栈是位于高地址并向低地址增长的，所以入栈时 SP 的值减小。
// BP 基址指针。也是用于指向栈的某些位置，在调用函数时会使用到它。
// AX 通用寄存器，我们的虚拟机中，它用于存放一条指令执行后的结果。

void next() {
    token = 0;
}

void expression(int level) {

}

void statement() {

}
int eval() {
    int op, *tmp;
    cycle ++;
    while (1) {
        cycle ++;
        op = *pc++;
        // print debug info
        if (debug) {
            printf("%d> %.4s", cycle,
                   & "LEA ,IMM ,JMP ,CALL,JZ  ,JNZ ,ENT ,ADJ ,LEV ,LI  ,LC  ,SI  ,SC  ,PUSH,"
                   "OR  ,XOR ,AND ,EQ  ,NE  ,LT  ,GT  ,LE  ,GE  ,SHL ,SHR ,ADD ,SUB ,MUL ,DIV ,MOD ,"
                   "OPEN,READ,CLOS,PRTF,MALC,MSET,MCMP,EXIT"[op * 5]);
            if (op <= ADJ)
                printf(" %d\n", *pc);
            else
                printf("\n");
        }
        if (op == IMM) ax = *pc++;
        else if (op == LC) {ax = *(char *)ax;} // 载入，要求 ax 中是地址
        else if (op == LI) {ax = *(int *)ax;}
        else if (op == SC) {*(char *)sp++ = ax;}
        else if (op == SI) {*(int *)sp++ = ax;}

        else if (op == PUSH) {*--sp = ax;} // 入栈
        else if (op == JMP) {pc = (int *)pc;} // 将下一条指令载入
        else if (op == JZ) { pc = ax ? pc + 1 : (int *)*pc; }
        else if (op == JNZ) { pc = ax ? (int *)*pc : pc + 1; }

        else if (op == CALL) {*--sp = (int)(pc+1); pc = (int *)*pc;} // call subroutine
        //else if (op == RET)  {pc = (int *)*sp++;}   // return from subroutine;
        else if (op == ENT) { *--sp = (int)bp; bp = sp; sp = sp - *pc++;} // 即保存当前的栈指针，同时在栈上保留一定的空间，用以存放局部变
        else if (op == ADJ) { sp = sp + *pc++; } // add     esp, 12 将调用子函数时压入栈中的数据清除
        else if (op == LEV) { sp = bp; bp = (int *)*sp++; pc = (int *)*sp++; } // 本质上这个指令并不是必需的，只是我们的指令集中并没有 POP 指令。并且三条指令写来比较麻烦且浪费空间，所以用一个指令代替
        /*
sub_function(arg1, arg2, arg3);

|    ....       | high address
+---------------+
| arg: 1        |    new_bp + 4
+---------------+
| arg: 2        |    new_bp + 3
+---------------+
| arg: 3        |    new_bp + 2
+---------------+
|return address |    new_bp + 1
+---------------+
| old BP        | <- new BP
+---------------+
| local var 1   |    new_bp - 1
+---------------+
| local var 2   |    new_bp - 2
+---------------+
|    ....       |  low address
        */
       else if (op == LEA) {ax = (int)(bp + *pc++);}

        else if (op == OR)  {ax = *sp++ | ax;}
        else if (op == XOR) {ax = *sp++ ^ ax;}
        else if (op == AND) {ax = *sp++ & ax;}
        else if (op == EQ)  {ax = *sp++ == ax;}
        else if (op == NE)  {ax = *sp++ != ax;}
        else if (op == LT)  {ax = *sp++ < ax;}
        else if (op == LE)  {ax = *sp++ <= ax;}
        else if (op == GT)  {ax = *sp++ >  ax;}
        else if (op == GE)  {ax = *sp++ >= ax;}
        else if (op == SHL) {ax = *sp++ << ax;}
        else if (op == SHR) {ax = *sp++ >> ax;}
        else if (op == ADD) {ax = *sp++ + ax;}
        else if (op == SUB) {ax = *sp++ - ax;}
        else if (op == MUL) {ax = *sp++ * ax;}
        else if (op == DIV) {ax = *sp++ / ax;}
        else if (op == MOD) {ax = *sp++ % ax;}

        else if (op == EXIT) { printf("exit(%d)", *sp); return *sp;}
        else if (op == OPEN) { ax = open((char *)sp[1], sp[0]); }
        else if (op == CLOS) { ax = close(*sp);}
        else if (op == READ) { ax = read(sp[2], (char *)sp[1], *sp); }
        else if (op == PRTF) { tmp = sp + pc[1]; ax = printf((char *)tmp[-1], tmp[-2], tmp[-3], tmp[-4], tmp[-5], tmp[-6]); }
        else if (op == MALC) { ax = (int)malloc(*sp);}
        else if (op == MSET) { ax = (int)memset((char *)sp[2], sp[1], *sp);}
        else if (op == MCMP) { ax = memcmp((char *)sp[2], (char *)sp[1], *sp);}
        else {
            printf("unknown instruction:%d\n", op);
            return -1;
        }
    }
}

int main(int argc, char const *argv[])
{

    poolsize = 256 * 1024; // arbitarary size
    
    // allock memory
    if (!(text = malloc(poolsize))) {
        printf("could not malloc(%d) for text area\n", poolsize);
        return -1;
    }
    if (!(data = malloc(poolsize))) {
        printf("could not malloc(%d) for data area\n", poolsize);
        return -1;
    }
    if (!(stack = malloc(poolsize))) {
        printf("could not malloc(%d) for stack area\n", poolsize);
        return -1;
    }
    memset(text, 0, poolsize);
    memset(data, 0, poolsize);
    memset(stack, 0, poolsize);
    
    if (!(sp = malloc(poolsize))) {
        printf("could not malloc(%d) for sp area\n", poolsize);
        return -1;
    }
    memset(sp, 0, poolsize);

    ax = 0;
    int i = 0;
    text[i++] = IMM;
    text[i++] = 10;
    text[i++] = PUSH;
    text[i++] = IMM;
    text[i++] = 20;
    text[i++] = MUL;
    text[i++] = PUSH;
    text[i++] = EXIT;
    pc = text;
    int result = eval();
    printf("%d", result);
    return 0;
}
