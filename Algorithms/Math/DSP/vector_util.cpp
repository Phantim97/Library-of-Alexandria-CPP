#include <vector>
#include <complex>
#include <omp.h>

enum class NumberType
{
	REAL,
	IMAG
};

void convert_double_to_complex(const std::vector<double>& input, std::vector<std::complex<double>>& output, const NumberType nt)
{
	output.resize(input.size());

	if (nt == NumberType::REAL)
	{
		std::ranges::transform(input, output.begin(), [](const double da)
			{
				return std::complex<double>(da, 0);
			});
	}
	else
	{
		std::ranges::transform(input, output.begin(), [](const double da)
			{
				return std::complex<double>(0, da);
			});
	}
}

std::vector<std::complex<double>> merge_to_complex(const std::vector<double>& r_in, const std::vector<double>& i_in)
{
	std::vector<std::complex<double>> out(r_in.size());

	#pragma omp parallel for
	for (int i = 0; i < out.size(); i++)
	{
		out[i] = std::complex<double>(r_in[i], i_in[i]);
	}

	return out;
}
