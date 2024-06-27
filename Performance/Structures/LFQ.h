//
// Created by Timothy Coelho on 6/27/24.
//

#ifndef LIBRARY_OF_ALEXANDRIA_CPP_LFQ_H
#define LIBRARY_OF_ALEXANDRIA_CPP_LFQ_H
#include <iostream>
#include <vector>
#include <pthread.h>
#include <atomic>

#include "util.h"

template<typename T>
class LFQueue final
{
private:
	std::vector<T> store_;
	std::atomic<size_t> next_write_index_ = {0};
	std::atomic<size_t> next_read_index_ = {0};
	std::atomic<size_t> num_elements_ = {0};

public:
	LFQueue(size_t num_elems) : store_(num_elems, T())
	{
	}

	LFQueue() = delete;
	LFQueue(const LFQueue&) = delete;
	LFQueue(const LFQueue&&) = delete;
	LFQueue& operator=(const LFQueue&) = delete;
	LFQueue& operator=(const LFQueue&&) = delete;

	T* get_next_write_loc() noexcept
	{
		return &store_[next_write_index_];
	}

	void update_write_idx() noexcept
	{
		next_write_index_ = (next_write_index_ + 1) % store_.size();
		num_elements_++;
	}

	const T* get_next_to_read() const noexcept
	{
		if (next_read_index_ == next_write_index_)
		{
			return nullptr;
		}

		return &store_[next_read_index_];
	}

	void update_read_idx() noexcept
	{
		next_read_index_ = (next_read_index_ + 1) % store_.size();

		char thread_name[64];
		pthread_getname_np(pthread_self(), thread_name, sizeof(thread_name));
		std::string thread_name_str(thread_name);

		ASSERT(num_elements_ != 0, "Read an invalid element in: " + thread_name_str);
		num_elements_--;
	}

	size_t size() const noexcept
	{
		return num_elements_.load();
	}
};

#endif //LIBRARY_OF_ALEXANDRIA_CPP_LFQ_H
