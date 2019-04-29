#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int *text, // text segment
    *old_text,  // dump text segment
    *stack; // stack
char *datasegment; // sdata segment

int *pc; // 程序计数器 存放指令
int *sp; // 指针寄存器 寄存数据
int *bp; // 基址指针
int ax;// 通用寄存器

int cycle;

enum { IMM ,PUSH, JMP ,JZ  ,JNZ ,CALL,ENT ,ADJ ,
    ADD ,SUB ,MUL ,DIV ,
    EXIT
};

int eval() {
    int op;
    while (1) {
        op =  *pc++;
        cycle ++;
        printf("%d> %.4s ax=%d  *sp = %d\n", cycle,
                   & "IMM ,PUSH,JMP ,JZ  ,JNZ ,CALL,ENT ,ADJ ,"
                   "ADD ,SUB ,MUL ,DIV ,"
                   "EXIT"[op * 5], ax, *sp);
        if (op == IMM) { // 将值移动到通用寄存器MOV(tar sor)
            ax = *pc++;

        } else if (op == PUSH) { // sp 的入栈是减小的，将值入栈
            *--sp = ax;
        // 跳转指令 JMP 
        } else if (op == JMP) {
            pc = (int *)*pc; // 将当前指令设置为指定的地址 (也就是下一条指令设置为指定的)
        } else if (op == JZ) { // （ax）为零或不为零情况下的跳转
            pc = ax ? pc + 1 : (int *)*pc;
        } else if (op == JNZ) {
            pc = ax ? (int *)*pc : pc + 1;
        } else if (op == CALL) {
            /*
             为什么不能直接使用 JMP 指令呢？原因是当我们从子函数中返回时，
             程序需要回到跳转之前的地方继续运行，这就需要事先将这个位置信息存储起来。
             反过来，子函数要返回时，就需要获取并恢复这个信息。因此实际中我们将 PC 保存在栈中
            */
           *--sp = (int)(pc + 1);
           pc = (int *)*pc;
        // } else if (op == RET)  {pc = (int *)*sp++;} 

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