#pragma once

#include <gtest/gtest.h>

#include "../../test/TestConstants.h"
#include "../Vec3.h"

namespace math::test {
	using ::test::DOUBLE_ACCEPTED_ERROR;
	using ::test::FLOAT_ACCEPTED_ERROR;

	TEST(Vec3Test, magnitude) {
		auto vec = Vec3(3.0F, 5.0F, 7.0F);
		ASSERT_NEAR(vec.magnitude(), 9.110433579F, FLOAT_ACCEPTED_ERROR);
	}

	TEST(Vec3Test, dotProdFloat) {
		auto vec1 = Vec3(3.5F, 5.5F, 7.5F);
		auto vec2 = Vec3(5.5F, 3.5F, 7.5F);
		ASSERT_FLOAT_EQ(vec1.dot_prod(vec2), 94.75F);
	}

	TEST(Vec3Test, dotProdDouble) {
		auto vec1 = Vec3(3.5, 5.5, 7.5);
		auto vec2 = Vec3(5.5, 3.5, 7.5);
		ASSERT_DOUBLE_EQ(vec1.dot_prod(vec2), 94.75);
	}

	TEST(Vec3Test, dotProdFloatInt) {
		auto vec1 = Vec3(3.5F, 5.5F, 7.5F);
		auto vec2 = Vec3(6, 4, 8);
		ASSERT_FLOAT_EQ(vec1.dot_prod(vec2), 103.0F);
	}

	TEST(Vec3Test, dotProdIntFloat) {
		auto vec1 = Vec3(6, 4, 8);
		auto vec2 = Vec3(3.5F, 5.5F, 7.5F);
		ASSERT_FLOAT_EQ(vec1.dot_prod(vec2), 103.0F);
	}

	TEST(Vec3Test, crossProdFloat) {
		auto vec1 = Vec3(3.5F, 8.4F, 10.2F);
		auto vec2 = Vec3(4.3F, 9.2F, 1.2F);
		ASSERT_EQ(vec1.cross_prod(vec2), Vec3<float>(-83.76F, 39.66F, -3.92F));
	}

	TEST(Vec3Test, crossProdDouble) {
		auto vec1 = Vec3(3.5, 8.4, 10.2);
		auto vec2 = Vec3(4.3, 9.2, 1.2);
		ASSERT_EQ(vec1.cross_prod(vec2), Vec3<double>(-83.76, 39.66, -3.92));
	}

	TEST(Vec3Test, crossProdFloatInt) {
		auto vec1 = Vec3(3.5F, 8.4F, 10.2F);
		auto vec2 = Vec3(4, 9, 1);
		ASSERT_EQ(vec1.cross_prod(vec2), Vec3<float>(-83.4F, 37.3F, -2.1F));
	}

	TEST(Vec3Test, crossProdIntFloat) {
		auto vec1 = Vec3(4, 9, 1);
		auto vec2 = Vec3(3.5F, 8.4F, 10.2F);
		ASSERT_EQ(vec1.cross_prod(vec2), Vec3<float>(83.4F, -37.3F, 2.1F));
	}

	TEST(Vec3Test, normalFloatFloat) {
		auto vec = Vec3(3.5F, 5.5F, 7.5F);
		auto normal = vec.normal();
		ASSERT_FLOAT_EQ(normal.dot_prod(vec), 0.0F);
	}

	TEST(Vec3Test, normalDoubleFloat) {
		auto vec = Vec3(3.5, 5.5, 7.5);
		auto normal = vec.normal();
		ASSERT_NEAR(normal.dot_prod(vec), 0.0F, FLOAT_ACCEPTED_ERROR);
	}

	TEST(Vec3Test, normalIntFloat) {
		auto vec = Vec3(3, 5, 7);
		auto normal = vec.normal();
		ASSERT_EQ(normal.dot_prod(vec), 0);
	}

	TEST(Vec3Test, normalizedFloat) {
		auto vec = Vec3(3.5F, 5.5F, 7.5F);
		ASSERT_NEAR(vec.normalized().magnitude(), 1.0F, FLOAT_ACCEPTED_ERROR);
	}

	TEST(Vec3Test, normalizedDouble) {
		auto vec = Vec3(3.5, 5.5, 7.5);
		ASSERT_NEAR(vec.normalized().magnitude(), 1.0F, FLOAT_ACCEPTED_ERROR);
	}

	TEST(Vec3Test, normalizedInt) {
		auto vec = Vec3(3, 5, 7);
		ASSERT_NEAR(vec.normalized().magnitude(), 1.0F, FLOAT_ACCEPTED_ERROR);
	}

	TEST(Vec3Test, opNegative) {
		auto vec = Vec3(3, 5, 7);
		ASSERT_EQ(-vec, Vec3<int>(-3, -5, -7));
	}

	TEST(Vec3Test, opPlus) {
		auto vec = Vec3(3, 5, 7);
		auto vec2 = Vec3(3.5F, 5.5F, 7.5F);
		ASSERT_EQ(vec + vec2, Vec3(6.5F, 10.5F, 14.5F));
	}

	TEST(Vec3Test, opPlusEquals) {
		auto vec = Vec3(3, 5, 7);
		auto vec2 = Vec3(3.5F, 5.5F, 7.5F);
		vec += vec2;
		ASSERT_EQ(vec, Vec3(6, 10, 14));
	}

	TEST(Vec3Test, opMinus) {
		auto vec = Vec3(3, 5, 7);
		auto vec2 = Vec3(3.5F, 5.5F, 7.5F);
		ASSERT_EQ(vec - vec2, Vec3(-0.5F, -0.5F, -0.5F));
	}

	TEST(Vec3Test, opMinusEquals) {
		auto vec = Vec3(3, 5, 7);
		auto vec2 = Vec3(3.5F, 5.5F, 7.5F);
		vec -= vec2;
		ASSERT_EQ(vec, Vec3(0, 0, 0));
	}

	TEST(Vec3Test, opMul) {
		auto vec = Vec3(3, 5, 7);
		ASSERT_EQ(vec * 2.5, Vec3(7.5, 12.5, 17.5));
	}

	TEST(Vec3Test, opMulEquals) {
		auto vec = Vec3(3, 5, 7);
		vec *= 2.5;
		ASSERT_EQ(vec, Vec3(7, 12, 17));
	}

	TEST(Vec3Test, opDivide) {
		auto vec = Vec3(3, 5, 7);
		ASSERT_EQ(vec / 2.5, Vec3(1.2, 2.0, 2.8));
	}

	TEST(Vec3Test, opDivideEquals) {
		auto vec = Vec3(3, 5, 7);
		vec /= 2.5;
		ASSERT_EQ(vec, Vec3(1, 2, 2));
	}
} // namespace math::test
