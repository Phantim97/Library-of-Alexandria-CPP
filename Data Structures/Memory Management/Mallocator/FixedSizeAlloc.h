//
// Created by Timothy Coelho on 8/3/24.
//

#ifndef DS_FIXEDSIZEALLOC_H
#define DS_FIXEDSIZEALLOC_H
#include <iostream>
#include <cstddef>
#include <limits>
#include <new>
#include "../Arena/arena.h"

// Stateful Allocator
template<class T, size_t N>
struct FixedSizeAlloc
{
	using arena_type = Arena<N>;
	using value_type = T;

private:
	arena_type* arena_;

public:
	FixedSizeAlloc(Arena<N>& arena) noexcept : arena_(&arena) {}

	template<class U>
	FixedSizeAlloc(const FixedSizeAlloc<U, N>& other) noexcept : arena_(other.arena_) {}

	FixedSizeAlloc(const FixedSizeAlloc&) = default;
	FixedSizeAlloc& operator=(const FixedSizeAlloc&) = default;

	template<class U>
	struct rebind
	{
		using other = FixedSizeAlloc<U, N>;
	};

	T* allocate(size_t n)
	{
		return reinterpret_cast<T*>(arena_->allocate(n * sizeof(T)));
	}

	void deallocate(T* p, size_t n) noexcept
	{
		arena_->deallocate(reinterpret_cast<std::byte*>(p), n * sizeof(T));
	}

	template<class U, size_t M>
	bool operator==(const FixedSizeAlloc<U, M>& other) const noexcept
	{
		return N == M && arena_ == other.arena_;
	}

	template<class U, size_t M>
	bool operator!=(const FixedSizeAlloc<U, M>& other) const noexcept
	{
		return *this != other;
	}

	template<class U, size_t M> friend struct FixedSizeAlloc;
};

#endif //DS_FIXEDSIZEALLOC_H
