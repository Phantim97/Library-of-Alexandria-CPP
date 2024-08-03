#pragma once
#include <cstddef>
#include <cstdlib>
#include <new>
#include <numeric>

template<typename T>
struct Alloc
{
	using value_type = T;

	Alloc() noexcept = default;

	template<typename U>
	Alloc(const Alloc<U>&) noexcept {}

	// Allocates memory for n objects of type T
	T* allocate(std::size_t n)
	{
		if (n == 0)
		{
			return nullptr;
		}

		if (n > std::numeric_limits<std::size_t>::max() / sizeof(T))
		{
			throw std::bad_array_new_length{};
		}

		void* ptr = std::malloc(n * sizeof(T));
		if (!ptr)
		{
			throw std::bad_alloc{};
		}

		return static_cast<T*>(ptr);
	}

	// Deallocates the memory pointed to by p
	void deallocate(T* p, std::size_t) noexcept
	{
		std::free(p);
	}

	// Comparison operators
	template<typename U>
	bool operator==(const Alloc<U>&) const noexcept
	{
		return true;
	}

	template<typename U>
	bool operator!=(const Alloc<U>&) const noexcept
	{
		return false;
	}
};
