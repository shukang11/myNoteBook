#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void test01() {
    string fileName = "afile.dat";
    // 写入
    char data[100];

    ofstream outfile;
    outfile.open(fileName);

    cout << "Write to the file" << endl;
    cout << "enter your name:";
    cin.getline(data, 100);

    // 写入
    outfile << data << endl;

    cout << "enter your age: ";
    cin >> data;
    cin.ignore();

    outfile << data << endl;

    outfile.close();

    // 读取数据
    ifstream infile;
    infile.open(fileName);

    infile >> data;
    cout << data << endl;
    infile.close();
};

void test02() {
    string fileName = "afile.dat";
    ifstream infile;
    // 定位到第10个字节
    infile.seekg(10);
    // 当前位置后移10字节
    infile.seekg(10, ios::cur);
    // 当前位置前移10字节
    // infile.seekg(10, ios::dec);
    infile.seekg(0, ios::end);
};

int main() {
    test01();
    return 0;
};