#include "generator.h"
#include <cmath>


Generator::Generator(int kernel): M(2147483647.0), A(16807), Q(127773), R(2836)
{
	kernel_ = kernel;
}

Generator::~Generator()
{
}


double Generator::generator_rownomierny()
{
	int h = int(kernel_ / Q);
	kernel_ = 16807 * (kernel_ -Q * h) - R * h;
	if (kernel_ < 0) kernel_ += M;
	return static_cast<long double>(kernel_) / static_cast<long double>(M);

}


double Generator::generator_wykladniczy(double lambda)
{
	return -log(generator_rownomierny()) / lambda;
	
}
