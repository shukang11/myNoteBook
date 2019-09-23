#include <iostream>
#include <string>

using namespace std;

class Man {
    public:
    int age;
    bool isBoy;
    string name;

    // 定义成员函数
    void setAge(int newAge);
    void changeName(string newName);
    bool isTeenage(void) {
        if (age <= 10) { return false; }
        if (age >= 20) { return false; }
        return true;
    }

    protected: // 在派生类中可以访问

    private:
    string secret;

    void setSecret(string secret) {
        secret = secret;
    }

    
};

void Man::changeName(string newName) {
    name = newName;
};

class Car {
    public:
    string name;
    Car(string n) { // 它会在每次创建类的新对象时执行。
    cout << "被调用了" << endl;
    name = n;
    }
    ~Car() {
        cout << "被释放了" << endl;
    }
};

class Box {
    public:
    Box(double l=2.0, double w=2.0, double d=5.0) {
        length = l;
        width = w;
        depth = d;
    };

    double Volumn() {
        return length * width * depth;
    }

    bool isBigerThan(Box b) {
        return this->Volumn() > b.Volumn();
    }
    private:
    double length;
    double width;
    double depth;
};

int main() {
    Man tom;
    tom.age = 11;
    tom.isBoy = true;
    tom.name = "Tom";
    tom.changeName("Nick");
    cout << tom.name << " " << tom.isTeenage() << endl;

    Car benz = Car("benz");
    cout << benz.name << endl;

    Box abox = Box(8.0, 5.0, 4.0);
    Box bbox = Box(8.0, 5.0, 2.0);
    bool is = abox.isBigerThan(bbox);
    cout << is << endl;

    return 0;
}