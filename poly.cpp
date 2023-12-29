#include <iostream>
#include <memory>
using namespace std;

// 类A有vptr, 指向一个数组vtbl;
// vtbl中, index(虚函数符号a()的编号) -> val(虚函数真正的地址)
// A->a()等价于(*vptr)[0]()
class A
{
public:
    // 打印地址, 为偏移量0x1
    virtual void a() {cout << "A a()" << endl;}
    virtual void b() {cout << "A b()" << endl;}
    virtual void c() {cout << "A c()" << endl;}
    void d() {cout << "A d()" << endl;}
};

class B : public A
{
public:
    // 打印地址, 为偏移量0x1
    // virtual void a() {cout << "A a()" << endl;}
    void b() override {cout << "B b()" << endl;} 
    // virtual void c() {cout << "A c()" << endl;}
    virtual void d() {cout << "B d()" << endl;}
};

typedef long long u64;
typedef void(*func)();

// int main()
// {
//     B a;
//     u64* p = (u64*)&a;  // p为vptr
//     u64* arr = (u64*)*p;// arr为vtbl
//     func fa = (func)arr[0];
//     func fb = (func)arr[1];
//     func fc = (func)arr[2];
//     func fd = (func)arr[3];
//     fa();fb();fc();fd();
//     // printf("%p\n", fa);
// }