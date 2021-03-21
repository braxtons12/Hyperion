#pragma once

#include "../../base/StandardIncludes.h"
#include "Material.h"

namespace graphics {

	// HOW DO WE NEED 4 BYTES OF PADDING FOR ONE FLOAT???????
	IGNORE_PADDING_START
	template<FloatingPoint T = float>
	class Dielectric final : public Material<T> {
	  public:
		using Ray = Ray<T>;
		using HitRecord = HitRecord<T>;
		using Color = Color<T>;

		constexpr Dielectric() noexcept = default;
		explicit constexpr Dielectric(T refraction_index) noexcept
			: m_refraction_index(refraction_index) {
		}
		constexpr Dielectric(const Dielectric& dielectric) noexcept = default;
		constexpr Dielectric(Dielectric&& dielectric) noexcept = default;
		constexpr ~Dielectric() noexcept final = default;

		inline constexpr auto scatter(const Ray& ray,
									  const HitRecord& record,
									  NotNull<Color> attenuation,
									  NotNull<Ray> scattered) const noexcept -> bool final {
			*attenuation = Color(narrow_cast<T>(1), narrow_cast<T>(1), narrow_cast<T>(1));
			auto refraction_ratio = record.m_hit_outer_face ?
										  (narrow_cast<T>(1) / m_refraction_index) :
										  m_refraction_index;

			auto direction_normalized = ray.direction().normalized();

			auto cos_theta = General::min((-direction_normalized).dot_prod(record.m_normal),
										  narrow_cast<T>(1));
			auto sin_theta = General::sqrt(narrow_cast<T>(1) - cos_theta * cos_theta);

			// if can't refract OR randomized change to reflect
			if(refraction_ratio * sin_theta > narrow_cast<T>(1)
			   || reflectance(cos_theta, refraction_ratio) > random_value<T>())
			{
				*scattered = {record.m_point, direction_normalized.reflected(record.m_normal)};
			}
			else {
				*scattered = {record.m_point,
							  direction_normalized.refracted(record.m_normal, refraction_ratio)};
			}

			return true;
		}

		constexpr auto operator=(const Dielectric& dielectric) noexcept -> Dielectric& = default;
		constexpr auto operator=(Dielectric&& dielectric) noexcept -> Dielectric& = default;

	  private:
		T m_refraction_index = narrow_cast<T>(1);

		static inline constexpr auto reflectance(T cosine, T refraction_index) noexcept -> T {
			auto r0
				= (narrow_cast<T>(1) - refraction_index) / (narrow_cast<T>(1) + refraction_index);
			r0 = r0 * r0;
			return r0
				   + (narrow_cast<T>(1) - r0)
						 * Exponentials::pow(narrow_cast<T>(1) - cosine, narrow_cast<T>(5));
		}
	};
	IGNORE_PADDING_STOP
} // namespace graphics
