#pragma once
#include <iostream>
#include <cstddef>
#include <cstdint>
#include <new>

template <size_t N>
class Arena
{
private:
	static constexpr size_t alignment_ = alignof(std::max_align_t);
	alignas(alignment_) std::byte buffer_[N];
	std::byte* ptr_;

	static size_t align_up(size_t n) noexcept
	{
		return (n + (alignment_ - 1)) & ~(alignment_ - 1);
	}

	bool pointer_in_buffer(const std::byte* p) const noexcept
	{
		return std::uintptr_t(p) >= std::uintptr_t(buffer_) &&
		       std::uintptr_t(p) < std::uintptr_t(buffer_) + N;
	}

public:
	Arena() noexcept : ptr_(buffer_) {}

	Arena(const Arena&) = delete;
	Arena& operator=(const Arena&) = delete;

	void reset() noexcept
	{
		ptr_ = buffer_;
	}

	static constexpr size_t size() noexcept
	{
		return N;
	}

	[[nodiscard]] size_t used() const noexcept
	{
		return static_cast<size_t>(ptr_ - buffer_);
	}

	std::byte* allocate(const size_t n)
	{
		const size_t aligned_n = align_up(n);
		const size_t available_bytes = buffer_ + N - ptr_;

		if (available_bytes >= aligned_n)
		{
			std::byte* r = ptr_;
			ptr_ += aligned_n;
			return r;
		}

		return static_cast<std::byte*>(::operator new(n)); // If no space, resort to operator new
	}

	void deallocate(std::byte* p, size_t n) noexcept
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
};