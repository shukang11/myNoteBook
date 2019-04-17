#include <iostream>
#include <string>

using namespace std;

// 多态

class People {
    protected:
    int age, height;
    string name;
    bool isMan;

    public:
    People(string a, int b, int c, bool d) {
        cout << "on init" << a << endl;
        name = a;
        age = b;
        height = c;
        isMan = d;
    };

    void reportInfo() {
        cout << name << " " << (isMan ? "Boy" : "Girl") << " " << age << " " << height << endl;
    };
};

class Boy: public People {
    public:
    Boy(string a, int b, int c, bool d=true):People(a, b, c, d) {};
};

int main() {
    People tom = Boy("tom", 11, 110);
    tom.reportInfo();
};