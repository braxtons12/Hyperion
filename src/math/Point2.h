#pragma once

#include <iostream>

#include "../utils/Concepts.h"
#include "Vec2.h"

namespace math {
	using math::Vec2;
	using math::Vec2Idx;
	using ::utils::concepts::FloatingPoint;
	using ::utils::concepts::SignedIntegral;
	using ::utils::concepts::SignedNumeric;

	using Point2Idx = Vec2Idx;

	template<SignedNumeric T = float>
	class Point2 {
	  public:
		constexpr Point2() noexcept = default;
		constexpr Point2(T x, T y) noexcept : m_vec(x, y) {
		}
		template<SignedNumeric TT = T>
		explicit constexpr Point2(const Vec2<TT>& vec) noexcept
			: m_vec(static_cast<T>(vec.x()), static_cast<T>(vec.y())) {
		}
		template<SignedNumeric TT = T>
		explicit constexpr Point2(Vec2<TT>&& vec) noexcept
			: m_vec(static_cast<T>(vec.x()), static_cast<T>(vec.y())) {
		}
		constexpr Point2(const Point2& point) noexcept = default;
		constexpr Point2(Point2&& point) noexcept = default;
		constexpr ~Point2() noexcept = default;

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

		inline constexpr auto as_vec() const noexcept -> Vec2<T> {
			return m_vec;
		}

		constexpr auto operator=(const Point2& point) noexcept -> Point2& = default;
		constexpr auto operator=(Point2&& point) noexcept -> Point2& = default;

		inline constexpr auto operator[](Point2Idx i) const noexcept -> T {
			return m_vec[i];
		}
		inline constexpr auto operator[](Point2Idx i) noexcept -> T& {
			return m_vec[i];
		}

		template<SignedNumeric TT = T>
		inline constexpr auto operator+(const Point2<TT>& point) const noexcept -> Point2 {
			return Point2(m_vec + point.m_vec);
		}

		template<SignedNumeric TT = T>
		inline constexpr auto operator+=(const Point2<TT>& point) noexcept -> Point2& {
			m_vec += point.m_vec;
			return *this;
		}

		template<SignedNumeric TT = T>
		inline constexpr auto operator-(const Point2<TT>& point) const noexcept -> Point2 {
			return Point2(m_vec - point.m_vec);
		}

		template<SignedNumeric TT = T>
		inline constexpr auto operator-=(const Point2<TT>& point) noexcept -> Point2& {
			m_vec -= point.m_vec;
			return *this;
		}

		template<SignedNumeric TT = T>
		inline constexpr auto operator+(const Vec2<TT>& vec) const noexcept -> Point2 {
			return Point2(m_vec + vec);
		}

		template<SignedNumeric TT = T>
		inline constexpr auto operator+=(const Vec2<TT>& vec) noexcept -> Point2& {
			m_vec += vec;
			return *this;
		}

		template<SignedNumeric TT = T>
		inline constexpr auto operator-(const Vec2<TT>& vec) const noexcept -> Point2 {
			return Point2(m_vec - vec);
		}

		template<SignedNumeric TT = T>
		inline constexpr auto operator-=(const Vec2<TT>& vec) noexcept -> Point2& {
			m_vec -= vec;
			return *this;
		}

		inline constexpr auto operator*(SignedNumeric auto s) const noexcept -> Point2 {
			return Point2(m_vec * s);
		}

		friend inline constexpr auto
		operator*(SignedNumeric auto lhs, const Point2& rhs) noexcept -> Point2 {
			return rhs * lhs;
		}

		inline constexpr auto operator*=(SignedNumeric auto s) noexcept -> Point2& {
			m_vec *= s;
			return *this;
		}

		inline constexpr auto operator/(SignedNumeric auto s) const noexcept -> Point2 {
			return Point2(m_vec / s);
		}

		friend inline constexpr auto
		operator/(SignedNumeric auto lhs, const Point2& rhs) noexcept -> Point2 {
			return rhs / lhs;
		}

		inline constexpr auto operator/=(SignedNumeric auto s) noexcept -> Point2& {
			m_vec /= s;
			return *this;
		}

		friend inline constexpr auto
		operator<<(std::ostream& out, const Point2& point) noexcept -> std::ostream& {
			return out << point.x() << ' ' << point.y() << ' ' << point.z();
		}

	  private:
		Vec2<T> m_vec = Vec2<T>();
	};

	template<FloatingPoint T>
	explicit Point2(T, T) -> Point2<T>;

	template<SignedIntegral T>
	explicit Point2(T, T) -> Point2<T>;

} // namespace math
