#ifndef MALLOCATOR_H
#define MALLOCATOR_H

#include <iostream>
#include <cstddef>
#include <limits>
#include <new>

// Stateless Allocator
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
	bool operator!=(const Mallocator<U>&) const noexcept
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

	void deallocate(T* p, size_t) const noexcept //we need 'size_t' here since the standard relies on this signature to behave properly
	{
		free(p);
	}
};


#endif // MALLOCATOR_H
