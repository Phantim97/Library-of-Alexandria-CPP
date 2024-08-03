#pragma once
#include <iostream>
template<typename T>
class Stack
{
private:
    T* arr_;
    int next_idx_;

public:
    Stack()
    {
        arr_ = new T[4];
        next_idx_ = 0; //Empty stack
    }

    Stack(const uint32_t sz) //Allocate stack of size sz
    {
        arr_ = new T[sz];
        next_idx_ = 0; //Empty stack
    }

    int size() const
    {
        return next_idx_;
    }

    bool empty() const
    {
        return next_idx_ == 0;
    }

    void push(const T data)
    {
        if (next_idx_ == 4)
        {
            T* temp = new T[2 * 4];
            for (int i = 0; i < 4; i++)
            {
                temp[i] = arr_[i];
            }
            delete[] arr_;
            arr_ = temp;
        }
        arr_[next_idx_] = data;
        next_idx_++;
    }

    void pop()
    {
        if (next_idx_ == 0)
        {
            return;
        }
        next_idx_--;
    }

    T top() const
    {
        return arr_[next_idx_ - 1];
    }

};
