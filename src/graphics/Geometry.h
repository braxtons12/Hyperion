#pragma once

#include <atomic>
#include <memory>

#include "../base/StandardIncludes.h"
#include "Ray.h"
#include "materials/Material.h"

namespace graphics {

	IGNORE_UNUSED_TEMPLATES_START
	template<FloatingPoint T = float>
	static std::atomic_bool DEFAULT_INITIALIZED;
	template<FloatingPoint T = float>
	[[clang::no_destroy]] static DefaultMaterial<T> DEFAULT_MATERIAL;

	template<FloatingPoint T = float>
	[[nodiscard]] inline static constexpr auto
	initalize_default() noexcept -> NotNull<DefaultMaterial<T>> {
		bool expected = false;
		if(DEFAULT_INITIALIZED<T>.compare_exchange_strong(expected,
														  true,
														  std::memory_order_seq_cst)) {
			DEFAULT_MATERIAL<T> = DefaultMaterial<T>();
		}
		return &DEFAULT_MATERIAL<T>;
	}
	IGNORE_UNUSED_TEMPLATES_STOP

	IGNORE_PADDING_START
	template<FloatingPoint T = float>
	struct HitRecord {
		using Point3 = Point3<T>;
		using Vec3 = Vec3<T>;
		using Ray = Ray<T>;
		using Material = Material<T>;
		using DefaultMaterial = DefaultMaterial<T>;

		Point3 m_point = Point3();
		Vec3 m_normal = Vec3();
		NotNull<Material> m_material = initalize_default<T>();
		T m_length = static_cast<T>(0);
		bool m_hit_outer_face = true;

		constexpr HitRecord() noexcept = default;
		explicit constexpr HitRecord(const Point3& point) noexcept : m_point(point) {
		}
		explicit constexpr HitRecord(Point3&& point) noexcept : m_point(std::move(point)) {
		}
		explicit constexpr HitRecord(const Vec3& normal) noexcept : m_normal(normal) {
		}
		explicit constexpr HitRecord(Vec3&& normal) noexcept : m_normal(std::move(normal)) {
		}
		constexpr HitRecord(const Point3& point, const Vec3& normal) noexcept
			: m_point(point), m_normal(normal) {
		}
		constexpr HitRecord(Point3&& point, const Vec3& normal) noexcept
			: m_point(std::move(point)), m_normal(normal) {
		}
		constexpr HitRecord(const Point3& point, Vec3&& normal) noexcept
			: m_point(point), m_normal(std::move(normal)) {
		}
		constexpr HitRecord(Point3&& point, Vec3&& normal) noexcept
			: m_point(std::move(point)), m_normal(std::move(normal)) {
		}
		constexpr HitRecord(const Point3& point, const Vec3& normal, T length) noexcept
			: m_point(point), m_normal(normal), m_length(length) {
		}
		constexpr HitRecord(Point3&& point, const Vec3& normal, T length) noexcept
			: m_point(std::move(point)), m_normal(normal), m_length(length) {
		}
		constexpr HitRecord(const Point3& point, Vec3&& normal, T length) noexcept
			: m_point(point), m_normal(std::move(normal)), m_length(length) {
		}
		constexpr HitRecord(Point3&& point, Vec3&& normal, T length) noexcept
			: m_point(std::move(point)), m_normal(std::move(normal)), m_length(length) {
		}
		constexpr HitRecord(const HitRecord& record) noexcept = default;
		constexpr HitRecord(HitRecord&& record) noexcept = default;

		constexpr inline auto set_normal(const Ray& ray, const Vec3& normal) noexcept -> void {
			m_hit_outer_face = ray.direction().dot_prod(normal) < 0;
			m_normal = m_hit_outer_face ? normal : -normal;
		}

		constexpr auto operator=(const HitRecord& record) noexcept -> HitRecord& = default;
		constexpr auto operator=(HitRecord&& record) noexcept -> HitRecord& = default;
	};
	IGNORE_PADDING_STOP

	template<FloatingPoint T = float>
	class Geometry {
	  public:
		using Ray = Ray<T>;
		using HitRecord = HitRecord<T>;

		constexpr Geometry() noexcept = default;
		constexpr Geometry(const Geometry& entity) noexcept = default;
		constexpr Geometry(Geometry&& entity) noexcept = default;
		virtual constexpr ~Geometry() noexcept = default;

		virtual constexpr auto intersected(const Ray& ray,
										   T min_length,
										   T max_length,
										   NotNull<HitRecord> record) const noexcept -> bool
			= 0;

		constexpr auto operator=(const Geometry& entity) noexcept -> Geometry& = default;
		constexpr auto operator=(Geometry&& entity) noexcept -> Geometry& = default;
	};
} // namespace graphics
