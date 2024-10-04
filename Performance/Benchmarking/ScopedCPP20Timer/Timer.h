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

//SFINAE's out any non-time types
template<TimeType T>
class Timer
{
private:
	std::chrono::high_resolution_clock::time_point t0_;
	std::chrono::high_resolution_clock::time_point t1_;

public:
	Timer() : t0_(std::chrono::high_resolution_clock::now())
	{
	}

	~Timer()
	{
		t1_ = std::chrono::high_resolution_clock::now();
		const int elapsed = std::chrono::duration_cast<T>(t1_ - t0_).count();

		//Compile Time Branching
		if constexpr (std::is_same_v<T, std::chrono::nanoseconds>)
		{
			std::cout << "Duration: " << elapsed << "ns" << '\n';
		}
		else if constexpr (std::is_same_v<T, std::chrono::milliseconds>)
		{
			std::cout << "Duration: " << elapsed << "ms" << '\n';
		}
		else if constexpr (std::is_same_v<T, std::chrono::seconds>)
		{
			std::cout << "Duration: " << elapsed << "s" << '\n';
		}
		else if constexpr (std::is_same_v<T, std::chrono::minutes>)
		{
			std::cout << "Duration: " << elapsed << "mins" << '\n';
		}
		else if constexpr (std::is_same_v<T, std::chrono::hours>)
		{
			std::cout << "Duration: " << elapsed << "hrs" << '\n';
		}
	}
};

#endif //LIBRARY_OF_ALEXANDRIA_CPP_TIMER_H
