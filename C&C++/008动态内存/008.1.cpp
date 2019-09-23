#include <iostream>
#include <string>

using namespace std;
/* 栈：在函数内部声明的所有变量都将占用栈内存。 */
/* 堆：这是程序中未使用的内存，在程序运行时可用于动态分配内存。 */

void test01() {
    double* pvalue = NULL; // 初始化一个 NULL 的指针
    /* new 与 malloc() 函数相比，其主要的优点是，new 不只是分配了内存，它还创建了对象。 */
    if (!(pvalue = new double)) { 
        cout << "Error: out of memory" << endl;
    }
    *pvalue = 100.3;
    cout << *pvalue << endl;
    delete pvalue; // 释放 pvalue 所指向的内存
};

void test02() { // 一维数组
    int* pvalue = NULL;
    pvalue = new int[20];
    pvalue[1] = 11;
    cout << pvalue[1] << endl;
    delete [] pvalue;
};

void test03() {// 二维数组
    int **array;
    int m = 4;
    int n = 3;
    array = new int *[m];
    for (size_t i = 0; i < m; i++)
    {
        array[i] = new int [n];
    }
    for (size_t i = 0; i < m; i++)
    {
        delete [] array[i];
    }
    delete [] array;
};

class Box {
    public:
    Box() { cout << "调用构造函数" << endl; }
    ~Box() { cout << "调用析构函数" << endl; }
};

void test04() {
    Box* boxes = new Box[4];
    delete [] boxes;
};

int main() {
    test01();
    test02();
    test03();
    test04();
    return 0;
};