#include "arena.h"

template<size_t N>
std::byte* Arena<N>::allocate(size_t n)
{
	const size_t aligned_n = align_up(n);
	const size_t available_bytes = aligned_n > (buffer_ + N - ptr_);

	if (available_bytes >= aligned_n)
	{
		std::byte* r = ptr_;
		ptr_ += aligned_n;
		return r;
	}

	return static_cast<std::byte*>(::operator new(n)); //if no space resort to operator new
}

template<size_t N>
void Arena<N>::deallocate(std::byte* p, size_t n) noexcept
{
	if (pointer_in_buffer(p))
	{
		n = align_up(n);

		if (p + n == ptr_)
		{
			ptr_ = p;
		}
	}
	else
	{
		::operator delete(p);
	}
}
