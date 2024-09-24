#ifndef LIBRARY_OF_ALEXANDRIA_CPP_TIMER_H
#define LIBRARY_OF_ALEXANDRIA_CPP_TIMER_H

#include <concepts>
#include <type_traits>
#include <chrono>
#include <functional>
#include <iostream>
#include <utility>

//SFINAE only time types
template <typename T>
concept TimeType = std::is_same_v<T, std::chrono::nanoseconds>
                   || std::is_same_v<T, std::chrono::milliseconds>
                   || std::is_same_v<T, std::chrono::seconds>
                   || std::is_same_v<T, std::chrono::minutes>
                   || std::is_same_v<T, std::chrono::hours>;

template <TimeType T>
struct TimerRes
{
	void operator()(const int t) const
	{
		//Compile Time Branching
		if constexpr (std::is_same_v<T, std::chrono::nanoseconds>)
		{
			std::cout << "Duration: " << t << "ns" << '\n';
		}
		else if constexpr (std::is_same_v<T, std::chrono::milliseconds>)
		{
			std::cout << "Duration: " << t << "ms" << '\n';
		}
		else if constexpr (std::is_same_v<T, std::chrono::seconds>)
		{
			std::cout << "Duration: " << t << "s" << '\n';
		}
		else if constexpr (std::is_same_v<T, std::chrono::minutes>)
		{
			std::cout << "Duration: " << t << "mins" << '\n';
		}
		else if constexpr (std::is_same_v<T, std::chrono::hours>)
		{
			std::cout << "Duration: " << t << "hrs" << '\n';
		}
	}
};

//SFINAE's out any non-time types
template<TimeType T>
class Timer
{
private:
	std::chrono::high_resolution_clock::time_point t0_;
	std::chrono::high_resolution_clock::time_point t1_;
	std::function<void(int)> callback_;

public:
	Timer() : t0_(std::chrono::high_resolution_clock::now()),
	          callback_(TimerRes<T>())
	{
	}

	Timer(std::function<void(int)> callback) :
			t0_(std::chrono::high_resolution_clock::now()),
			callback_(std::move(callback))
	{
	}

	~Timer()
	{
		t1_ = std::chrono::high_resolution_clock::now();
		const int elapsed = std::chrono::duration_cast<T>(t1_ - t0_).count();

		callback_(elapsed);
	}
};

#endif //LIBRARY_OF_ALEXANDRIA_CPP_TIMER_H
