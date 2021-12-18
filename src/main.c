#include <stdio.h>
#include <uncertain.h>

int
main(int argc, char *  argv[])
{
	double a1, a2;
	const double rangeStart = 0;
	const double rangeStop = 1;
	const unsigned long iterations = 5;
	const double cutoff = 0.9;

	a1 = libUncertainDoubleUniformDist(rangeStart, rangeStop);
	printf("Create a uniform distribution a1 between [%lf, %lf] (constant)\n", rangeStart, rangeStop);
	printf("a1 = %lf\n", a1);
	libUncertainDoublePrint(a1);

	for (unsigned long i = 0; i < iterations; i++){
		printf("Iteration i = %lu\n", i);

		printf("Subtract from a1 a parameter-equal uniform distribution a2 (changes every iteration)\n");
		a2 = libUncertainDoubleUniformDist(rangeStart, rangeStop);
		printf("a2 = %lf\n", a2);
		libUncertainDoublePrint(a2);

		double result = a1 - a2;
		double result2ndMode = libUncertainDoubleNthMoment(result, 1);
		double resultTailProbabilityPositive = libUncertainDoubleProbabilityGT(result, +cutoff);
		double resultTailProbabilityNegative = 1 - libUncertainDoubleProbabilityGT(result, -cutoff);

		printf("result = a1 - a2 = %lf\n", result);
		libUncertainDoublePrint(result);
		printf("result's 2nd mode = %lf\n", result2ndMode);
		printf("tail (>%lf) probability for result = %lf\n", +cutoff, resultTailProbabilityPositive);
		printf("tail (<%lf) probability for result = %lf\n", -cutoff, resultTailProbabilityNegative);

		/*if (result < cutoff){*/
		/*  printf("result below cutoff %.3lf\n", cutoff);*/
		/*}*/

	}

	return 0;
}
