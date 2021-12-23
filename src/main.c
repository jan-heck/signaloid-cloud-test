#include <stdio.h>
#include <uncertain.h>

int
main(int argc, char *  argv[])
{
	/*
	 * Example for testing on signaloid.io
	 *
	 * Create a distribution a1 and subtract from it parameter-equal but changing
	 * distributions a2
	 *
	 * If a1, a2 were non-uncertainty-aware fixed-value scalars, the result would
	 * be identically 0. If a1, a2 were e.g. sensor readings that are expected to
	 * fall very close to each other, a real program might check for them to be
	 * equal (given some $cutoff for comparing floating point values), and change
	 * its control flow path based on the outcome. Given enough time and uncertainty,
	 * the noise in a1 and a2 will add together to reach over some $cutoff.
	 *
	 * To find the likelihood for this occuring, we can check for the result of
	 * abs(a1 - a2) > cutoff, which is a simple measure for when an unlikely-but-
	 * possible result would occur and require special handling (e.g. re-checking)
	 * when working with noisy data but without the use of uncertainty/distribution-
	 * aware arithmetic.
	 *
	 */
	double a1, a2;
	const double rangeStart = 0;
	const double rangeStop = 1;
	const unsigned long iterations = 10;
	const double cutoff = 0.9;

	a1 = libUncertainDoubleUniformDist(rangeStart, rangeStop);
	printf("Create a uniform distribution a1 between [%lf, %lf] (constant)\n", rangeStart, rangeStop);
	printf("a1 = %lf\n", a1);
	libUncertainDoublePrint(a1);

	for (unsigned long i = 0; i < iterations; i++){
		printf("\n\nIteration i = %lu\n", i);

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
		printf("tail (>%+lf) probability for result = %lf\n", +cutoff, resultTailProbabilityPositive);
		printf("tail (<%+lf) probability for result = %lf\n", -cutoff, resultTailProbabilityNegative);
	}

	return 0;
}
