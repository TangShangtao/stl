#include <iostream>
// 左值, 可以取地址, 有内存空间且生命周期稳定
// 右值, 不可以取地址, 临时对象(将亡值)
// 返回值是右值(将亡值)

class A
{
public:
    int a = 0;
    A() {}
};
A getA()
{
    return A();
}


// 万能引用(T&& t 或 auto&& t), 实际上是一个模板推断
// 传入左值时, 推断为左值引用, 传入右值时, 推断为右值引用

template<typename T>
void print(T & t){
    std::cout << "左值" << std::endl;
}

template<typename T>
void print(T && t){
    std::cout << "右值" << std::endl;
}
// 万能引用+std::forward = 完美转发
// https://zhuanlan.zhihu.com/p/369203981
template<typename T>
void testForward(T && v){
    print(v);
    print(std::forward<T>(v));  
    print(std::move(v));        // 无论左右都强转为右值
}
// 为什么要完美转发？
// 函数1实现了对左值的处理逻辑(拷贝), 函数2实现了对右值的处理逻辑(移动)
// 但对于不确定是左值传入还是右值传入的情况，需要使用完美转发
// 根本目的---充分利用右值可以移动的属性，减少拷贝

// int main(int argc, char * argv[])
// {
//     // testForward(1);

//     // std::cout << "======================" << std::endl;

//     // int x = 1;
//     // testForward(x);
//     int x = 1;
// }