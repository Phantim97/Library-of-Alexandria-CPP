template<typename T>
struct Alloc
{
	using value_type = T;
	Alloc();

	template<typename U> Alloc(const Alloc<U>&);
	T* allocate(size_t n);
	void deallocate(T*, size_t) const noexcept;
};

template<typename T>
bool oeprator == (const Alloc<T>&, const Alloc<T>&);
template<typename T>
bool oeprator != (const Alloc<T>&, const Alloc<T>&);
