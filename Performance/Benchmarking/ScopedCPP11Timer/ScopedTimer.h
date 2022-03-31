#pragma once

#include <functional>
#include <chrono>
#include <iostream>

struct TimerRes
{
	void operator()(const int ns) const
	{
		std::cout << "Duration: " << ns << "ns" << '\n';
	}
};

class ScopedTimer
{
private:
	std::chrono::high_resolution_clock::time_point t0_;
	std::chrono::high_resolution_clock::time_point t1_;
	std::function<void(int)> callback_;
public:
	ScopedTimer() : t0_(std::chrono::high_resolution_clock::now()),
		callback_(TimerRes())
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
		const int elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(t1_ - t0_).count();

		callback_(elapsed);
	}
};
