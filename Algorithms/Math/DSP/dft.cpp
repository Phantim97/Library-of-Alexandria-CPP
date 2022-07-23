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

//Inverse DFT (note needs full length N lengths of both th
void calc_sig_idft(double* sig_re, double* sig_im, double* res, const int idft_len)
{
	for (int k = 0; k < idft_len / 2; k++)
	{
		sig_re[k] /= (idft_len / 2);
		sig_im[k] /= -(idft_len / 2);
	}

	sig_re[0] /= 2;
	sig_im[0] /= -2;

	for (int k = 0; k < idft_len / 2; k++)
	{
		for (int i = 0; i < idft_len; i++)
		{
			res[i] += sig_re[k] * cos(2 * M_PI * k * i / idft_len);
			res[i] += sig_im[k] * sin(2 * M_PI * k * i / idft_len);
		}
	}
}

std::vector<double> idft_calc(std::vector<std::complex<double>>& in)
{
	std::vector<double> res;
	res.resize(in.size());

	in[0].real(in[0].real() / 2);
	in[0].imag(-in[0].imag() / 2);

	#pragma omp parallel for
	for (int k = 1; k < in.size() / 2; k++)
	{
		in[k].real(in[k].real() / (in.size() / 2));
		in[k].imag(-in[k].imag() / (in.size() / 2));
	}

	//This algorithm is iteration dependent and cannot be parallelized
	for (int k = 0; k < in.size() / 2; k++)
	{
		for (int i = 0; i < in.size(); i++)
		{
			res[i] += in[k].real() * cos((2 * M_PI * k * i) / static_cast<double>(in.size()));
			res[i] += in[k].imag() * sin((2 * M_PI * k * i) / static_cast<double>(in.size()));
		}
	}

	return res;
}

std::vector<std::complex<double>> complex_dft(const std::vector<std::complex<double>>& time_domain)
{
	constexpr double two_pi = 2 * M_PI;
    std::vector<std::complex<double>> freq_domain(time_domain.size());
    const size_t sz = time_domain.size();

    for (int k = 0; k < sz; k++)
    {
        for (int i = 0; i < sz; i++)
        {
			const double eval = 2 * M_PI * k * i / sz;
            freq_domain[k].real(freq_domain[k].real() + time_domain[i].real() * cos(eval) + time_domain[k].imag() * sin(eval));
            freq_domain[k].imag(freq_domain[k].imag() + time_domain[i].imag() * cos(eval) + time_domain[k].real() * sin(eval));
        }
    }

    return freq_domain;
}

std::vector<std::complex<double>> complex_dft_euler(const std::vector<std::complex<double>>& time_domain)
{
	using namespace std::complex_literals;
	constexpr double two_pi = 2 * M_PI;
	std::vector<std::complex<double>> freq_domain(time_domain.size());
	const size_t sz = time_domain.size();

	for (int k = 0; k < sz; k++)
	{
		for (int n = 0; n < sz; n++)
		{
			const double eval = two_pi * k * n / sz;
			freq_domain[k] += time_domain[n] * exp(-1i * eval);
		}
	}

	return freq_domain;
}
