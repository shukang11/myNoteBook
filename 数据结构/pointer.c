#include <stdio.h>
/*
int p; //这是一个普通的整型变量  
int *p; //首先从P 处开始,先与*结合,所以说明P 是一个指针,然后再与int 结合,说明指针所指向的内容的类型为int 型.所以P是一个返回整型数据的指针  
int p[3]; //首先从P 处开始,先与[]结合,说明P 是一个数组,然后与int 结合,说明数组里的元素是整型的,所以P 是一个由整型数据组成的数组  
int *p[3]; //首先从P 处开始,先与[]结合,因为其优先级比*高,所以P 是一个数组,然后再与*结合,说明数组里的元素是指针类型,然后再与int 结合,说明指针所指向的内容的类型是整型的,所以P 是一个由返回整型数据的指针所组成的数组  
int (*p)[3]; //首先从P 处开始,先与*结合,说明P 是一个指针然后再与[]结合(与"()"这步可以忽略,只是为了改变优先级),说明指针所指向的内容是一个数组,然后再与int 结合,说明数组里的元素是整型的.所以P 是一个指向由整型数据组成的数组的指针  
int **p; //首先从P 开始,先与*结合,说是P 是一个指针,然后再与*结合,说明指针所指向的元素是指针,然后再与int 结合,说明该指针所指向的元素是整型数据.由于二级指针以及更高级的指针极少用在复杂的类型中,所以后面更复杂的类型我们就不考虑多级指针了,最多只考虑一级指针.  
int p(int); //从P 处起,先与()结合,说明P 是一个函数,然后进入()里分析,说明该函数有一个整型变量的参数,然后再与外面的int 结合,说明函数的返回值是一个整型数据  
Int (*p)(int); //从P 处开始,先与指针结合,说明P 是一个指针,然后与()结合,说明指针指向的是一个函数,然后再与()里的int 结合,说明函数有一个int 型的参数,再与最外层的int 结合,说明函数的返回类型是整型,所以P 是一个指向有一个整型参数且返回类型为整型的函数的指针  
int *(*p(int))[3]; //可以先跳过,不看这个类型,过于复杂从P 开始,先与()结合,说明P 是一个函数,然后进入()里面,与int 结合,说明函数有一个整型变量参数,然后再与外面的*结合,说明函数返回的是一个指针
    ,然后到最外面一层,先与[]结合,说明返回的指针指向的是一个数组,然后再与*结合,说明数组里的元素是指针,然后再与int 结合,说明指针指向的内容是整型数据.所以P 是一个参数为一个整数据且返回一个指向由整型指针变量组成的数组的指针变量的函数. 
*/
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

void point001() {
    int a = 11;
    int *p; // 说明指针指向的内容是一个 int 类型
    p = &a;
    printf("p 的地址是 %p \n", &p);
    printf("p 的值是 %d \n", *p);
    // char c = 's';
    // p = &c;
    // printf("*p =  %c \n", *p);
}

/// 数组 内容是 int
void pointer002() {
    int p[3] = {1, 2, 3};
    p[1] = 11;
    for(size_t i = 0; i < sizeof(p)/sizeof(p[0]); i++) {
        int pi = p[i];
        printf("%d \n", pi);
    }
}

// int *p[3]; 数组里的元素是指针类型，指针指向的类型是 int 类型
void pointer003() {
    int a, b, c;
    a = 1; 
    b = 3;
    c = 5;
    int *p[3];
    p[0] = &a;
    p[1] = &b;
    p[2] = &c;
    for(size_t i = 0; i < sizeof(p)/sizeof(p[0]); i++) {
        int *pi = p[i];
        printf("%d \n", *pi);
    }
}

void demo3() {
    int array[5] = {0};
    int *ptr = array;
    for(int i = 0; i < sizeof(array)/sizeof(array[0]); i ++) {
        (*ptr)++; // 使array[i]的值 += 1
        ptr++; // 游标向下继续走，移动到下一个目标
    }
    for(size_t i = 0; i < sizeof(array)/sizeof(array[0]); i++)
    {
        printf("%d \n", array[i]);
    }
    
}

void demo4() {
    char a[20] = "You_are_a_girl";
    printf("size of a is %lu \n", sizeof(a));
    printf("size of a[0] is %lu \n", sizeof(a[0]));
    char *p = a;
    printf("ptr = %c \n", *p); // 指向*p 的指针位置
    p ++; // p 移动位置
    printf("ptr = %c \n", *p); // 指向*p 的指针位置
}

int main(int argc, char const *argv[])
{
    // printPointer();
    // point001();
    // pointer002();
    // pointer003();
    // demo3();
    demo4();
    return 0;
}
