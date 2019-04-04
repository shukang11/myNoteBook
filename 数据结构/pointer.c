#include <stdio.h>

// 取址运算符
void printPointer() {
    /*
    可以得到对象的地址
    */
    int a, b;
    printf("a 的地址是： %p \n", &a);
    printf("b 的值是： %d \n", b);

    int c[2];
    printf("a[0] 的地址是: %p\n", &c[0]);
    printf("a[1] 的地址是: %p\n", &c[1]);
    printf("a[2] 的地址是: %p\n", &c[2]);
}

int main(int argc, char const *argv[])
{
    printPointer();
    return 0;
}
