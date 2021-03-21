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

	enum class Vec3Idx : size_t
	{
		X = 0ULL,
		Y,
		Z
	};

	template<SignedNumeric T = float>
	class Vec3 {
	  public:
		/// @brief Creates a default `Vec3`
		constexpr Vec3() noexcept = default;

		/// @brief Creates a new `Vec3` with the given x, y, and z components
		///
		/// @param x - The x component
		/// @param y - The y component
		/// @param z - The z component
		constexpr Vec3(T x, T y, T z) noexcept : elements{x, y, z} {
		}
		constexpr Vec3(const Vec3& vec) noexcept = default;
		constexpr Vec3(Vec3&& vec) noexcept = default;
		constexpr ~Vec3() noexcept = default;

		/// @brief Returns the x component
		///
		/// @return a const ref to the x component
		[[nodiscard]] inline constexpr auto x() const noexcept -> const T& {
			return elements[X];
		}

		/// @brief Returns the x component
		///
		/// @return a mutable (ie: non-const) ref to the x component
		[[nodiscard]] inline constexpr auto x() noexcept -> T& {
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
		[[nodiscard]] inline constexpr auto y() noexcept -> T& {
			return elements[Y];
		}

		/// @brief Returns the z component
		///
		/// @return a const ref to the z component
		[[nodiscard]] inline constexpr auto z() const noexcept -> const T& {
			return elements[Z];
		}

		/// @brief Returns the z component
		///
		/// @return a mutable (ie: non-const) ref to the z component
		[[nodiscard]] inline constexpr auto z() noexcept -> T& {
			return elements[Z];
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
		[[nodiscard]] inline constexpr auto dot_prod(const Vec3<TT>& vec) const noexcept -> TT {
			return narrow_cast<TT>(x()) * vec.x() + narrow_cast<TT>(y()) * vec.y()
				   + narrow_cast<TT>(z()) * vec.z();
		}

		/// @brief Returns the dot product of this and `vec`
		///
		/// @param vec - The vector to perform the dot product with
		///
		/// @return The dot product
		template<SignedIntegral TT = int>
		[[nodiscard]] inline constexpr auto dot_prod(const Vec3<TT>& vec) const noexcept -> T {
			return x() * narrow_cast<T>(vec.x()) + y() * narrow_cast<T>(vec.y())
				   + z() * narrow_cast<T>(vec.z());
		}

		/// @brief Performs the cross product
		///
		/// @param vec The vector to perform the cross product with
		///
		/// @return The cross product
		template<FloatingPoint TT = float>
		[[nodiscard]] inline constexpr auto
		cross_prod(const Vec3<TT>& vec) const noexcept -> Vec3<TT> {
			const auto _x = narrow_cast<TT>(y()) * vec.z() - narrow_cast<TT>(z()) * vec.y();
			const auto _y = narrow_cast<TT>(z()) * vec.x() - narrow_cast<TT>(x()) * vec.z();
			const auto _z = narrow_cast<TT>(x()) * vec.y() - narrow_cast<TT>(y()) * vec.x();
			return {_x, _y, _z};
		}

		/// @brief Performs the cross product
		///
		/// @param vec The vector to perform the cross product with
		///
		/// @return The cross product
		template<SignedIntegral TT = int>
		[[nodiscard]] inline constexpr auto cross_prod(const Vec3<TT>& vec) const noexcept -> Vec3 {
			const auto _x = y() * narrow_cast<T>(vec.z()) - z() * narrow_cast<T>(vec.y());
			const auto _y = z() * narrow_cast<T>(vec.x()) - x() * narrow_cast<T>(vec.z());
			const auto _z = x() * narrow_cast<T>(vec.y()) - y() * narrow_cast<T>(vec.x());
			return {_x, _y, _z};
		}

		/// @brief Returns **a** vector normal to this one
		/// @note this is not necessarily the **only** vector normal to this one
		///
		/// @return a vector normal to this
		[[nodiscard]] inline constexpr auto normal() const noexcept -> Vec3 {
			return cross_prod(
				Vec3<T>(narrow_cast<T>(1.0), narrow_cast<T>(0.0), narrow_cast<T>(0.0)));
		}

		/// @brief Returns this vector with normalized magnitude
		///
		/// @return this vector, normalized
		template<FloatingPoint TT = float>
		[[nodiscard]] inline constexpr auto normalized() const noexcept -> Vec3<TT> {
			return std::move(*this / magnitude<TT>());
		}

		template<SignedNumeric TT = float>
		[[nodiscard]] inline static constexpr auto random() noexcept -> Vec3<TT> {
			return {random_value<TT>(), random_value<TT>(), random_value<TT>()};
		}

		template<SignedNumeric TT = float>
		[[nodiscard]] inline static constexpr auto random(TT min, TT max) noexcept -> Vec3<TT> {
			return {random_value<TT>(min, max),
					random_value<TT>(min, max),
					random_value<TT>(min, max)};
		}

		template<FloatingPoint TT = float>
		[[nodiscard]] inline static constexpr auto random_in_unit_sphere() noexcept -> Vec3<TT> {
			do {
				auto val = random<TT>(narrow_cast<TT>(-1), narrow_cast<TT>(1));
				if(narrow_cast<TT>(val.magnitude_squared()) < narrow_cast<TT>(1)) {
					return val;
				}
			} while(true);
		}

		template<FloatingPoint TT = float>
		[[nodiscard]] inline static constexpr auto random_in_unit_disk() noexcept -> Vec3<TT> {
			do {
				auto val = random(narrow_cast<TT>(-1), narrow_cast<TT>(1));
				val.z() = narrow_cast<TT>(0);
				if(narrow_cast<TT>(val.magnitude_squared()) < narrow_cast<TT>(1)) {
					return val;
				}
			} while(true);
		}

		[[nodiscard]] inline constexpr auto is_approx_zero() noexcept -> bool {
			constexpr auto zero_tolerance = narrow_cast<T>(0.0001);
			return (General::abs(x()) < zero_tolerance) && (General::abs(y()) < zero_tolerance)
				   && (General::abs(z()) < zero_tolerance);
		}

		[[nodiscard]] inline constexpr auto
		reflected(const Vec3& surface_normal) const noexcept -> Vec3 {
			return std::move(
				*this - narrow_cast<T>(2) * (this->dot_prod(surface_normal) * surface_normal));
		}

		[[nodiscard]] inline constexpr auto
		refracted(const Vec3& surface_normal, T eta_external_over_eta_internal) noexcept -> Vec3 {
			const auto uv = *this;
			const auto cos_theta = General::min((-uv).dot_prod(surface_normal), narrow_cast<T>(1));

			auto out_perpendicular
				= eta_external_over_eta_internal * (uv + cos_theta * surface_normal);
			auto out_parallel = -General::sqrt(General::abs(
									narrow_cast<T>(1) - out_perpendicular.magnitude_squared()))
								* surface_normal;
			return out_perpendicular + out_parallel;
		}

		constexpr auto operator=(const Vec3& vec) noexcept -> Vec3& = default;
		constexpr auto operator=(Vec3&& vec) noexcept -> Vec3& = default;

		template<FloatingPoint TT = float>
		inline constexpr auto operator==(const Vec3<TT>& vec) const noexcept -> bool {
			const auto xEqual
				= General::abs<TT>(narrow_cast<TT>(x()) - vec.x()) < narrow_cast<TT>(0.01);
			const auto yEqual
				= General::abs<TT>(narrow_cast<TT>(y()) - vec.y()) < narrow_cast<TT>(0.01);
			const auto zEqual
				= General::abs<TT>(narrow_cast<TT>(z()) - vec.z()) < narrow_cast<TT>(0.01);
			return xEqual && yEqual && zEqual;
		}

		template<SignedIntegral TT = int>
		inline constexpr auto operator==(const Vec3<TT>& vec) const noexcept -> bool {
			if constexpr(FloatingPoint<T>) {
				const auto xEqual
					= General::abs<T>(x() - narrow_cast<T>(vec.x())) < narrow_cast<TT>(0.01);
				const auto yEqual
					= General::abs<T>(y() - narrow_cast<T>(vec.y())) < narrow_cast<TT>(0.01);
				const auto zEqual
					= General::abs<T>(z() - narrow_cast<T>(vec.z())) < narrow_cast<TT>(0.01);
				return xEqual && yEqual && zEqual;
			}
			else {
				return x() == narrow_cast<T>(vec.x()) && y() == narrow_cast<T>(vec.y())
					   && z() == narrow_cast<T>(vec.z());
			}
		}

		template<SignedNumeric TT = T>
		inline constexpr auto operator!=(const Vec3<TT>& vec) const noexcept -> bool {
			return !(*this == vec);
		}

		inline constexpr auto operator-() const noexcept -> Vec3 {
			return {-x(), -y(), -z()};
		}

		inline constexpr auto operator[](Vec3Idx i) const noexcept -> T {
			const auto index = static_cast<size_t>(i);
			return elements[index]; // NOLINT
		}
		inline constexpr auto operator[](Vec3Idx i) noexcept -> T& {
			const auto index = static_cast<size_t>(i);
			return elements[index]; // NOLINT
		}

		template<FloatingPoint TT = float>
		inline constexpr auto operator+(const Vec3<TT>& vec) const noexcept -> Vec3<TT> {
			return {narrow_cast<TT>(x()) + vec.x(),
					narrow_cast<TT>(y()) + vec.y(),
					narrow_cast<TT>(z()) + vec.z()};
		}

		template<SignedIntegral TT = int>
		inline constexpr auto operator+(const Vec3<TT>& vec) const noexcept -> Vec3 {
			return {x() + narrow_cast<T>(vec.x()),
					y() + narrow_cast<T>(vec.y()),
					z() + narrow_cast<T>(vec.z())};
		}

		template<SignedNumeric TT = T>
		inline constexpr auto operator+=(const Vec3<TT>& vec) noexcept -> Vec3 {
			x() += narrow_cast<T>(vec.x());
			y() += narrow_cast<T>(vec.y());
			z() += narrow_cast<T>(vec.z());
			return *this;
		}

		template<FloatingPoint TT = float>
		inline constexpr auto operator-(const Vec3<TT>& vec) const noexcept -> Vec3<TT> {
			return {narrow_cast<TT>(x()) - vec.x(),
					narrow_cast<TT>(y()) - vec.y(),
					narrow_cast<TT>(z()) - vec.z()};
		}

		template<SignedIntegral TT = int>
		inline constexpr auto operator-(const Vec3<TT>& vec) const noexcept -> Vec3 {
			return {x() - narrow_cast<T>(vec.x()),
					y() - narrow_cast<T>(vec.y()),
					z() - narrow_cast<T>(vec.z())};
		}

		template<SignedNumeric TT = T>
		inline constexpr auto operator-=(const Vec3<TT>& vec) noexcept -> Vec3& {
			x() -= narrow_cast<T>(vec.x());
			y() -= narrow_cast<T>(vec.y());
			z() -= narrow_cast<T>(vec.z());
			return *this;
		}

		inline constexpr auto operator*(FloatingPoint auto s) const noexcept -> Vec3<decltype(s)> {
			using TT = decltype(s);
			return {narrow_cast<TT>(x()) * s, narrow_cast<TT>(y()) * s, narrow_cast<TT>(z()) * s};
		}

		inline constexpr auto operator*(SignedIntegral auto s) const noexcept -> Vec3 {
			auto scalar = narrow_cast<T>(s);
			return {x() * scalar, y() * scalar, z() * scalar};
		}

		friend inline constexpr auto
		operator*(FloatingPoint auto lhs, const Vec3& rhs) noexcept -> Vec3<decltype(lhs)> {
			return rhs * lhs;
		}

		friend inline constexpr auto
		operator*(SignedIntegral auto lhs, const Vec3& rhs) noexcept -> Vec3 {
			return rhs * lhs;
		}

		inline constexpr auto operator*=(FloatingPoint auto s) noexcept -> Vec3& {
			using TT = decltype(s);
			x() = narrow_cast<T>(narrow_cast<TT>(x()) * s);
			y() = narrow_cast<T>(narrow_cast<TT>(y()) * s);
			z() = narrow_cast<T>(narrow_cast<TT>(z()) * s);
			return *this;
		}

		inline constexpr auto operator*=(SignedIntegral auto s) noexcept -> Vec3& {
			auto scalar = narrow_cast<T>(s);
			x() *= scalar;
			y() *= scalar;
			z() *= scalar;
			return *this;
		}

		inline constexpr auto operator/(FloatingPoint auto s) const noexcept -> Vec3<decltype(s)> {
			using TT = decltype(s);
			return {narrow_cast<TT>(x()) / s, narrow_cast<TT>(y()) / s, narrow_cast<TT>(z()) / s};
		}

		inline constexpr auto operator/(SignedIntegral auto s) const noexcept -> Vec3 {
			auto scalar = narrow_cast<T>(s);
			return {x() / scalar, y() / scalar, z() / scalar};
		}

		friend inline constexpr auto
		operator/(FloatingPoint auto lhs, const Vec3& rhs) noexcept -> Vec3<decltype(lhs)> {
			return rhs / lhs;
		}

		friend inline constexpr auto
		operator/(SignedIntegral auto lhs, const Vec3& rhs) noexcept -> Vec3 {
			return rhs / lhs;
		}

		inline constexpr auto operator/=(FloatingPoint auto s) noexcept -> Vec3& {
			using TT = decltype(s);
			x() = narrow_cast<T>(narrow_cast<TT>(x()) / s);
			y() = narrow_cast<T>(narrow_cast<TT>(y()) / s);
			z() = narrow_cast<T>(narrow_cast<TT>(z()) / s);
			return *this;
		}

		inline constexpr auto operator/=(SignedIntegral auto s) noexcept -> Vec3& {
			auto scalar = narrow_cast<T>(s);
			x() /= scalar;
			y() /= scalar;
			z() /= scalar;
			return *this;
		}

		friend inline constexpr auto
		operator<<(std::ostream& out, const Vec3& vec) noexcept -> std::ostream& {
			return out << vec.x() << ' ' << vec.y() << ' ' << vec.z();
		}

	  private:
		static constexpr size_t NUM_ELEMENTS = static_cast<size_t>(Vec3Idx::Z) + 1;
		T elements[NUM_ELEMENTS] // NOLINT
			= {narrow_cast<T>(0), narrow_cast<T>(0), narrow_cast<T>(0)};

		/// @brief Calculates the magnitude squared of this vector
		///
		/// @return The magnitude squared
		[[nodiscard]] inline constexpr auto magnitude_squared() const noexcept -> T {
			return x() * x() + y() * y() + z() * z();
		}

		/// Index for x component
		static constexpr size_t X = static_cast<size_t>(Vec3Idx::X);
		/// Index for y component
		static constexpr size_t Y = static_cast<size_t>(Vec3Idx::Y);
		/// Index for z component
		static constexpr size_t Z = static_cast<size_t>(Vec3Idx::Z);
	};

	// Deduction Guides

	template<FloatingPoint T>
	explicit Vec3(T, T, T) -> Vec3<T>;

	template<SignedIntegral T>
	explicit Vec3(T, T, T) -> Vec3<T>;

} // namespace math
