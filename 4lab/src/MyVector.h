#pragma once

#include <algorithm>
#include <cassert>
#include <iterator>

template <typename T>
class MyVector
{
private:
    T* data;
    int size;
    int capacity;

public:

  /*  class iterator
    {
    private:
        it;

    public:

        iterator()
        {

        }

      T operator ++ ()


    };*/

    using iterator = T*;
    using const_iterator = T*;
    using allocator_type = T;


    MyVector() :
        data{ nullptr },
        size{ 0 },
        capacity{ 0 }
    {}
    
    MyVector(int num)
    {
        if (num <= 0)
            throw std::exception("[ERROR]");

        size = num;
        capacity = num * 2;

        data = new T[sum];

        for (int i = 0; i < size; i++)
        {
            data[i] = 0;
        }
    }

    MyVector(int num, T info)
    {
        if (num <= 0)
            throw std::exception("[ERROR]");

        size = num;
        capacity = num * 2;

        data = new T[num];

        for (int i = 0; i < size; i++)
        {
            data[i] = info;
        }
    }

    ~MyVector()
    {
        size = 0;
        capacity = 0;
    }

    iterator& operator++ () { return data++; }
    iterator& operator-- () { return data--; }

    const MyVector& operator[] (const int i) { return data[i]};

    inline typename iterator begin() { return data; }

    inline typename iterator end() { return data + size;  }

    void pop_back()
    {
        if (!size)
            return;

       
    }

};
