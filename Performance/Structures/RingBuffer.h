//
// Created by Timothy Coelho on 6/27/24.
//

#ifndef LIBRARY_OF_ALEXANDRIA_CPP_RINGBUFFER_H
#define LIBRARY_OF_ALEXANDRIA_CPP_RINGBUFFER_H
#include <util.h>

#include <string>
#include <iostream>
#include <vector>

template <typename T>
class RingBuffer
{
private:
	T *buffer_;
	size_t head_ = 0; //write pointer
	size_t tail_ = 0; //read pointer
	size_t capacity_;

public:
	explicit RingBuffer(const size_t sz)
	{
		buffer_ = new T[sz];
		capacity_ = sz;
	}

	~RingBuffer()
	{
		delete[] buffer_;
	}

	void push_back(const T data)
	{
		buffer_[head_] = data;

		if (head_ == capacity_ - 1)
		{
			head_ = 0;
		}
		else
		{
			head_++;
		}
	}

	T top()
	{
		T res = buffer_[tail_];

		if (tail_ == capacity_ - 1)
		{
			tail_ = 0;
		}
		else
		{
			tail_++;
		}

		return res;
	}

	[[nodiscard]] size_t size() const
	{
		return capacity_;
	}

	void clear()
	{
		memset(buffer_, 0, capacity_ * sizeof(T));
	}

	T operator[](const size_t iter)
	{
		if (iter < capacity_)
		{
			return buffer_[iter];
		}

		return NULL;
	}

	void print_top()
	{
		std::cout << this->top() << '\n';
	}
};

#endif //LIBRARY_OF_ALEXANDRIA_CPP_RINGBUFFER_H
