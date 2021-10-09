#include <iostream>
#include <chrono>

class ScopedTimer
{
private:
	using ClockType = std::chrono::steady_clock;
	const char* function_name_{};
	const ClockType::time_point_ start{};
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
		auto stop = ClockType::now();
		auto duration = (stop - start_);
		auto ms = duration_cast<milliseconds>(duration).count();
		std::cout << ms << "ms " << function_name_ << '\n';
	}
};

#if USE_TIMER
#define MEASURE_FUNCTION() ScopedTimer timer{__func__};
#else
#define MEASURE_FUNCTION()
#endif
