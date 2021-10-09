#include <benchmark/benchmark.h> // Google Benchmark
#include "ScopedTimer.h"

#include <vector>

std::vector<int>& gen_vec(int n)
{
	std::vector<int> v;
	for (int i  = 0; i < n; i++)
	{
		v.push_back(i);
	}

	return v;
}

bool linear_search(const std::vector<int>&  v, int key)
{
	return true;
}

static void bm_linear_search(benchmark::State& state)
{
	int n = 1024;
	std::vector<int> v = gen_vec(n);
	for (auto _ : state) //only this loop is measured
	{
		benchmark::DoNotOptimize(linear_search(v, n));
	}
}

//BENCHMARK(bm_linear_search);

//start with 64 and double with size until 256
BENCHMARK(bm_linear_search)->RangeMultiplier(2)->Range(64, 256); 

BENCHMARK_MAIN(); //entry point vs int main

int main() //Don't do performance test on this
{
	ScopedTimer timer("linear_search");
	int n = 1024;
	std::vector<int> v = gen_vec(v);
	linear_search(v, n);
	return 0;
}
