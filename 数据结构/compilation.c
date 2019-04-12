#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

int token; // current token
int debug = 1;

// instructions
enum { 
    IMM, LC, LI, SC, SI,
    OR  ,XOR ,AND ,EQ  ,NE  ,LT  ,GT  ,LE  ,GE  ,SHL ,SHR ,ADD ,SUB ,MUL ,DIV ,MOD,
    PUSH, EXIT
};

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

        if (op == IMM) ax = *pc++;
        else if (op == LC) {ax = *(char *)ax;}
        else if (op == LI) {ax = *(int *)ax;}
        else if (op == SC) {*(char *)sp++ = ax;}
        else if (op == SI) {*(int *)sp++ = ax;}

        else if (op == PUSH) {*--sp = ax;} // 入栈


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
