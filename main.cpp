#include "smartPtr.h"
#include <iostream>

unique_ptr getPtr(int a)
{
    return unique_ptr::make_unique(a);
}

int main()
{
    auto ptr = getPtr(1);

}