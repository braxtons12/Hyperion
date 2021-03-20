#pragma once

#include "../base/StandardIncludes.h"

namespace graphics {
	template<FloatingPoint T = float>
	class Ray {
	  public:
		using Vec3 = Vec3<T>;
		using Point3 = Point3<T>;

		constexpr Ray() noexcept = default;
		explicit constexpr Ray(const Point3& origin) noexcept : m_origin(origin) {
		}
		explicit constexpr Ray(Point3&& origin) noexcept : m_origin(std::move(origin)) {
		}
		explicit constexpr Ray(const Vec3& direction) noexcept : m_direction(direction) {
		}
		explicit constexpr Ray(Vec3&& direction) noexcept : m_direction(std::move(direction)) {
		}
		constexpr Ray(const Point3& origin, const Vec3& direction) noexcept
			: m_origin(origin), m_direction(direction) {
		}
		constexpr Ray(Point3&& origin, const Vec3& direction) noexcept
			: m_origin(std::move(origin)), m_direction(direction) {
		}
		constexpr Ray(const Point3& origin, Vec3&& direction) noexcept
			: m_origin(origin), m_direction(std::move(direction)) {
		}
		constexpr Ray(Point3&& origin, Vec3&& direction) noexcept
			: m_origin(std::move(origin)), m_direction(std::move(direction)) {
		}
		constexpr Ray(const Ray& ray) noexcept = default;
		constexpr Ray(Ray&& ray) noexcept = default;
		constexpr ~Ray() noexcept = default;

		inline constexpr auto origin() const noexcept -> const Point3& {
			return m_origin;
		}
		inline constexpr auto origin() noexcept -> Point3& {
			return m_origin;
		}

		inline constexpr auto direction() const noexcept -> const Vec3& {
			return m_direction;
		}
		inline constexpr auto direction() noexcept -> Vec3& {
			return m_direction;
		}

		inline constexpr auto point_at(T length) const noexcept -> Point3 {
			return m_origin + m_direction * length;
		}

		constexpr auto operator=(const Ray& ray) noexcept -> Ray& = default;
		constexpr auto operator=(Ray&& ray) noexcept -> Ray& = default;

	  private:
		Point3 m_origin = Point3(0, 0, 0);
		Vec3 m_direction = Vec3(1, 0, 0);
	};

	// Deduction Guides

	template<FloatingPoint T = float>
	explicit Ray(const Point3<T>&) -> Ray<T>;

	template<FloatingPoint T = float>
	explicit Ray(Point3<T>&&) -> Ray<T>;

	template<FloatingPoint T = float>
	explicit Ray(const Vec3<T>&) -> Ray<T>;

	template<FloatingPoint T = float>
	explicit Ray(Vec3<T>&&) -> Ray<T>;

	template<FloatingPoint T = float>
	explicit Ray(const Point3<T>&, const Vec3<T>&) -> Ray<T>;

	template<FloatingPoint T = float>
	explicit Ray(Point3<T>&&, const Vec3<T>&) -> Ray<T>;

	template<FloatingPoint T = float>
	explicit Ray(const Point3<T>&, Vec3<T>&&) -> Ray<T>;

	template<FloatingPoint T = float>
	explicit Ray(Point3<T>&&, Vec3<T>&&) -> Ray<T>;
} // namespace graphics
