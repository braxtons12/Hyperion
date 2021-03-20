#pragma once

#include <gsl/gsl>
#include <iostream>

#include "../utils/Concepts.h"
#include "General.h"
#include "Random.h"

namespace math {
	using gsl::narrow_cast;
	using utils::concepts::SignedNumeric, utils::concepts::Integral,
		utils::concepts::SignedIntegral, utils::concepts::FloatingPoint;

	enum class Vec2Idx : size_t
	{
		X = 0ULL,
		Y
	};

	template<SignedNumeric T = float>
	class Vec2 {
	  public:
		/// @brief Creates a default `Vec2`
		constexpr Vec2() noexcept = default;

		/// @brief Creates a new `Vec2` with the given x and y components
		///
		/// @param x - The x component
		/// @param y - The y component
		constexpr Vec2(T x, T y) noexcept : elements{x, y} {
		}
		constexpr Vec2(const Vec2& vec) noexcept = default;
		constexpr Vec2(Vec2&& vec) noexcept = default;
		constexpr ~Vec2() noexcept = default;

		/// @brief Returns the x component
		///
		/// @return a const ref to the x component
		[[nodiscard]] inline constexpr auto x() const noexcept -> const T& {
			return elements[X];
		}

		/// @brief Returns the x component
		///
		/// @return a mutable (ie: non-const) ref to the x component
		inline constexpr auto x() noexcept -> T& {
			return elements[X];
		}

		/// @brief Returns the y component
		///
		/// @return a const ref to the y component
		[[nodiscard]] inline constexpr auto y() const noexcept -> const T& {
			return elements[Y];
		}

		/// @brief Returns the y component
		///
		/// @return a mutable (ie: non-const) ref to the y component
		inline constexpr auto y() noexcept -> T& {
			return elements[Y];
		}

		/// @brief Returns the magnitude (length) of the vector
		///
		/// @return The magnitude
		template<FloatingPoint TT = float>
		[[nodiscard]] inline constexpr auto magnitude() const noexcept -> TT {
			return General::sqrt(narrow_cast<TT>(magnitude_squared()));
		}

		/// @brief Returns the dot product of this and `vec`
		///
		/// @param vec - The vector to perform the dot product with
		///
		/// @return The dot product
		template<FloatingPoint TT = float>
		[[nodiscard]] inline constexpr auto dot_prod(const Vec2<TT>& vec) const noexcept -> TT {
			return narrow_cast<TT>(x()) * vec.x() + narrow_cast<TT>(y()) * vec.y();
		}

		/// @brief Returns the dot product of this and `vec`
		///
		/// @param vec - The vector to perform the dot product with
		///
		/// @return The dot product
		template<SignedIntegral TT = int>
		[[nodiscard]] inline constexpr auto dot_prod(const Vec2<TT>& vec) const noexcept -> T {
			return x() * narrow_cast<T>(vec.x()) + y() * narrow_cast<T>(vec.y());
		}

		/// @brief Performs the 2D equivalent to the cross product
		/// @note This is equivalent to the z component of a 3D cross product
		///
		/// @param vec The vector to perform the cross product with
		///
		/// @return The 2D cross product
		template<FloatingPoint TT = float>
		[[nodiscard]] inline constexpr auto cross_prod(const Vec2<TT>& vec) const noexcept -> TT {
			return narrow_cast<TT>(x()) * vec.y() - narrow_cast<TT>(y()) * vec.x();
		}

		/// @brief Performs the 2D equivalent to the cross product
		/// @note This is equivalent to the z component of a 3D cross product
		///
		/// @param vec The vector to perform the cross product with
		///
		/// @return The 2D cross product
		template<SignedIntegral TT = int>
		[[nodiscard]] inline constexpr auto cross_prod(const Vec2<TT>& vec) const noexcept -> T {
			return x() * narrow_cast<T>(vec.y()) - y() * narrow_cast<T>(vec.x());
		}

		/// @brief Returns **a** vector normal to this one
		/// @note this is not necessarily the **only** vector normal to this one
		///
		/// @return a vector normal to this
		template<FloatingPoint TT = float>
		[[nodiscard]] inline constexpr auto normal() const noexcept -> Vec2<TT> {
			constexpr auto _x = narrow_cast<TT>(1.0);
			const auto _y = (-_x * narrow_cast<TT>(x())) / narrow_cast<TT>(y());
			return {_x, _y};
		}

		/// @brief Returns this vector with normalized magnitude
		///
		/// @return this vector, normalized
		template<FloatingPoint TT = float>
		[[nodiscard]] inline constexpr auto normalized() const noexcept -> Vec2<TT> {
			return std::move(*this / magnitude<TT>());
		}

		template<SignedNumeric TT = float>
		[[nodiscard]] inline static constexpr auto random() noexcept -> Vec2<TT> {
			return {random_value<TT>(), random_value<TT>()};
		}

		template<SignedNumeric TT = float>
		[[nodiscard]] inline static constexpr auto random(TT min, TT max) noexcept -> Vec2<TT> {
			return {random_value<TT>(min, max), random_value<TT>(min, max)};
		}

		template<FloatingPoint TT = float>
		[[nodiscard]] inline static constexpr auto random_in_unit_circle() noexcept -> Vec2<TT> {
			do {
				auto val = random(narrow_cast<TT>(-1), narrow_cast<TT>(1));
				if(val.magnitude_squared() < narrow_cast<TT>(1)) {
					return val;
				}
			} while(true);
		}

		constexpr auto operator=(const Vec2& vec) noexcept -> Vec2& = default;
		constexpr auto operator=(Vec2&& vec) noexcept -> Vec2& = default;

		template<FloatingPoint TT = float>
		inline constexpr auto operator==(const Vec2<TT>& vec) const noexcept -> bool {
			const auto xEqual
				= General::abs<TT>(narrow_cast<TT>(x()) - vec.x()) < narrow_cast<TT>(0.01);
			const auto yEqual
				= General::abs<TT>(narrow_cast<TT>(y()) - vec.y()) < narrow_cast<TT>(0.01);
			return xEqual && yEqual;
		}

		template<SignedIntegral TT = int>
		inline constexpr auto operator==(const Vec2<TT>& vec) const noexcept -> bool {
			if constexpr(FloatingPoint<T>) {
				const auto xEqual
					= General::abs<T>(x() - narrow_cast<T>(vec.x())) < narrow_cast<TT>(0.01);
				const auto yEqual
					= General::abs<T>(y() - narrow_cast<T>(vec.y())) < narrow_cast<TT>(0.01);
				return xEqual && yEqual;
			}
			else {
				return x() == narrow_cast<T>(vec.x()) && y() == narrow_cast<T>(vec.y());
			}
		}

		template<SignedNumeric TT = T>
		inline constexpr auto operator!=(const Vec2<TT>& vec) const noexcept -> bool {
			return !(*this == vec);
		}

		inline constexpr auto operator-() const noexcept -> Vec2 {
			return {-x(), -y()};
		}

		inline constexpr auto operator[](Vec2Idx i) const noexcept -> T {
			const auto index = static_cast<size_t>(i);
			return elements[index]; // NOLINT
		}
		inline constexpr auto operator[](Vec2Idx i) noexcept -> T& {
			const auto index = static_cast<size_t>(i);
			return elements[index]; // NOLINT
		}

		template<FloatingPoint TT = float>
		inline constexpr auto operator+(const Vec2<TT>& vec) const noexcept -> Vec2<TT> {
			return {narrow_cast<TT>(x()) + vec.x(), narrow_cast<TT>(y()) + vec.y()};
		}

		template<SignedIntegral TT = int>
		inline constexpr auto operator+(const Vec2<TT>& vec) const noexcept -> Vec2<T> {
			return {x() + narrow_cast<T>(vec.x()), y() + narrow_cast<T>(vec.y())};
		}

		template<SignedNumeric TT = T>
		inline constexpr auto operator+=(const Vec2<TT>& vec) noexcept -> Vec2& {
			x() += narrow_cast<T>(vec.x());
			y() += narrow_cast<T>(vec.y());
			return *this;
		}

		template<FloatingPoint TT = float>
		inline constexpr auto operator-(const Vec2<TT>& vec) const noexcept -> Vec2<TT> {
			return {narrow_cast<TT>(x()) - vec.x(), narrow_cast<TT>(y()) - vec.y()};
		}

		template<SignedIntegral TT = int>
		inline constexpr auto operator-(const Vec2<TT>& vec) const noexcept -> Vec2<T> {
			return {x() - narrow_cast<T>(vec.x()), y() - narrow_cast<T>(vec.y())};
		}

		template<SignedNumeric TT = T>
		inline constexpr auto operator-=(const Vec2<TT>& vec) noexcept -> Vec2& {
			x() -= narrow_cast<T>(vec.x());
			y() -= narrow_cast<T>(vec.y());
			return *this;
		}

		inline constexpr auto operator*(FloatingPoint auto s) const noexcept -> Vec2<decltype(s)> {
			using TT = decltype(s);
			return {narrow_cast<TT>(x()) * s, narrow_cast<TT>(y()) * s};
		}

		inline constexpr auto operator*(SignedIntegral auto s) const noexcept -> Vec2 {
			auto scalar = narrow_cast<T>(s);
			return {x() * scalar, y() * scalar};
		}

		inline constexpr auto operator*=(FloatingPoint auto s) noexcept -> Vec2& {
			using TT = decltype(s);
			x() = narrow_cast<T>(narrow_cast<TT>(x()) * s);
			y() = narrow_cast<T>(narrow_cast<TT>(y()) * s);
			return *this;
		}

		inline constexpr auto operator*=(SignedIntegral auto s) noexcept -> Vec2& {
			auto scalar = narrow_cast<T>(s);
			x() *= scalar;
			y() *= scalar;
			return *this;
		}

		friend inline constexpr auto
		operator*(FloatingPoint auto lhs, const Vec2& rhs) noexcept -> Vec2<decltype(lhs)> {
			return rhs * lhs;
		}

		friend inline constexpr auto
		operator*(SignedIntegral auto lhs, const Vec2& rhs) noexcept -> Vec2 {
			return rhs * lhs;
		}

		inline constexpr auto operator/(FloatingPoint auto s) const noexcept -> Vec2<decltype(s)> {
			using TT = decltype(s);
			return {narrow_cast<TT>(x()) / s, narrow_cast<TT>(y()) / s};
		}

		inline constexpr auto operator/(SignedIntegral auto s) const noexcept -> Vec2 {
			auto scalar = narrow_cast<T>(s);
			return {x() / scalar, y() / scalar};
		}

		friend inline constexpr auto
		operator/(FloatingPoint auto lhs, const Vec2& rhs) noexcept -> Vec2<decltype(lhs)> {
			return rhs / lhs;
		}

		friend inline constexpr auto
		operator/(SignedIntegral auto lhs, const Vec2& rhs) noexcept -> Vec2 {
			return rhs / lhs;
		}

		inline constexpr auto operator/=(FloatingPoint auto s) noexcept -> Vec2 {
			using TT = decltype(s);
			x() = narrow_cast<T>(narrow_cast<TT>(x()) / s);
			y() = narrow_cast<T>(narrow_cast<TT>(y()) / s);
			return *this;
		}

		inline constexpr auto operator/=(SignedIntegral auto s) noexcept -> Vec2 {
			auto scalar = narrow_cast<T>(s);
			x() /= scalar;
			y() /= scalar;
			return *this;
		}

		friend inline constexpr auto
		operator<<(std::ostream& out, const Vec2& vec) noexcept -> std::ostream& {
			return out << vec.x() << ' ' << vec.y();
		}

	  private:
		static constexpr size_t NUM_ELEMENTS = static_cast<size_t>(Vec2Idx::Y) + 1;
		T elements[NUM_ELEMENTS] = {narrow_cast<T>(0), narrow_cast<T>(0)}; // NOLINT

		/// @brief Calculates the magnitude squared of this vector
		///
		/// @return The magnitude squared
		[[nodiscard]] inline constexpr auto magnitude_squared() const noexcept -> T {
			return x() * x() + y() * y();
		}

		/// Index for x component
		static constexpr size_t X = static_cast<size_t>(Vec2Idx::X);
		/// Index for y component
		static constexpr size_t Y = static_cast<size_t>(Vec2Idx::Y);
	};

	template<FloatingPoint T>
	explicit Vec2(T, T) -> Vec2<T>;

	template<SignedIntegral T>
	explicit Vec2(T, T) -> Vec2<T>;
} // namespace math
