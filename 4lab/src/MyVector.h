#pragma once

#include <algorithm>
#include <cassert>
#include <iterator>
#include <iostream>

template <typename T>
class MyVector
{
private:
    T* data;
    size_t m_size;
    size_t m_capacity;

public:
    MyVector() :
        data{ nullptr },
        m_size{},
        m_capacity{}
    {}

    MyVector(int num)
    {
        if (num <= 0)
            throw std::exception("[ERROR]");

        m_size = num;
        m_capacity = num * 2;

        data = new T[m_capacity];

        for (int i = 0; i < m_size; i++)
        {
            data[i] = 0;
        }
    }

    MyVector(int num, T info)
    {
        if (num <= 0)
            throw std::exception("[ERROR]");

        m_size = num;
        m_capacity = num * 2;

        data = new T[m_capacity];

        for (int i = 0; i < m_size; i++)
        {
            data[i] = info;
        }
    }

    ~MyVector()
    {
        delete[] data;

        m_size = 0;
        m_capacity = 0;
    }

    friend std::ostream& operator << (std::ostream& out, const MyVector& p)
    {
        return out;
    }

    class iterator
    {
    private:
        T* it;

    public:

        iterator() :
            it{}
        {}

        iterator(T* cur) :
            it{ cur }
        {}

        bool operator!= (const iterator& iter) const { return it != iter.it; }

        iterator operator++(int) { return it++; }

    };
    /*
    @return The 0 pos of array
    */
    iterator begin() const { return data; }
    /*
    @return 1 pos after last element
    */
    iterator end() const { return data + m_size; }

    const T& operator[] (const int i) { return data[i]; };
    /*
    @return Get a position
    */
    T& at(int index)
    {
        if (index < 0 || index >(m_size - 1))
            throw std::exception("[ERROR]");

        else
            return at[index];
    }
    /*
        @brief Add an element
    */
    void push_back(T info)
    {
        if (m_capacity == m_size)
        {
            ++m_capacity *= 2;

            T* new_data = new T[m_capacity];

            for (size_t i = 0; i < m_size; i++)
            {
                new_data[i] = data[i];
            }

            delete[] data;

            data = new_data;

            data[m_size] = info;

            m_size++;
        }

        else
        {
            data[m_size] = info;

            m_size++;
        }
    }

    /*
        @brief delete an element
    */
    void pop_back()
    {
        if (!m_size)
            return;

        data[--m_size] = {};
    }

    size_t size() const { return m_size; }
    
};