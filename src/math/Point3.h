#pragma once

#include <iostream>

#include "../utils/Concepts.h"
#include "Vec3.h"

namespace math {
	using math::Vec3;
	using math::Vec3Idx;
	using ::utils::concepts::FloatingPoint;
	using ::utils::concepts::SignedIntegral;
	using ::utils::concepts::SignedNumeric;

	using Point3Idx = Vec3Idx;

	template<SignedNumeric T = float>
	class Point3 {
	  public:
		constexpr Point3() noexcept = default;
		constexpr Point3(T x, T y, T z) noexcept : m_vec(x, y, z) {
		}
		template<SignedNumeric TT = T>
		explicit constexpr Point3(const Vec3<TT>& vec) noexcept
			: m_vec(static_cast<T>(vec.x()), static_cast<T>(vec.y()), static_cast<T>(vec.z())) {
		}
		template<SignedNumeric TT = T>
		explicit constexpr Point3(Vec3<TT>&& vec) noexcept
			: m_vec(static_cast<T>(vec.x()), static_cast<T>(vec.y()), static_cast<T>(vec.z())) {
		}
		constexpr Point3(const Point3& point) noexcept = default;
		constexpr Point3(Point3&& point) noexcept = default;
		constexpr ~Point3() noexcept = default;

		inline constexpr auto x() const noexcept -> const T& {
			return m_vec.x();
		}
		inline constexpr auto x() noexcept -> T& {
			return m_vec.x();
		}

		inline constexpr auto y() const noexcept -> const T& {
			return m_vec.y();
		}
		inline constexpr auto y() noexcept -> T& {
			return m_vec.y();
		}

		inline constexpr auto z() const noexcept -> const T& {
			return m_vec.z();
		}
		inline constexpr auto z() noexcept -> T& {
			return m_vec.z();
		}

		inline constexpr auto as_vec() const noexcept -> Vec3<T> {
			return m_vec;
		}

		constexpr auto operator=(const Point3& point) noexcept -> Point3& = default;
		constexpr auto operator=(Point3&& point) noexcept -> Point3& = default;

		inline constexpr auto operator[](Point3Idx i) const noexcept -> T {
			return m_vec[i];
		}
		inline constexpr auto operator[](Point3Idx i) noexcept -> T& {
			return m_vec[i];
		}

		template<SignedNumeric TT = T>
		inline constexpr auto operator+(const Point3<TT>& point) const noexcept -> Point3 {
			return Point3(m_vec + point.m_vec);
		}

		template<SignedNumeric TT = T>
		inline constexpr auto operator+=(const Point3<TT>& point) noexcept -> Point3& {
			m_vec += point.m_vec;
			return *this;
		}

		template<SignedNumeric TT = T>
		inline constexpr auto operator-(const Point3<TT>& point) const noexcept -> Point3 {
			return Point3(m_vec - point.m_vec);
		}

		template<SignedNumeric TT = T>
		inline constexpr auto operator-=(const Point3<TT>& point) noexcept -> Point3& {
			m_vec -= point.m_vec;
			return *this;
		}

		template<SignedNumeric TT = T>
		inline constexpr auto operator+(const Vec3<TT>& vec) const noexcept -> Point3 {
			return Point3(m_vec + vec);
		}

		template<SignedNumeric TT = T>
		inline constexpr auto operator+=(const Vec3<TT>& vec) noexcept -> Point3& {
			m_vec += vec;
			return *this;
		}

		template<SignedNumeric TT = T>
		inline constexpr auto operator-(const Vec3<TT>& vec) const noexcept -> Point3 {
			return Point3(m_vec - vec);
		}

		template<SignedNumeric TT = T>
		inline constexpr auto operator-=(const Vec3<TT>& vec) noexcept -> Point3& {
			m_vec -= vec;
			return *this;
		}

		inline constexpr auto operator*(SignedNumeric auto s) const noexcept -> Point3 {
			return Point3(m_vec * s);
		}

		friend inline constexpr auto
		operator*(SignedNumeric auto lhs, const Point3& rhs) noexcept -> Point3 {
			return rhs * lhs;
		}

		inline constexpr auto operator*=(SignedNumeric auto s) noexcept -> Point3& {
			m_vec *= s;
			return *this;
		}

		inline constexpr auto operator/(SignedNumeric auto s) const noexcept -> Point3 {
			return Point3(m_vec / s);
		}

		friend inline constexpr auto
		operator/(SignedNumeric auto lhs, const Point3& rhs) noexcept -> Point3 {
			return rhs / lhs;
		}

		inline constexpr auto operator/=(SignedNumeric auto s) noexcept -> Point3& {
			m_vec /= s;
			return *this;
		}

		friend inline constexpr auto
		operator<<(std::ostream& out, const Point3& point) noexcept -> std::ostream& {
			return out << point.x() << ' ' << point.y() << ' ' << point.z();
		}

	  private:
		Vec3<T> m_vec = Vec3<T>();
	};

	template<FloatingPoint T>
	explicit Point3(T, T, T) -> Point3<T>;

	template<SignedIntegral T>
	explicit Point3(T, T, T) -> Point3<T>;

} // namespace math
