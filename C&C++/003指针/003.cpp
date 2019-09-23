#include <iostream>
#include <string>
#include <ctime>

using namespace std;
void getSeconds(unsigned long *par);
double getAverage(int *arr, int size);

/* *访问值； & 访问地址 */
int main() {
    int var1;
    int var2[10];

    cout << "var1 地址 " << &var1 << endl;
    /*
    指针是一个变量，其值为另一个变量的地址，
    即，内存位置的直接地址。就像其他变量或常量一样，您必须在使用指针存储其他变量地址之前，对其进行声明
    */ 
    int var = 20; // 变量的声明
    int *ip; // 指针变量的声明
    ip = &var; // 在指针变量中存储 var 的地址
    cout << "var地址: " << ip << endl;
    cout << "var的值: " << *ip << endl;

    // Null 指针
    int *ptr = NULL;
    if (ptr) {} 
    if (!ptr) {}
    cout << "ptr: " << ptr << endl;

    // 指针的算术运算
    const int MAX = 3;
    int ptrv2[MAX] = {10, 100, 1000};
    int *ptr2;
    ptr2 = ptrv2;
    for (int i = 0; i < MAX; i++) {
        cout << "Address of var[" << i << "] = ";
      cout << ptr2 << endl;
 
      cout << "Value of var[" << i << "] = ";
      cout << *ptr2 << endl;
 
      // 移动到下一个位置
      ptr2++;
    }

    /* 指向指针的指针（多级间接寻址） */
    int c = 10;
    int *cp;
    int **cpp;
    cp = &c;
    cpp = &cp;
    // 使用 cpp 获取值
    cout << "var 值为 :" << c << endl;
    cout << "*ptr 值为:" << *cp << endl;
    cout << "**pptr 值为:" << **cpp << endl;

    /* 传递指针给函数 */ 
    unsigned long sec;
    getSeconds(&sec);
    cout << "sec 值为 :" << sec << endl;

    int d[5] = {1000, 2, 5, 3, 10};
    double davg;
    davg = getAverage(d, sizeof(d) / sizeof(d[0]));
    cout << "davg 值为:" << davg << endl;

    return 0;
}

void getSeconds(unsigned long *par) {
    *par = time(NULL);
}

double getAverage(int *arr, int size) {
    int sum = 0;
    double avg;
    for (int i = 0; i < size; i++)
    {
        sum += arr[i];
    }
    avg = double(sum) / size;
    return avg;
}