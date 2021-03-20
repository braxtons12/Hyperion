#pragma once

#include <cstdint>

#include "../utils/Concepts.h"

namespace math {
#ifndef _MSC_VER
	using std::int32_t;
	using std::size_t;
#endif //_MSC_VER

	using utils::concepts::Numeric, utils::concepts::FloatingPoint;
	class General {
	  public:
		/// @brief Calculates the maximum of the two values
		///
		/// @param x
		/// @param y
		/// @return The maximum of the two
		[[nodiscard]] inline static constexpr auto
		max(Numeric auto left, Numeric auto right) noexcept -> decltype(left) {
			return (left > right ? left : right);
		}

		/// @brief Calculates the minimum of the two values
		///
		/// @param x
		/// @param y
		/// @return The maximum of the two
		[[nodiscard]] inline static constexpr auto
		min(Numeric auto left, Numeric auto right) noexcept -> decltype(left) {
			return (left < right ? left : right);
		}

		/// @brief Calculates the absolute value of x
		///
		/// @param x - The value to take the absolute value of
		/// @return - The absolute value of x
		[[nodiscard]] inline static constexpr auto abs(Numeric auto x) noexcept -> decltype(x) {
			using T = decltype(x);
			const auto sign = x < static_cast<T>(0) ? static_cast<T>(-1) : static_cast<T>(1);
			return x * sign;
		}

		/// @brief Fast approximation calculation of the square root of the given value
		///
		/// @param x - The value to take the square root of
		/// @return - The square root of x
		[[nodiscard]] inline static constexpr auto
		sqrt(FloatingPoint auto x) noexcept -> decltype(x) {
			if constexpr(std::is_same_v<decltype(x), float>) {
				return sqrtf_internal(x);
			}
			else {
				return sqrt_internal(x);
			}
		}

		/// @brief Calculates the truncation of x
		///
		/// @param x - The value to truncate
		/// @return - The truncated value
		[[nodiscard]] inline static constexpr auto
		trunc(FloatingPoint auto x) noexcept -> decltype(x) {
			if constexpr(std::is_same_v<decltype(x), float>) {
				return static_cast<float>(static_cast<std::int64_t>(x));
			}
			else {
				return static_cast<double>(static_cast<std::int64_t>(x));
			}
		}

		/// @brief Calculates the floating point modulus, x mod y
		///
		/// @param x - The moduland
		/// @param y - The dividend
		/// @return x mod y
		[[nodiscard]] inline static constexpr auto
		fmod(FloatingPoint auto x, FloatingPoint auto y) noexcept
			-> decltype(x) requires(std::is_same_v<decltype(x), decltype(y)>) {
			if constexpr(std::is_same_v<decltype(x), float>) {
				return x - trunc<float>(x / y) * y;
			}
			else {
				return x - trunc<double>(x / y) * y;
			}
		}

		/// @brief Calculates the integer rounded version of the given value
		///
		/// @param x - The value to round
		/// @return - The rounded value
		[[nodiscard]] inline static constexpr auto round(FloatingPoint auto x) noexcept -> int32_t {
			if constexpr(std::is_same_v<decltype(x), float>) {
				return static_cast<int32_t>(x + 0.5F);
			}
			else {
				return static_cast<int32_t>(x + 0.5);
			}
		}

		/// @brief Calculates the unsigned integer rounded version of the given value
		///
		/// @param x - The value to round
		/// @return - The rounded value
		[[nodiscard]] inline static constexpr auto roundU(FloatingPoint auto x) noexcept -> size_t {
			if constexpr(std::is_same_v<decltype(x), float>) {
				return static_cast<size_t>(x + 0.5F);
			}
			else {
				return static_cast<size_t>(x + 0.5);
			}
		}

	  private:
		/// @brief Fast approximation calculation of the square root of the given value
		///
		/// @param x - The value to take the square root of
		/// @return - The square root of x
		[[nodiscard]] static constexpr inline auto sqrtf_internal(float x) noexcept -> float {
			const float xhalf = 0.5F * x;
			union // get bits for floating value
			{
				float f = 0.0F;
				int i;
			} u;
			u.f = x;			// NOLINT
								// gives initial guess y0. use 0x5fe6ec85e7de30da for double
			u.i = 0x5F375A86	// NOLINT
				  - (u.i >> 1); // NOLINT
			// Newton method, repeating increases accuracy
			u.f = u.f * (1.5F - xhalf * u.f * u.f); // NOLINT
			// Newton method, repeating increases accuracy
			u.f = u.f * (1.5F - xhalf * u.f * u.f); // NOLINT
			return x * u.f;							// NOLINT
		}

		/// @brief Fast approximation calculation of the square root of the given value
		///
		/// @param x - The value to take the square root of
		/// @return - The square root of x
		[[nodiscard]] static constexpr inline auto sqrt_internal(double x) noexcept -> double {
			const double xhalf = 0.5 * x;
			union // get bits for floating value
			{
				double f = 0.0;
				int64_t i;
			} u;
			u.f = x; // NOLINT
			// gives initial guess y0. use 0x5F375A86 for float
			u.i = 0x5fe6ec85e7de30da - (u.i >> 1); // NOLINT
			// Newton method, repeating increases accuracy
			u.f = u.f * (1.5 - xhalf * u.f * u.f); // NOLINT
			// Newton method, repeating increases accuracy
			u.f = u.f * (1.5 - xhalf * u.f * u.f); // NOLINT
			return x * u.f;						   // NOLINT
		}
	};
} // namespace math
