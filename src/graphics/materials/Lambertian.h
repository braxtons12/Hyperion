#pragma once

#include "../../base/StandardIncludes.h"
#include "Material.h"

namespace graphics {

	IGNORE_PADDING_START
	template<FloatingPoint T = float>
	class Lambertian final : public Material<T> {
	  public:
		using Ray = Ray<T>;
		using HitRecord = HitRecord<T>;
		using Color = Color<T>;
		using Vec3 = Vec3<T>;

		constexpr Lambertian() noexcept = default;
		explicit constexpr Lambertian(const Color& albedo) noexcept : m_albedo(albedo) {
		}
		explicit constexpr Lambertian(Color&& albedo) noexcept : m_albedo(std::move(albedo)) {
		}
		constexpr Lambertian(const Lambertian& lambertian) noexcept = default;
		constexpr Lambertian(Lambertian&& lambertian) noexcept = default;
		constexpr ~Lambertian() noexcept final = default;

		inline constexpr auto scatter(const Ray& ray,
									  const HitRecord& record,
									  NotNull<Color> attenuation,
									  NotNull<Ray> scattered) const noexcept -> bool final {
			ignore(ray);
			auto scatter_direction = record.m_normal + Vec3::random_in_unit_sphere().normalized();
			if(scatter_direction.is_approx_zero()) {
				scatter_direction = record.m_normal;
			}
			*scattered = {record.m_point, scatter_direction};
			*attenuation = m_albedo;
			return true;
		}

		constexpr auto operator=(const Lambertian& lambertian) noexcept -> Lambertian& = default;
		constexpr auto operator=(Lambertian&& lambertian) noexcept -> Lambertian& = default;

	  private:
		Color m_albedo = Color();
	};
	IGNORE_PADDING_STOP

	// Deduction Guides

	template<FloatingPoint T = float>
	explicit Lambertian(const Color<T>&) -> Lambertian<T>;

	template<FloatingPoint T = float>
	explicit Lambertian(Color<T>&&) -> Lambertian<T>;
} // namespace graphics
