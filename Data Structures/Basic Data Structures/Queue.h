#pragma once
#include <iostream>

template <typename T>
class Queue
{
private:
	T* arr_;
	size_t capacity_;
	size_t front_;
	size_t back_;
	size_t size_;

public:
	Queue() : capacity_(4), front_(0), back_(0), size_(0)
	{
		arr_ = new T[capacity_];
	}

	Queue(const size_t sz) : capacity_(sz), front_(0), back_(0), size_(0)
	{
		arr_ = new T[capacity_];
	}

	~Queue()
	{
		delete[] arr_;
	}

	size_t size() const
	{
		return size_;
	}

	bool empty() const
	{
		return size_ == 0;
	}

	void enqueue(const T& data)
	{
		if (size_ == capacity_)
		{
			T* temp = new T[2 * capacity_];

			for (size_t i = 0; i < size_; i++)
			{
				temp[i] = arr_[(front_ + i) % capacity_];
			}

			delete[] arr_;
			arr_ = temp;
			front_ = 0;
			back_ = size_;
			capacity_ *= 2;
		}

		arr_[back_] = data;
		back_ = (back_ + 1) % capacity_;
		size_++;
	}

	void dequeue()
	{
		if (size_ == 0)
		{
			return;
		}

		front_ = (front_ + 1) % capacity_;
		size_--;
	}

	T front() const
	{
		if (empty())
		{
			return T();
		}

		return arr_[front_];
	}

	T back() const
	{
		if (empty())
		{
			return T();
		}

		return arr_[(back_ + capacity_ - 1) % capacity_];
	}
};
