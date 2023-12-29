// STL, 序列容器、关联容器
// 底层实现

// STL = 算法 + 迭代器 + 容器

// 1.迭代器iterator(重视迭代器的地位)
// 对所有容器遍历操作的封装, 提供给算法, 以实现解耦
// 重载了*,->,++等运算符, 使其与指针的使用方式相同
// 迭代器失效!! 对容器修改会使迭代器失效

// 2.序列容器
#pragma once
#include <cstring>
#include <iostream>
class vector
{
    // 内部为一个连续的内存数组
    // [start, ... , finish, ... , endOfStorage]
private:
    // 迭代器
    int* start;         // 起始位置
    int* finish;        // 有效元素的下一个位置
    int* endOfStorage;  // 空间末尾

public:
    // 左闭右开[), 迭代器
    int* begin() const {return start;}
    const int* cbegin() const {return start;}
    int* end() const {return finish;}
    vector()
    {
        start = new int[2];
        finish = start;
        endOfStorage = finish + 1;
    }
    vector(int n, int val)
    {
        start = new int[n];
        finish = start + n;
        endOfStorage = finish;
        for (auto it = begin(); it != end(); it++)
        {
            *it = val;
        }
    }
    // 三五法则
    ~vector() {delete[] start;}
    vector(const vector& other)
    {
        std::cout << "拷贝构造" << std::endl;
        start = new int[other.capacity()];
        memcpy(start, other.start, sizeof(int) * other.size());
        finish = start + other.size();
        endOfStorage = start + other.capacity();
    }
    vector& operator=(const vector& other)
    {
        if (this == &other) return *this;
        std::cout << "拷贝赋值" << std::endl;
        start = new int[other.capacity()];
        memcpy(start, other.start, sizeof(int) * other.size());
        finish = start + other.size();
        endOfStorage = start + other.capacity();
        return *this;
    }
    vector(vector&& other) noexcept
    {
        std::cout << "移动构造" << std::endl;
        start = other.start;
        finish = other.finish;
        endOfStorage = other.endOfStorage;
        other.start = nullptr;
        other.finish = nullptr;
        other.endOfStorage = nullptr;
    }
    vector& operator=(vector&& other) noexcept
    {
        std::cout << "移动赋值" << std::endl;
        if (this == &other) return *this;
        start = other.start;
        finish = other.finish;
        endOfStorage = other.endOfStorage;
        other.start = nullptr;
        other.finish = nullptr;
        other.endOfStorage = nullptr;
        return *this;
    }
    // 随机访问、修改-O(1)
    int& operator[](int index) const
    {
        return *(begin() + index);
    }
    // 扩容, 当finish与endOfStorage重合时
    int capacity() const
    {
        return endOfStorage - start;
    }
    int size() const
    {
        return end() - cbegin();
    }
    void reserve(int n)
    {
        if (n <= capacity()) return;
        int* tmp = new int[n];
        int tmpSize = size();
        memcpy(tmp, start, sizeof(int) * tmpSize);
        delete[] start;
        start = tmp;
        finish = start + tmpSize;
        endOfStorage = start + n;
    }
    void resize(int n)
    {
        finish = start + n;
    }
    // 尾部插入-平均O(1), 最坏O(n)
    void push_back(int val)
    {
        if (finish == endOfStorage) reserve(2 * capacity());
        *finish = val;
        finish++;
    }
    // 中间插入-平均O(n), 禁用
    void insert(int* pos, const int& val)
    {
        if (finish == endOfStorage) reserve(2 * capacity());
        for (auto it = end(); it != pos; it--)
        {
            *it = *(it - 1);
        }
        *pos = val;
        finish++;
    }
};