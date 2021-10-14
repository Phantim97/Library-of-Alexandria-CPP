#include <iostream>

template <size_t N>
class Arena
{
private:
	static constexpr size_t alignment = alignof(std::max_align_t);
	alignas(alignment) std::byte buffer_[N];
	std::byte* ptr_;

	static size_t align_up(size_t n) noexcept
	{
		return (n + (alignment - 1)) & ~(alignment - 1);
	}

	bool pointer_in_buffer(const std::byte* p) const noexcept
	{
		return std::uintptr_t(p) >= std::uintptr_t(buffer_) &&
			std::uintptr_t(p) < std::uintptr_t(buffer_) + N;
	}

public:
	Arena() noexcept
	{
		ptr_(buffer_);
	}

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

	size_t used() const noexcept
	{
		return static_cast<size_t>(ptr_ - buffer_);
	}

	std::byte* allocate(size_t n);
	void deallocate(std::byte* p, size_t n) noexcept;
};
