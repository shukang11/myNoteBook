#include <string>
#include <iostream>

using namespace std;
// 基本语法
// template <typename T> class ClassA;

// 定义了一个动态数组（列表）的模板类vector，它对于任意的元素类型都具有push_back和clear的操作
template <typename T>
class TempVector {
    public:
    void push_back(T const&);
    void clear();

    private:
    T* elements;
};

template <typename T> void TempVector<T>::clear() {
    cout << "in clear" << endl;
};

// 模板函数的调用格式是 函数模板名 < 模板参数列表 > ( 参数 )
template <typename T> T Add(T a, T b) {
    return a + b;
};

// 另一个例子
float data[1024];
template<typename T> T GetValue(int i) {
    return static_cast<T>(data[i]); // 转换数据
}

// 两个参数的
// 在部分推导、部分指定的情况下，编译器对模板参数的顺序是有限制的：先写需要指定的模板参数，再把能推导出来的模板参数放在后面
template <typename DstT, typename SrcT> DstT c_style_cast(SrcT v)	// 模板参数 DstT 需要人肉指定，放前面。
{
    return (DstT)(v);
}

// 特化
// 我们来做一个练习。我们有一些类型，然后你要用模板做一个对照表，让类型对应上一个数字
template <typename T> class TypeToID {
    public: 
    static int const ID = -1;
};
template <> class TypeToID<uint8_t> {
    public:
    static int const ID = 0;
};
template <> class TypeToID<float> {
    public:
    static int const ID = 0xF10A7;
};
template <> class TypeToID<void*> {
    public:
    static int const ID = 0x401d;
};

// eg.
struct A;
template <typename T> struct B;
template <typename T> struct X {
    typedef X<T> _A; // 编译器当然知道 X<T> 是一个类型。
    typedef X    _B; // X 等价于 X<T> 的缩写
    typedef T    _C; // T 不是一个类型还玩毛

    // ！！！注意我要变形了！！！
    class Y {
        typedef X<T>     _D;          // X 的内部，既然外部高枕无忧，内部更不用说了
        typedef X<T>::Y  _E;          // 嗯，这里也没问题，编译器知道Y就是当前的类型，
                                      // 这里在VS2015上会有错，需要添加 typename，
                                      // Clang 上顺利通过。
        typedef typename X<T*>::Y _F; // 这个居然要加 typename！
                                      // 因为，X<T*>和X<T>不一样哦，
                                      // 它可能会在实例化的时候被别的偏特化给抢过去实现了。
    };
    
    typedef A _G;                   // 嗯，没问题，A在外面声明啦
    typedef B<T> _H;                // B<T>也是一个类型
    typedef typename B<T>::type _I; // 嗯，因为不知道B<T>::type的信息，
                                    // 所以需要typename
    typedef B<int>::type _J;        // B<int> 不依赖模板参数，
                                    // 所以编译器直接就实例化（instantiate）了
                                    // 但是这个时候，B并没有被实现，所以就出错了
};

int main() {
    TempVector<int> intArray;
    intArray.clear();

    float result = Add<float>(11, 33);
    cout << result << endl;

    float r3 = GetValue<float>(0);

    int r4 = 0;
    float r5 = c_style_cast<float>(r4);

    cout  << "ID of uint8_t: " << TypeToID<uint8_t>::ID << endl;
    cout  << "ID of float: " << TypeToID<float>::ID << endl;
    cout  << "ID of void *: " << TypeToID<void *>::ID << endl;
};

// Ref:
// https://github.com/wuye9036/CppTemplateTutorial