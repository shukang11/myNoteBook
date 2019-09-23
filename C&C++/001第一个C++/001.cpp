#include <iostream> // 引入
#include <string>
#include <limits>

using namespace std; // 使用命名空间

int main() {
    cout << "Hello  word"; // 输出语句
    /* 数据类型 */
    cout << "type : \t\t" << "************size************" << endl;
    cout << "bool :" << sizeof(bool);
    cout << "\t最大值: " << (numeric_limits<bool>::max)();
    cout << "\t最小值: " << (numeric_limits<bool>::min)() << endl;

    cout << "typedef : \t\t" << "************typedef************" << endl;
    typedef bool another_bool;
    typedef int another_int;
    another_int a = 11;
    cout << "another_int value:" << a;

    cout << "enum : \t\t" << "************enum************" << endl;
    enum Language {
        english,
        chinese,
        japanese
    };
    Language myl = japanese;
    cout << "Language: " << myl << endl;

    cout << "C++ 中的左值（Lvalues）和右值（Rvalues）" << endl;
    cout << "左值（lvalue）：指向内存位置的表达式被称为左值（lvalue）表达式。左值可以出现在赋值号的左边或右边。" << endl;
    cout << "右值（rvalue）：术语右值（rvalue）指的是存储在内存中某些地址的数值" << endl;
    return 0;
}