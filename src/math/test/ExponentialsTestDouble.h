#pragma once

#ifndef __MSC_VER
	#include <cmath>
#endif

#include "../../test/TestConstants.h"
#include "../Exponentials.h"
#include "gtest/gtest.h"

namespace math::test {
	using ::test::DOUBLE_ACCEPTED_ERROR;

	TEST(ExponentialsTestDouble, rexpCase1) {
		double input = 1.0;
		double resultTest = 0.0;
		double resultStd = 0.0;
		int exponentTest = 0;
		int exponentStd = 0;

		resultTest = Exponentials::frexp(input, &exponentTest);
		resultStd = std::frexp(input, &exponentStd);

		ASSERT_NEAR(resultTest, resultStd, DOUBLE_ACCEPTED_ERROR);
		ASSERT_EQ(exponentTest, exponentStd);
	}

	TEST(ExponentialsTestDouble, rexpCase2) {
		double input = 2.093284109;
		double resultTest = 0.0;
		double resultStd = 0.0;
		int exponentTest = 0;
		int exponentStd = 0;

		resultTest = Exponentials::frexp(input, &exponentTest);
		resultStd = std::frexp(input, &exponentStd);

		ASSERT_NEAR(resultTest, resultStd, DOUBLE_ACCEPTED_ERROR);
		ASSERT_EQ(exponentTest, exponentStd);
	}

	TEST(ExponentialsTestDouble, expCase1) {
		double input = 1.0;
		ASSERT_NEAR(Exponentials::exp(input), std::exp(input), DOUBLE_ACCEPTED_ERROR);
	}

	TEST(ExponentialsTestDouble, expCase2) {
		double input = -1.0 / (44100.0 * 0.3);
		ASSERT_NEAR(Exponentials::exp(input), std::exp(input), DOUBLE_ACCEPTED_ERROR);
	}

	TEST(ExponentialsTestDouble, expCase3) {
		double input = 3.0;
		ASSERT_NEAR(Exponentials::exp(input), std::exp(input), DOUBLE_ACCEPTED_ERROR);
	}

	TEST(ExponentialsTestDouble, expCase4) {
		double input = 9.0;
		ASSERT_NEAR(Exponentials::exp(input), std::exp(input), DOUBLE_ACCEPTED_ERROR);
	}

	TEST(ExponentialsTestDouble, lnCase1) {
		double input = 1.0;
		ASSERT_NEAR(Exponentials::ln(input), std::log(input), DOUBLE_ACCEPTED_ERROR);
	}

	TEST(ExponentialsTestDouble, lnCase2) {
		double input = 3.0;
		ASSERT_NEAR(Exponentials::ln(input), std::log(input), DOUBLE_ACCEPTED_ERROR);
	}

	TEST(ExponentialsTestDouble, log2Case1) {
		double input = 1.0;
		ASSERT_NEAR(Exponentials::log2(input), std::log2(input), DOUBLE_ACCEPTED_ERROR);
	}

	TEST(ExponentialsTestDouble, log2Case2) {
		double input = 3.0;
		ASSERT_NEAR(Exponentials::log2(input), std::log2(input), DOUBLE_ACCEPTED_ERROR);
	}

	TEST(ExponentialsTestDouble, log10Case1) {
		double input = 1.0;
		ASSERT_NEAR(Exponentials::log10(input), std::log10(input), DOUBLE_ACCEPTED_ERROR);
	}

	TEST(ExponentialsTestDouble, log10Case2) {
		double input = 3.0;
		ASSERT_NEAR(Exponentials::log10(input), std::log10(input), DOUBLE_ACCEPTED_ERROR);
	}

	TEST(ExponentialsTestDouble, pow2Case1) {
		double input = 1.0;
		ASSERT_NEAR(Exponentials::pow2(input), std::pow(2.0, input), DOUBLE_ACCEPTED_ERROR);
	}

	TEST(ExponentialsTestDouble, pow2Case2) {
		double input = 3.0;
		ASSERT_NEAR(Exponentials::pow2(input), std::pow(2.0, input), DOUBLE_ACCEPTED_ERROR);
	}

	TEST(ExponentialsTestDouble, pow2Case3) {
		double input = 3.123456;
		ASSERT_NEAR(Exponentials::pow2(input), std::pow(2.0, input), DOUBLE_ACCEPTED_ERROR);
	}

	TEST(ExponentialsTestDouble, pow2Case4) {
		double input = -2.123456;
		ASSERT_NEAR(Exponentials::pow2(input), std::pow(2.0, input), DOUBLE_ACCEPTED_ERROR);
	}

	TEST(ExponentialsTestDouble, pow10Case1) {
		double input = 1.0;
		ASSERT_NEAR(Exponentials::pow10(input), std::pow(10.0, input), DOUBLE_ACCEPTED_ERROR);
	}

	TEST(ExponentialsTestDouble, pow10Case2) {
		double input = 3.0;
		ASSERT_NEAR(Exponentials::pow10(input), std::pow(10.0, input), DOUBLE_ACCEPTED_ERROR);
	}

	TEST(ExponentialsTestDouble, pow10Case3) {
		double input = 3.123456;
		ASSERT_NEAR(Exponentials::pow10(input), std::pow(10.0, input), DOUBLE_ACCEPTED_ERROR);
	}

	TEST(ExponentialsTestDouble, pow10Case4) {
		double input = -2.123456;
		ASSERT_NEAR(Exponentials::pow10(input), std::pow(10.0, input), DOUBLE_ACCEPTED_ERROR);
	}

	TEST(ExponentialsTestDouble, powCase1) {
		double base = 3.5;
		double exponent = 1.0;
		ASSERT_NEAR(Exponentials::pow(base, exponent),
					std::pow(base, exponent),
					DOUBLE_ACCEPTED_ERROR);
	}

	TEST(ExponentialsTestDouble, powCase2) {
		double base = 3.5;
		double exponent = 2.0;
		ASSERT_NEAR(Exponentials::pow(base, exponent),
					std::pow(base, exponent),
					DOUBLE_ACCEPTED_ERROR);
	}

	TEST(ExponentialsTestDouble, powCase3) {
		double base = 3.5;
		double exponent = 2.123456;
		ASSERT_NEAR(Exponentials::pow(base, exponent),
					std::pow(base, exponent),
					DOUBLE_ACCEPTED_ERROR);
	}

	TEST(ExponentialsTestDouble, powCase4) {
		double base = 3.5;
		double exponent = -2.123456;
		ASSERT_NEAR(Exponentials::pow(base, exponent),
					std::pow(base, exponent),
					DOUBLE_ACCEPTED_ERROR);
	}

	TEST(ExponentialsTestdouble, powCase5) {
		double base = 3.5;
		double exponent = 1.0 / 2.0;
		ASSERT_NEAR(Exponentials::pow(base, exponent),
					std::pow(base, exponent),
					DOUBLE_ACCEPTED_ERROR);
	}

	TEST(ExponentialsTestdouble, powCase6) {
		double base = 0.7;
		double exponent = 1.0 / 2.0;
		ASSERT_NEAR(Exponentials::pow(base, exponent),
					std::pow(base, exponent),
					DOUBLE_ACCEPTED_ERROR);
	}

	TEST(ExponentialsTestdouble, powCase7) {
		double base = 0.2;
		double exponent = 1.0 / 2.0;
		ASSERT_NEAR(Exponentials::pow(base, exponent),
					std::pow(base, exponent),
					DOUBLE_ACCEPTED_ERROR);
	}

	TEST(ExponentialsTestdouble, powCase8) {
		double base = 2.0;
		double exponent = 7.5;
		ASSERT_NEAR(Exponentials::pow(base, exponent),
					std::pow(base, exponent),
					DOUBLE_ACCEPTED_ERROR); // close enough
	}
} // namespace math::test
