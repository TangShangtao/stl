#pragma once
#include <cstring>
#include <iostream>
// 为什么要智能指针
// 1.传统指针诸多缺点: 忘记delete、delete[]还是delete, 何时delete

struct A
{
    int data[10];
    int val;
    A(int val) : val(val)
    {
        memset(&data, val, sizeof(int) * 10);
    }
};


class unique_ptr
{
private:
    A* ptr;

public:
    static unique_ptr make_unique(int val)
    {
        // 触发返回值优化, 不会拷贝该临时对象
        return unique_ptr(new A(val));
    }
    // auto ptr = unique_ptr(new A(val));
    explicit unique_ptr(A* ptr) : ptr(ptr) {}
    // 三五法则
    ~unique_ptr() {delete ptr;}
    // 独占语义, 只可移动不可拷贝
    unique_ptr(const unique_ptr& other) = delete;
    unique_ptr& operator=(const unique_ptr& other) = delete;
    unique_ptr(unique_ptr&& other) noexcept
    {
        std::cout << "移动构造" << std::endl;
        ptr = other.ptr;
        other.ptr = nullptr;
    }
    unique_ptr& operator=(unique_ptr&& other) noexcept
    {
        std::cout << "移动赋值" << std::endl;
        if (this == &other) return *this;
        ptr = other.ptr;
        other.ptr = nullptr;
        return *this;
    }
    A& operator*() const
    {
        return *ptr;
    }
    A* operator->() const
    {
        return ptr;
    }
    // 释放当前unique_ptr对其内部ptr的管理
    A* release()
    {
        auto tmp = ptr;
        ptr = nullptr;
        return tmp;
    }
    // 将当前unique_ptr内部ptr销毁, 若有, 则重置为一个新的ptr
    void reset(A* other=nullptr)
    {
        delete ptr;
        ptr = other;
    }
};