#pragma once

#include <gtest/gtest.h>

#include "../../test/TestConstants.h"
#include "../Vec2.h"

namespace math::test {
	using ::test::DOUBLE_ACCEPTED_ERROR;
	using ::test::FLOAT_ACCEPTED_ERROR;

	TEST(Vec2Test, magnitude) {
		auto vec = Vec2(3.0F, 5.0F);
		ASSERT_NEAR(vec.magnitude(), 5.830951895F, FLOAT_ACCEPTED_ERROR);
	}

	TEST(Vec2Test, dotProdFloat) {
		auto vec1 = Vec2(3.5F, 5.5F);
		auto vec2 = Vec2(5.5F, 3.5F);
		ASSERT_FLOAT_EQ(vec1.dot_prod(vec2), 38.5F);
	}

	TEST(Vec2Test, dotProdDouble) {
		auto vec1 = Vec2(3.5, 5.5);
		auto vec2 = Vec2(5.5, 3.5);
		ASSERT_DOUBLE_EQ(vec1.dot_prod(vec2), 38.5);
	}

	TEST(Vec2Test, dotProdFloatInt) {
		auto vec1 = Vec2(3.5F, 5.5F);
		auto vec2 = Vec2(6, 4);
		ASSERT_FLOAT_EQ(vec1.dot_prod(vec2), 43.0F);
	}

	TEST(Vec2Test, dotProdIntFloat) {
		auto vec1 = Vec2(6, 4);
		auto vec2 = Vec2(3.5F, 5.5F);
		ASSERT_FLOAT_EQ(vec1.dot_prod(vec2), 43.0F);
	}

	TEST(Vec2Test, crossProdFloat) {
		auto vec1 = Vec2(3.5F, 8.4F);
		auto vec2 = Vec2(4.3F, 9.2F);
		ASSERT_NEAR(vec1.cross_prod(vec2), -3.92F, FLOAT_ACCEPTED_ERROR);
	}

	TEST(Vec2Test, crossProdDouble) {
		auto vec1 = Vec2(3.5, 8.4);
		auto vec2 = Vec2(4.3, 9.2);
		ASSERT_NEAR(vec1.cross_prod(vec2), -3.92, DOUBLE_ACCEPTED_ERROR);
	}

	TEST(Vec2Test, crossProdFloatInt) {
		auto vec1 = Vec2(3.5F, 8.4F);
		auto vec2 = Vec2(4, 9);
		ASSERT_NEAR(vec1.cross_prod(vec2), -2.1F, FLOAT_ACCEPTED_ERROR);
	}

	TEST(Vec2Test, crossProdIntFloat) {
		auto vec1 = Vec2(4, 9);
		auto vec2 = Vec2(3.5F, 8.4F);
		ASSERT_NEAR(vec1.cross_prod(vec2), 2.1F, FLOAT_ACCEPTED_ERROR);
	}

	TEST(Vec2Test, normalFloatFloat) {
		auto vec = Vec2(3.5F, 5.5F);
		auto normal = vec.normal();
		ASSERT_FLOAT_EQ(normal.dot_prod(vec), 0.0F);
	}

	TEST(Vec2Test, normalDoubleFloat) {
		auto vec = Vec2(3.5, 5.5);
		auto normal = vec.normal();
		ASSERT_NEAR(normal.dot_prod(vec), 0.0F, FLOAT_ACCEPTED_ERROR);
	}

	TEST(Vec2Test, normalIntFloat) {
		auto vec = Vec2(3, 5);
		auto normal = vec.normal();
		ASSERT_FLOAT_EQ(normal.dot_prod(vec), 0.0F);
	}

	TEST(Vec2Test, normalizedFloat) {
		auto vec = Vec2(3.5F, 5.5F);
		ASSERT_FLOAT_EQ(vec.normalized().magnitude(), 1.0F);
	}

	TEST(Vec2Test, normalizedDouble) {
		auto vec = Vec2(3.5, 5.5);
		ASSERT_FLOAT_EQ(vec.normalized().magnitude(), 1.0F);
	}

	TEST(Vec2Test, normalizedInt) {
		auto vec = Vec2(3, 5);
		ASSERT_NEAR(vec.normalized().magnitude(), 1.0F, FLOAT_ACCEPTED_ERROR);
	}

	TEST(Vec2Test, opNegative) {
		auto vec = Vec2(3, 5);
		ASSERT_EQ(-vec, Vec2(-3, -5));
	}

	TEST(Vec2Test, opPlus) {
		auto vec = Vec2(3, 5);
		auto vec2 = Vec2(3.5F, 5.5F);
		ASSERT_EQ(vec + vec2, Vec2(6.5F, 10.5F));
	}

	TEST(Vec2Test, opPlusEquals) {
		auto vec = Vec2(3, 5);
		auto vec2 = Vec2(3.5F, 5.5F);
		vec += vec2;
		ASSERT_EQ(vec, Vec2(6, 10));
	}

	TEST(Vec2Test, opMinus) {
		auto vec = Vec2(3, 5);
		auto vec2 = Vec2(3.5F, 5.5F);
		ASSERT_EQ(vec - vec2, Vec2(-0.5F, -0.5F));
	}

	TEST(Vec2Test, opMinusEquals) {
		auto vec = Vec2(3, 5);
		auto vec2 = Vec2(3.5F, 5.5F);
		vec -= vec2;
		ASSERT_EQ(vec, Vec2(0, 0));
	}

	TEST(Vec2Test, opMul) {
		auto vec = Vec2(3, 5);
		ASSERT_EQ(vec * 2.5, Vec2(7.5, 12.5));
	}

	TEST(Vec2Test, opMulEquals) {
		auto vec = Vec2(3, 5);
		vec *= 2.5;
		ASSERT_EQ(vec, Vec2(7, 12));
	}

	TEST(Vec2Test, opDivide) {
		auto vec = Vec2(3, 5);
		ASSERT_EQ(vec / 2.5, Vec2(1.2, 2.0));
	}

	TEST(Vec2Test, opDivideEquals) {
		auto vec = Vec2(3, 5);
		vec /= 2.5;
		ASSERT_EQ(vec, Vec2(1, 2));
	}
} // namespace math::test
