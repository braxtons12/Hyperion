#pragma once

#include <gsl/gsl>
#include <memory>
#include <tuple>

#include "../math/Constants.h"
#include "../math/Exponentials.h"
#include "../math/General.h"
#include "../math/Point2.h"
#include "../math/Point3.h"
#include "../math/Random.h"
#include "../math/TrigFuncs.h"
#include "../math/Vec2.h"
#include "../math/Vec3.h"
#include "../utils/Concepts.h"
/// @brief custom mathematics implementaitons
namespace math { } // namespace math

/// @brief utility types
namespace utils { } // namespace utils

using utils::concepts::ConstructibleFrom;		// NOLINT
using utils::concepts::Copyable;				// NOLINT
using utils::concepts::CopyOrMovable;			// NOLINT
using utils::concepts::DefaultConstructible;	// NOLINT
using utils::concepts::Derived;					// NOLINT
using utils::concepts::FloatingPoint;			// NOLINT
using utils::concepts::Integral;				// NOLINT
using utils::concepts::Movable;					// NOLINT
using utils::concepts::NotCopyable;				// NOLINT
using utils::concepts::NotCopyOrMovable;		// NOLINT
using utils::concepts::NotDefaultConstructible; // NOLINT
using utils::concepts::NotMovable;				// NOLINT
using utils::concepts::NotPassable;				// NOLINT
using utils::concepts::NotPointer;				// NOLINT
using utils::concepts::NotReference;			// NOLINT
using utils::concepts::NotSemiRegular;			// NOLINT
using utils::concepts::Numeric;					// NOLINT
using utils::concepts::Passable;				// NOLINT
using utils::concepts::Pointer;					// NOLINT
using utils::concepts::Reference;				// NOLINT
using utils::concepts::SemiRegular;				// NOLINT
using utils::concepts::SignedIntegral;			// NOLINT
using utils::concepts::SignedNumeric;			// NOLINT

using math::Constants;	  // NOLINT
using math::Exponentials; // NOLINT
using math::General;	  // NOLINT
using math::Point2;		  // NOLINT
using math::Point2Idx;	  // NOLINT
using math::Point3;		  // NOLINT
using math::Point3Idx;	  // NOLINT
using math::random_value; // NOLINT
using math::Trig;		  // NOLINT
using math::Vec2;		  // NOLINT
using math::Vec2Idx;	  // NOLINT
using math::Vec3;		  // NOLINT
using math::Vec3Idx;	  // NOLINT

using gsl::narrow_cast; // NOLINT
template<typename T>
using NotNull = gsl::not_null<T*>; // NOLINT
template<typename T>
using Owner = gsl::owner<T*>; // NOLINT

template<FloatingPoint T = float>
inline constexpr auto degrees_to_radians(T degrees) noexcept -> T {
	return degrees * Constants<T>::pi / narrow_cast<T>(180.0);
}

template<FloatingPoint T = float>
inline constexpr auto radians_to_degrees(T radians) noexcept -> T {
	return radians * narrow_cast<T>(180.0) / Constants<T>::pi;
}

template<SignedNumeric T = float>
inline constexpr auto clamp(T val, T min, T max) noexcept -> T {
	if(val < min) {
		return min;
	}
	else if(val > max) {
		return max;
	}
	else {
		return val;
	}
}

template<typename... Args>
inline constexpr auto ignore(Args&&... args) noexcept -> void {
	std::ignore = std::tuple<Args...>(args...);
}

// clang-format off
#ifndef _MSC_VER
	// NOLINTNEXTLINE
	#define IGNORE_UNUSED_MACROS_START \
		_Pragma("GCC diagnostic push")\
		_Pragma("GCC diagnostic ignored \"-Wunused-macros\"")
#else
	// NOLINTNEXTLINE
	#define IGNORE_UNUSED_MACROS_START
#endif
// clang-format on

// clang-format off
#ifndef _MSC_VER
	// NOLINTNEXTLINE
	#define IGNORE_UNUSED_MACROS_STOP \
		_Pragma("GCC diagnostic pop")
#else
	// NOLINTNEXTLINE
	#define IGNORE_UNUSED_MACROS_STOP
#endif
// clang-format on

IGNORE_UNUSED_MACROS_START

// clang-format off
#ifndef _MSC_VER
	// NOLINTNEXTLINE
	#define IGNORE_PADDING_START \
		_Pragma("GCC diagnostic push") \
		_Pragma("GCC diagnostic ignored \"-Wpadded\"")
#else
	// NOLINTNEXTLINE
	#define IGNORE_PADDING_START \
		_Pragma("warning( push )") \
		_Pragma("warning( disable : 4820 )")
#endif
// clang-format on

// clang-format off
#ifndef _MSC_VER
	// NOLINTNEXTLINE
	#define IGNORE_PADDING_STOP \
		_Pragma("GCC diagnostic pop")
#else
	// NOLINTNEXTLINE
	#define IGNORE_PADDING_STOP \
		_Pragma("warning( pop )")
#endif
// clang-format on

// clang-format off
#ifndef _MSC_VER
	// NOLINTNEXTLINE
	#define IGNORE_UNUSED_TEMPLATES_START \
		_Pragma("GCC diagnostic push")\
		_Pragma("GCC diagnostic ignored \"-Wunused-template\"")
#else
	// NOLINTNEXTLINE
	#define IGNORE_UNUSED_TEMPLATES_START
#endif
// clang-format on

// clang-format off
#ifndef _MSC_VER
	// NOLINTNEXTLINE
	#define IGNORE_UNUSED_TEMPLATES_STOP \
		_Pragma("GCC diagnostic pop")
#else
	// NOLINTNEXTLINE
	#define IGNORE_UNUSED_TEMPLATES_STOP
#endif
// clang-format on

IGNORE_UNUSED_MACROS_STOP
