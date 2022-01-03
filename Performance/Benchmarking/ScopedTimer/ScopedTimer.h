#include <iostream>
#include <chrono>

class ScopedTimer
{
private:
	using ClockType = std::chrono::steady_clock;
	const char* function_name_{};
	ClockType::time_point start_{};
public:
	ScopedTimer(const char* func)
	{
		function_name_ = func;
		start_ = ClockType::now();
	}

	ScopedTimer(const ScopedTimer&) = delete;
	ScopedTimer(ScopedTimer&&) = delete;

	ScopedTimer& operator=(const ScopedTimer&) = delete;
	ScopedTimer& operator=(ScopedTimer&&) = delete;

	~ScopedTimer()
	{
		using namespace std::chrono;
		std::chrono::time_point<steady_clock> stop = ClockType::now();
		std::common_type_t<duration<long long, std::ratio<1, 1000000000>>, duration<
			                   long long, std::ratio<1, 1000000000>>> duration = (stop - start_);
		const long long ms = duration_cast<milliseconds>(duration).count();
		std::cout << ms << "ms " << function_name_ << '\n';
	}
};

#if USE_TIMER
#define MEASURE_FUNCTION() ScopedTimer timer{__func__};
#else
#define MEASURE_FUNCTION()
#endif
