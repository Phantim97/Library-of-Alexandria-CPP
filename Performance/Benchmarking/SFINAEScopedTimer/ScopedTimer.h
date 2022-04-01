#pragma once

#include <functional>
#include <chrono>
#include <iostream>

template <typename T>
struct st_time
{
	static const bool val = false;
};

template<>
struct st_time<std::chrono::nanoseconds>
{
	static const bool val = true;
	using type = std::chrono::nanoseconds;
};

template<>
struct st_time<std::chrono::milliseconds>
{
	static const bool val = true;
	using type = std::chrono::milliseconds;
};

template<>
struct st_time<std::chrono::seconds>
{
	static const bool val = true;
	using type = std::chrono::seconds;
};

template<>
struct st_time<std::chrono::minutes>
{
	static const bool val = true;
	using type = std::chrono::minutes;
};

template<>
struct st_time<std::chrono::hours>
{
	static const bool val = true;
	using type = std::chrono::hours;
};

//value template using constexpr keyword
template<typename T>
constexpr bool is_timeunit = st_time<T>::val; // compile time resolution

template<typename T>
using timeunit_t = typename st_time<T>::type;

//Identical type check
template<typename T1, typename T2>
struct st_same_type
{
	static const bool value = false;
};

template<typename T>
struct st_same_type<T, T>
{
	static const bool value = true;
	using type = T;
};

//value template
template<typename T1, typename T2>
constexpr bool is_same_v = st_same_type<T1, T2>::value;

//using template - type alias
template<typename T1, typename T2>
using same_t = typename st_same_type<T1, T2>::type;


template<typename T, typename = st_time<T>>
struct TimerRes
{
	void operator()(const int t) const
	{
		if (is_same_v<T, std::chrono::nanoseconds>)
		{
			std::cout << "Duration: " << t << "ns" << '\n';
		}
		else if (is_same_v<T, std::chrono::milliseconds>)
		{
			std::cout << "Duration: " << t << "ms" << '\n';
		}
		else if (is_same_v<T, std::chrono::seconds>)
		{
			std::cout << "Duration: " << t << "s" << '\n';
		}
		else if (is_same_v<T, std::chrono::minutes>)
		{
			std::cout << "Duration: " << t << "mins" << '\n';
		}
		else if (is_same_v<T, std::chrono::hours>)
		{
			std::cout << "Duration: " << t << "hrs" << '\n';
		}
	}
};

//SFINAE out all other units of time except for the ones specialized
template<typename T, typename = st_time<T>>
class ScopedTimer
{
private:
	std::chrono::high_resolution_clock::time_point t0_;
	std::chrono::high_resolution_clock::time_point t1_;
	std::function<void(int)> callback_;
  
public:
	ScopedTimer() : t0_(std::chrono::high_resolution_clock::now()),
		callback_(TimerRes<T>())
	{
	}

	ScopedTimer(std::function<void(int)> callback) :
		t0_(std::chrono::high_resolution_clock::now()),
		callback_(callback)
	{
	}

	~ScopedTimer()
	{
		t1_ = std::chrono::high_resolution_clock::now();
		const int elapsed = std::chrono::duration_cast<T>(t1_ - t0_).count();

		callback_(elapsed);
	}
};
