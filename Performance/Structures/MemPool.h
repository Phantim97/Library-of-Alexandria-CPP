//
// Created by Timothy Coelho on 6/27/24.
//

#ifndef LIBRARY_OF_ALEXANDRIA_CPP_MEMPOOL_H
#define LIBRARY_OF_ALEXANDRIA_CPP_MEMPOOL_H

#include <vector>
#include <string>
#include "util.h"

template<typename T>
class MemPool final
{
private:
	struct ObjectBlock
	{
		T obj_;
		bool is_free_ = true;
	};

	std::vector<ObjectBlock> store_;
	size_t next_free_idx_ = 0;

	void update_next_free_idx() noexcept
	{
		const size_t initial_free_idx = next_free_idx_;

		while (!store_[next_free_idx_].is_free_)
		{
			next_free_idx_++;

			if (next_free_idx_ == store_.size()) [[unlikely]]
			{
				next_free_idx_ = 0;
			}

			if (initial_free_idx == next_free_idx_) [[unlikely]]
			{
				ASSERT(initial_free_idx != next_free_idx_, "Memory Pool out of Memory");
			}
		}
	}
public:
	//Preallocate the array
	explicit MemPool(size_t num_elements) : store_(num_elements, {T(), true})
	{
		ASSERT(reinterpret_cast<const ObjectBlock*>(&(store_[0].obj_)) == &(store_[0]),
		       "T object should be first member of ObjectBlock.");
	}

	MemPool() = delete;
	MemPool(const MemPool&) = delete;
	MemPool(const MemPool&&) = delete;
	MemPool& operator=(const MemPool&) = delete;
	MemPool& operator=(const MemPool&&) = delete;

	template<typename... Args>
	T* allocate(Args... args) noexcept
	{
		//Captures the underlying type of the expression store_[next_free_idx_] and removes any ref qualifiers from it.
		using BlockType = typename std::remove_reference<decltype(store_[next_free_idx_])>::type;

		BlockType* obj_block = &(store_[next_free_idx_]);
		ASSERT(obj_block->is_free_, "Expected free ObjectBlock at index:" + std::to_string(next_free_idx_));
		T* ret = &(obj_block->obj_);
		ret = new(ret) T(args...); // placement new
		obj_block->is_free_ = false;

		update_next_free_idx();

		return ret;
	}

	void deallocate(const T* elem) noexcept
	{
		const auto elem_index = (reinterpret_cast<const ObjectBlock*>(elem) - &store_[0]);
		ASSERT(elem_index >= 0 && static_cast<size_t>(elem_index) < store_.size(), "Element being deallocated does not belong in this memory pool");
		ASSERT(!store_[elem_index].is_free_, "Expected in-use ObjectBlock at idx: " + std::to_string(elem_index));
		store_[elem_index].is_free_ = true;
	}
};
#endif //LIBRARY_OF_ALEXANDRIA_CPP_MEMPOOL_H
