#pragma once

#include <algorithm>
#include <cassert>
#include <iterator>

template <typename T>
class MyVector
{
private:
    T* data;
    size_t size;
    size_t capacity;

public:

    ~MyVector()
    {
        delete[] T;
    }

    void pop_back()
    {
        if (!size)
            return;

        data[size].~T();
        size--;
    }

};
