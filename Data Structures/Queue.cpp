#include <iostream>

template <typename T>
class Queue
{
private:
    T* arr_;
    int front_;
    int back_;
    int size_;

public:
    Queue()
    {
        arr_ = new T[4];
        front_ = 0;
        back_ = 0;
        size_ = 0;
    }

    Queue(uint32_t sz)
    {
        arr_ = new T[sz];
        front_ = 0;
        back_ = 0;
        size_ = 0;
    }

    int size() const
    {
        return size_;
    }

    bool empty() const
    {
        return size_ == 0;
    }

    void enqueue(T data)
    {
        if (size_ == 4)
        {
            T* temp = new T[2 * 4];
            for (int i = 0; i < 4; i++)
            {
                temp[i] = arr_[i];
            }
            delete[] arr_;
            arr_ = temp;
        }
        arr_[back_] = data;
        back_ = (back_ + 1) % 4;
        size_++;
    }

    void dequeue()
    {
        if (size_ == 0)
        {
            return;
        }
        front_ = (front_ + 1) % 4;
        size_--;
    }

    T front() const
    {
        return arr_[front_];
    }
};
