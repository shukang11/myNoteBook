#include <iostream>
#include <string>

using namespace std;

class People {
    public:
    int age;
    // 提供接口框架的纯虚函数
    virtual int getAge() = 0;
    void setAge(int newAge);

};

class Man: public People {
    public:
    void setAge(int newAge) {
        age = newAge;
    };
    int getAge() { return age/10; };
};

int main() {
    /* 
    面向对象的系统可能会使用一个抽象基类为所有的外部应用程序提供一个适当的、通用的、标准化的接口。然后，派生类通过继承抽象基类，就把所有类似的操作都继承下来。

    外部应用程序提供的功能（即公有函数）在抽象基类中是以纯虚函数的形式存在的。这些纯虚函数在相应的派生类中被实现。

    这个架构也使得新的应用程序可以很容易地被添加到系统中，即使是在系统被定义之后依然可以如此。
 */
    Man man;
    man.setAge(1444);
    cout << man.getAge() << endl;
    return 0;
};