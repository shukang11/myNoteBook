#include <iostream> // 引入
#include <string>
#include <limits>

using namespace std;
static int global_int = 10;

// extern 是用来在另一个文件中声明一个全局变量或函数
extern void write_extern();

int main() {
    cout << "存储类定义 C++ 程序中变量/函数的范围（可见性）和生命周期" << endl;
    cout << "static 静态变量 分为局部静态变量和全局静态变量" << endl;
    static int const_int = 11;
    cout << "extern 存储类用于提供一个全局变量的引用，全局变量对所有的程序文件都是可见的" << endl;

    /* 数组 */
    int scores[3] = {1, 2, 0};
    double balance[] = {1.2, 2.2};
    balance[1] = 11.2;
    cout << scores[1] << endl;

    int indexPath[2][2] = {
        {1, 2},
        {3, 4}
    };
    cout << indexPath[0][1] << endl;

    /* 字符串 */
    char greeting[6] = {'h', 'e', 'l', 'l', 'o', '\0'};
    char greet[6];
    cout << greeting << endl;
    strcpy(greet, greeting);
    cout << greet << endl;

    string str1 = "Hello world";
    string str2;
    string str3;
    str2 = str1;
    int len = str2.size();
    str3 = str1 + str2;

}

// thread_local
//  变量在创建线程时创建，并在销毁线程时销毁。
/*
thread_local int x; // 命名空间下的全局变量

class X {
    static thread_local std::string s;
};
static thread_local std::string X::s; // X::s 需要被定义

void foo() {
    thread_local std::vector<int> v; // 本地变量
}
*/
