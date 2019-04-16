#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int *text, // text segment
    *old_text,  // dump text segment
    *stack; // stack
char *datasegment; // sdata segment

int *pc; // 程序计数器
int *sp; // 指针寄存器
int *bp; // 基址指针
int ax;// 通用寄存器

int cycle;

enum { IMM ,PUSH, 
    ADD ,SUB ,MUL ,DIV,
    EXIT
};

int eval() {
    int op;
    while (1) {
        op =  *pc++;
        cycle ++;
        printf("%d> %.4s ax=%d  *sp = %d\n", cycle,
                   & "IMM ,PUSH,"
                   "ADD ,SUB ,MUL ,DIV ,"
                   "EXIT"[op * 5], ax, *sp);
        if (op == IMM) { // 将值移动到通用寄存器MOV(tar sor)
            ax = *pc++;

        } else if (op == PUSH) { // sp 的入栈是减小的，将值入栈
            *--sp = ax;
            
        // 操作数
        } else if (op == ADD) { // +
            ax = *sp++ + ax;
        } else if (op == SUB) { // -
            ax = *sp++ - ax;
        } else if (op == DIV) { // /
            ax = *sp++ / ax;
        } else if (op == MUL) { // *
            ax = *sp++ * ax;

        // 系统操作
        } else if (op == EXIT) {
            cout << "exit(" << *sp << ")" << endl;
            return *sp;
        }
    }
}

int main() {
    int poolsize = 1024 * 256;
    // alloc
    text = (int *)malloc(poolsize);
    old_text = (int *)malloc(poolsize);
    stack = (int *)malloc(poolsize);
    datasegment = (char *)malloc(poolsize);

    memset(text, 0, poolsize);
    memset(old_text, 0, poolsize);
    memset(stack, 0, poolsize);
    memset(datasegment, 0, poolsize);


    sp = (int *)malloc(poolsize);
    memset(sp, 0, poolsize);

    ax = 0;
    int i = 0;
    text[i++] = IMM;
    text[i++] = 10;
    text[i++] = PUSH;

    text[i++] = IMM;
    text[i++] = 20;
    text[i++] = ADD;
    text[i++] = PUSH;

    text[i++] = IMM;
    text[i++] = 20;
    text[i++] = ADD;
    text[i++] = PUSH;

    text[i++] = IMM;
    text[i++] = 30;
    text[i++] = SUB;
    text[i++] = PUSH;

    text[i++] = EXIT;
    pc = text;
    int result = eval();
    return 0;
}