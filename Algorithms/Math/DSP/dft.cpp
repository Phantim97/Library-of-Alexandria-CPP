#define _USE_MATH_DEFINES 
#include <iostream>
#include <cmath>
#include <vector>
#include <complex>

//Real/Imaginary mix
std::vector<std::complex<double>> computeDFT(const std::vector<std::complex<double>>& input)
{
	std::vector<std::complex<double>> output;
	
	for (size_t k = 0; k < input.size(); k++) //for each output element
	{
		std::complex<double> sum(0.0, 0.0);
		
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
