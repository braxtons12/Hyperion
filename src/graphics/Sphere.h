#pragma once

#include <unordered_set>

#include "../base/StandardIncludes.h"
#include "Geometry.h"
#include "Ray.h"

namespace graphics {

	IGNORE_PADDING_START
	template<FloatingPoint T = float>
	class Sphere : public Geometry<T> {
	  public:
		using Point3 = Point3<T>;
		using Ray = Ray<T>;
		using HitRecord = HitRecord<T>;
		using Material = Material<T>;

		constexpr Sphere() noexcept = default;
		explicit constexpr Sphere(const Point3& center) noexcept : m_center(center) {
		}
		explicit constexpr Sphere(Point3&& center) noexcept : m_center(std::move(center)) {
		}
		explicit constexpr Sphere(T radius) noexcept : m_radius(radius) {
		}
		template<typename MaterialType>
		requires Derived<MaterialType, Material>
		constexpr Sphere(T radius, std::unique_ptr<MaterialType>&& material) noexcept
			: m_material(std::move(material)), m_radius(radius) {
		}
		template<typename MaterialType>
		requires Derived<MaterialType, Material>
		constexpr Sphere(const Point3& center, std::unique_ptr<MaterialType>&& material) noexcept
			: m_center(center), m_material(std::move(material)) {
		}
		template<typename MaterialType>
		requires Derived<MaterialType, Material>
		constexpr Sphere(Point3&& center, std::unique_ptr<MaterialType>&& material) noexcept
			: m_center(std::move(center)), m_material(std::move(material)) {
		}
		explicit constexpr Sphere(const Point3& center, T radius) noexcept
			: m_center(center), m_radius(radius) {
		}
		explicit constexpr Sphere(Point3&& center, T radius) noexcept
			: m_center(std::move(center)), m_radius(radius) {
		}
		template<typename MaterialType>
		requires Derived<MaterialType, Material>
		constexpr Sphere(const Point3& center,
						 T radius,
						 std::unique_ptr<MaterialType>&& material) noexcept
			: m_center(center), m_material(std::move(material)), m_radius(radius) {
		}
		template<typename MaterialType>
		requires Derived<MaterialType, Material>
		constexpr Sphere(Point3&& center,
						 T radius,
						 std::unique_ptr<MaterialType>&& material) noexcept
			: m_center(std::move(center)), m_material(std::move(material)), m_radius(radius) {
		}
		constexpr Sphere(const Sphere& sphere) noexcept = default;
		constexpr Sphere(Sphere&& sphere) noexcept = default;

		inline constexpr auto intersected(const Ray& ray,
										  T min_length,
										  T max_length,
										  NotNull<HitRecord> record) const noexcept -> bool final {
			auto origin_minus_center = ray.origin() - m_center;
			auto oc_vec = origin_minus_center.as_vec();
			auto oc_mag = oc_vec.template magnitude<T>();
			auto sqrta = ray.direction().template magnitude<T>();
			auto a = sqrta * sqrta;
			auto half_b = oc_vec.dot_prod(ray.direction());
			auto c = (oc_mag * oc_mag) - (m_radius * m_radius);

			auto discriminant = (half_b * half_b) - (a * c);
			if(discriminant < 0) {
				return false;
			}
			auto sqrt_discrim = General::sqrt(discriminant);

			auto root = (-half_b - sqrt_discrim) / a;
			if(root < min_length + HIT_THRESHOLD || root > max_length - HIT_THRESHOLD) {
				root = (-half_b + sqrt_discrim) / a;
				if(root < min_length + HIT_THRESHOLD || root > max_length - HIT_THRESHOLD) {
					return false;
				}
			}

			record->m_length = root;
			record->m_point = ray.point_at(root);
			auto normal = ((record->m_point - m_center) / m_radius).as_vec();
			record->set_normal(ray, normal);
			record->m_material = m_material.get();

			return true;
		}

		constexpr auto operator=(const Sphere& sphere) noexcept -> Sphere& = default;
		constexpr auto operator=(Sphere&& sphere) noexcept -> Sphere& = default;

	  private:
		Point3 m_center = Point3();
		std::unique_ptr<Material> m_material;
		T m_radius = static_cast<T>(1);

		static const constexpr T HIT_THRESHOLD = narrow_cast<T>(0.002);
	};
	IGNORE_PADDING_STOP

	// Deduction Guides

	template<FloatingPoint T = float>
	Sphere(T) -> Sphere<T>;

	template<FloatingPoint T = float>
	Sphere(T, std::unique_ptr<Material<T>>&&) -> Sphere<T>;

	template<FloatingPoint T = float>
	Sphere(const Point3<T>&) -> Sphere<T>;

	template<FloatingPoint T = float>
	Sphere(Point3<T>&&) -> Sphere<T>;

	template<FloatingPoint T = float>
	Sphere(const Point3<T>&, T) -> Sphere<T>;

	template<FloatingPoint T = float>
	Sphere(Point3<T>&&, T) -> Sphere<T>;

	template<FloatingPoint T = float>
	Sphere(const Point3<T>&, std::unique_ptr<Material<T>>&&) -> Sphere<T>;

	template<FloatingPoint T = float>
	Sphere(Point3<T>&&, std::unique_ptr<Material<T>>&&) -> Sphere<T>;
} // namespace graphics
