#include <stdio.h>
#include <uncertain.h>

int
main(int argc, char *  argv[])
{
	double a1, a2;
	const double rangeStart = 0;
	const double rangeStop = 1;
	const unsigned long iterations = 5;
	const double cutoff = 0.01;

	a1 = libUncertainDoubleUniformDist(rangeStart, rangeStop);
	printf("a1 = %lf\n", a1);
	libUncertainDoublePrint(a1);

	for (unsigned long i = 0; i < iterations; i++){
		printf("i = %lu\n", i);

		a2 = libUncertainDoubleUniformDist(rangeStart, rangeStop);
		printf("a2 = %lf\n", a2);
		libUncertainDoublePrint(a2);

		double result = a1 - a2;
		double result1stMode = libUncertainDoubleNthMoment(result, 1);

		printf("result = a1 - a2 = %lf\n", result);
		libUncertainDoublePrint(result);
		printf("result's 1st mode = %lf\n", result1stMode);
		libUncertainDoublePrint(result1stMode);

		/*if (result < cutoff){*/
		/*  printf("result below cutoff %.3lf\n", cutoff);*/
		/*}*/

	}

	return 0;
}
