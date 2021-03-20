#include "../math/test/ExponentialsTestDouble.h"
#include "../math/test/ExponentialsTestFloat.h"
#include "../math/test/GeneralTestDouble.h"
#include "../math/test/GeneralTestFloat.h"
#include "../math/test/TrigFuncsTestDouble.h"
#include "../math/test/TrigFuncsTestFloat.h"
#include "../math/test/Vec2Test.h"
#include "../math/test/Vec3Test.h"
#include "../utils/test/RingBufferTest.h"
#include "gtest/gtest.h"

auto main(int argc, char** argv) -> int {
	testing::InitGoogleTest(&argc, argv);
	testing::FLAGS_gtest_death_test_style = "fast";
	return RUN_ALL_TESTS();
}
