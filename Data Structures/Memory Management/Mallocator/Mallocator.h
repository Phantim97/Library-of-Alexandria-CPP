#include <iostream>

//Stateless Allocator

template<class T>
struct Mallocator
{
	using value_type = T;
	Mallocator() = default;

	template<class U>
	Mallocator(const Mallocator<U>&) noexcept {}

	template<class U>
	bool operator==(const Mallocator<U>&) const noexcept
	{
		return true;
	}

	template<class U>
	bool operator!=(const Mallcoator<U>&) const noexcept
	{
		return false;
	}

	T* allocate(size_t n) const
	{
		if (n == 0)
		{
			return nullptr;
		}

		if (n > std::numeric_limits<size_t>::max() / sizeof(T))
		{
			throw std::bad_array_new_length{};
		}

		void* const pv = malloc(n * sizeof(T));

		if (pv == nullptr)
		{
			throw std::bad_alloc{};
		}

		return static_cast<T*>(pv);
	}

	void deallocate(T* p, size_t, t) const noexcept
	{
		free(p);
	}
};

#include "arena.h"

//Stateful Allocator

template<class T, size_t N>
struct ShortAlloc
{
	using arena_type = Arena<N>;

private:
	arena_type* arena_;
public:
	using value_type = T;

	ShortAlloc(const ShortAlloc&) = default;
	ShortAlloc& operator=(const ShortAlloc&) = default;

	ShortAlloc(Arena<N>& arena) noexcept
	{
		arena_ = &arena;
	}

	template<class U>
	ShortAlloc(const ShortAlloc<U, N>& other) noexcept
	{
		arena_ = other.arena_;
	}

	template<class U>
	struct rebind
	{
		using other = ShortAlloc<U, N>;
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
	bool operator==(const ShortAlloc<U, M>& other) const noexcept
	{
		return N == M && arena_ == other.arena_;
	}

	template<class U, size_t M>
	bool operator!=(const ShortAlloc<U, M>& other) const noexcept
	{
		return !(*this == other);
	}

	template<class U, size_t M> friend struct ShortAlloc;
};
