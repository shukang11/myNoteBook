#include <iostream>
#include <string>

using namespace std;

class Say {
    public:
    // 重载函数
    void say(int i) {
        cout << "say int " << i << endl;
    };

    void say(double i) {
        cout << "say double " << i << endl;
    };

    void say(char i[]) {
        cout << "say char " << i << endl;
    };

};

class Lenth {
    private:
    int length;
    public:
    void setLength(int l) {
        length = l;
    };
    int getLengh() { return this->length; };

    Lenth operator+(const Lenth& a) { // 重载运算符。使用了引用变量
        Lenth newl = Lenth();
        newl.length = this->length + a.length;
        return newl;
    }
};

int main() {
    Say say = Say();
    say.say(5);
    say.say(10.33);
    char c[] = "Hello C++";
    say.say(c);

    Lenth l = Lenth();
    Lenth l2 = Lenth();
    l.setLength(1);
    l2.setLength(8);
    Lenth l3 = l + l2;
    say.say(l3.getLengh());
};