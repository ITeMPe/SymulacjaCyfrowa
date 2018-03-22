#ifndef TEST_LICZB_PSEUDOLOSOWYCH_GENERATOR_H
#define TEST_LICZB_PSEUDOLOSOWYCH_GENERATOR_H
class Generator
{
public:
	Generator(int kernel);
	~Generator();

	const double M;
	const double A;
	const double Q;
	const double R;
	int kernel_;

	double generator_rownomierny();
	double generator_wykladniczy(double lambda);
};
#endif // SYMULACJA CYFROWA Generator H
