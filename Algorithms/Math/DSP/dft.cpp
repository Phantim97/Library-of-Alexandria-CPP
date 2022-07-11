#define _USE_MATH_DEFINES 
#include <iostream>
#include <cmath>
#include <vector>
#include <complex>
#include <omp.h>

//Note for the result the DFT is from range N/2 relative to the input otherwise the resulting sinusoid is the same as the first half reflected

//Real/Imaginary mix (angle calc approach)
std::vector<std::complex<double>> dft(const std::vector<std::complex<double>>& input)
{
	std::vector<std::complex<double>> output;
	
	for (size_t k = 0; k < input.size(); k++) //for each output element
	{
		std::complex<double> sum(0.0, 0.0);
		
		#pragma omp parallel for shared(input) reduction(+ : sum)
		for (int t = 0; t < input.size(); t++) //for each input element
		{
			double angle = 2 * M_PI * t * k / input.size();
			sum += input[t] * std::exp(-angle); //X[t] * e ^(-i(2*pi*k)/n)
		}

		output.push_back(sum);
	}

	return output;
}

//Only real numbers
void computeDFT_realonly(const std::vector<double>& inreal, const std::vector<double>& inimag, std::vector<double>& outreal, std::vector<double>& outimag)
{
	for (size_t k = 0; k < inreal.size(); k++) //for each output element
	{
		double sumreal = 0;
		double sumimag = 0;
		
		#pragma omp parallel for shared(inreal, inimag) reduction(+ : sumreal, sumimag)
		for (size_t t = 0; t < inreal.size(); t++)
		{
			double angle = 2 * M_PI * t * k / inreal.size();
			sumreal += inreal[t] * cos(angle) + inimag[t] * sin(angle);
			sumimag += -inreal[t] * sin(angle) + inimag[t] * cos(angle);
		}
		outreal[k] = sumreal;
		outimag[k] = sumimag;
	}
}

//Another variation
std::vector<std::complex<double>> dft_calc(const std::vector<std::complex<double>>& x)
{
	constexpr double two_pi = 2 * M_PI;
	const int N = x.size();
	const int K = N;

	std::vector<std::complex<double>> X; //output
	X.reserve(K);

	for (int k = 0; k < K; k++)
	{
		std::complex<double> int_sum = std::complex<double>(0, 0);

		#pragma omp parallel for shared(x) reduction(+ : int_sum)
		for (int n = 0; n < N; n++)
		{
			const double real_part = std::cos((two_pi / N) * k * n);
			const double imag_part = std::sin((two_pi / N) * k * n);
			const std::complex<double> val(real_part, -imag_part);
			int_sum += x[n] * val;
		}

		X.push_back(int_sum);
	}

	return X;
}

//C-Style Implementation of DFT
//res array for both real and imag should be sig_len/2
void c_style_dft(const double* sig_src, double* sig_res_real, double* sig_res_im, const int sig_len)
{
	for (int k = 0; k < sig_len / 2; k++)
	{
		for (int i = 0; i < sig_len; i++)
		{
			sig_res_real[k] += sig_src[i] * cos(2 * M_PI * k * i/ sig_len);
			sig_res_im[k] -= sig_src[i] * sin(2 * M_PI * k * i / sig_len);
		}
	}
}
