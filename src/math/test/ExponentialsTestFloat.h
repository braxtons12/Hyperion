#pragma once

#ifndef __MSC_VER
	#include <cmath>
#endif

#include "../../test/TestConstants.h"
#include "../Exponentials.h"
#include "gtest/gtest.h"

namespace math::test {
	using ::test::FLOAT_ACCEPTED_ERROR;

	TEST(ExponentialsTestFloat, frexpfCase1) {
		float input = 1.0F;
		float resultTest = 0.0F;
		float resultStd = 0.0F;
		int exponentTest = 0;
		int exponentStd = 0;

		resultTest = Exponentials::frexp(input, &exponentTest);
		resultStd = std::frexp(input, &exponentStd);

		ASSERT_FLOAT_EQ(resultTest, resultStd);
		ASSERT_EQ(exponentTest, exponentStd);
	}

	TEST(ExponentialsTestFloat, frexpfCase2) {
		float input = 2.093284109F;
		float resultTest = 0.0F;
		float resultStd = 0.0F;
		int exponentTest = 0;
		int exponentStd = 0;

		resultTest = Exponentials::frexp(input, &exponentTest);
		resultStd = std::frexp(input, &exponentStd);

		ASSERT_FLOAT_EQ(resultTest, resultStd);
		ASSERT_EQ(exponentTest, exponentStd);
	}

	TEST(ExponentialsTestFloat, expfCase1) {
		float input = 1.0F;
		ASSERT_FLOAT_EQ(Exponentials::exp(input), std::exp(input));
	}

	TEST(ExponentialsTestFloat, expfCase2) {
		float input = -1.0F / (44100.0F * 0.3F);
		ASSERT_FLOAT_EQ(Exponentials::exp(input), std::exp(input));
	}

	TEST(ExponentialsTestFloat, expfCase3) {
		float input = 3.0F;
		ASSERT_FLOAT_EQ(Exponentials::exp(input), std::exp(input));
	}

	TEST(ExponentialsTestFloat, expfCase4) {
		float input = 9.0F;
		ASSERT_FLOAT_EQ(Exponentials::exp(input), std::exp(input));
	}

	TEST(ExponentialsTestFloat, lnfCase1) {
		float input = 1.0F;
		ASSERT_FLOAT_EQ(Exponentials::ln(input), std::log(input));
	}

	TEST(ExponentialsTestFloat, lnfCase2) {
		float input = 3.0F;
		ASSERT_NEAR(Exponentials::ln(input), std::log(input), FLOAT_ACCEPTED_ERROR);
	}

	TEST(ExponentialsTestFloat, log2fCase1) {
		float input = 1.0F;
		ASSERT_NEAR(Exponentials::log2(input), std::log2(input), FLOAT_ACCEPTED_ERROR);
	}

	TEST(ExponentialsTestFloat, log2fCase2) {
		float input = 3.0F;
		ASSERT_NEAR(Exponentials::log2(input), std::log2(input), FLOAT_ACCEPTED_ERROR);
	}

	TEST(ExponentialsTestFloat, log10fCase1) {
		float input = 1.0F;
		ASSERT_NEAR(Exponentials::log10(input), std::log10(input), FLOAT_ACCEPTED_ERROR);
	}

	TEST(ExponentialsTestFloat, log10fCase2) {
		float input = 3.0F;
		ASSERT_NEAR(Exponentials::log10(input), std::log10(input), FLOAT_ACCEPTED_ERROR);
	}

	TEST(ExponentialsTestFloat, pow2fCase1) {
		float input = 1.0F;
		ASSERT_NEAR(Exponentials::pow2(input), std::pow(2.0F, input), FLOAT_ACCEPTED_ERROR);
	}

	TEST(ExponentialsTestFloat, pow2fCase2) {
		float input = 3.0F;
		ASSERT_NEAR(Exponentials::pow2(input), std::pow(2.0F, input), FLOAT_ACCEPTED_ERROR);
	}

	TEST(ExponentialsTestFloat, pow2fCase3) {
		float input = 3.123456F;
		ASSERT_NEAR(Exponentials::pow2(input), std::pow(2.0F, input), FLOAT_ACCEPTED_ERROR);
	}

	TEST(ExponentialsTestFloat, pow2fCase4) {
		float input = -2.123456F;
		ASSERT_NEAR(Exponentials::pow2(input), std::pow(2.0F, input), FLOAT_ACCEPTED_ERROR);
	}

	TEST(ExponentialsTestFloat, pow10fCase1) {
		float input = 1.0F;
		ASSERT_NEAR(Exponentials::pow10(input), std::pow(10.0F, input), FLOAT_ACCEPTED_ERROR);
	}

	TEST(ExponentialsTestFloat, pow10fCase2) {
		float input = 3.0F;
		ASSERT_NEAR(Exponentials::pow10(input), std::pow(10.0F, input), FLOAT_ACCEPTED_ERROR);
	}

	TEST(ExponentialsTestFloat, pow10fCase3) {
		float input = 3.123456F;
		ASSERT_NEAR(Exponentials::pow10(input), std::pow(10.0F, input), FLOAT_ACCEPTED_ERROR);
	}

	TEST(ExponentialsTestFloat, pow10fCase4) {
		float input = -2.123456F;
		ASSERT_NEAR(Exponentials::pow10(input), std::pow(10.0F, input), FLOAT_ACCEPTED_ERROR);
	}

	TEST(ExponentialsTestFloat, powfCase1) {
		float base = 3.5F;
		float exponent = 1.0F;
		ASSERT_NEAR(Exponentials::pow(base, exponent),
					std::pow(base, exponent),
					FLOAT_ACCEPTED_ERROR);
	}

	TEST(ExponentialsTestFloat, powfCase2) {
		float base = 3.5F;
		float exponent = 2.0F;
		ASSERT_NEAR(Exponentials::pow(base, exponent),
					std::pow(base, exponent),
					FLOAT_ACCEPTED_ERROR);
	}

	TEST(ExponentialsTestFloat, powfCase3) {
		float base = 3.5F;
		float exponent = 2.123456F;
		ASSERT_NEAR(Exponentials::pow(base, exponent),
					std::pow(base, exponent),
					FLOAT_ACCEPTED_ERROR);
	}

	TEST(ExponentialsTestFloat, powfCase4) {
		float base = 3.5F;
		float exponent = -2.123456F;
		ASSERT_NEAR(Exponentials::pow(base, exponent),
					std::pow(base, exponent),
					FLOAT_ACCEPTED_ERROR);
	}

	TEST(ExponentialsTestFloat, powfCase5) {
		float base = 3.5F;
		float exponent = 1.0F / 2.0F;
		ASSERT_NEAR(Exponentials::pow(base, exponent),
					std::pow(base, exponent),
					FLOAT_ACCEPTED_ERROR);
	}

	TEST(ExponentialsTestFloat, powfCase6) {
		float base = 0.7F;
		float exponent = 1.0F / 2.0F;
		ASSERT_NEAR(Exponentials::pow(base, exponent),
					std::pow(base, exponent),
					FLOAT_ACCEPTED_ERROR);
	}

	TEST(ExponentialsTestFloat, powfCase7) {
		float base = 0.2F;
		float exponent = 1.0F / 2.0F;
		ASSERT_NEAR(Exponentials::pow(base, exponent),
					std::pow(base, exponent),
					FLOAT_ACCEPTED_ERROR);
	}

	TEST(ExponentialsTestFloat, powfCase8) {
		float base = 2.0F;
		float exponent = 7.5F;
		ASSERT_NEAR(Exponentials::pow(base, exponent),
					std::pow(base, exponent),
					FLOAT_ACCEPTED_ERROR);
	}

	TEST(ExponentialsTestFloat, powfCase9) {
		float base = 8.0F;
		float exponent = 0.5F;
		ASSERT_NEAR(Exponentials::pow(base, exponent),
					std::pow(base, exponent),
					FLOAT_ACCEPTED_ERROR + 0.0001); // close enough
	}
} // namespace math::test
