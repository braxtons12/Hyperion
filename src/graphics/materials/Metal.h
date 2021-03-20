#pragma once

#include "../../base/StandardIncludes.h"
#include "Material.h"

namespace graphics {

	IGNORE_PADDING_START
	template<FloatingPoint T = float>
	class Metal final : public Material<T> {
	  public:
		using Color = Color<T>;
		using Ray = Ray<T>;
		using HitRecord = HitRecord<T>;

		constexpr Metal() noexcept = default;
		explicit constexpr Metal(const Color& albedo) noexcept : m_albedo(albedo) {
		}
		explicit constexpr Metal(Color&& albedo) noexcept : m_albedo(albedo) {
		}
		constexpr Metal(const Metal& metal) noexcept = default;
		constexpr Metal(Metal&& metal) noexcept = default;
		constexpr ~Metal() noexcept final = default;

		inline constexpr auto scatter(const Ray& ray,
									  const HitRecord& record,
									  NotNull<Color> attenuation,
									  NotNull<Ray> scattered) const noexcept -> bool final {
			auto reflected = ray.direction().normalized().reflected(record.m_normal);

			*scattered = {record.m_point, reflected};
			*attenuation = m_albedo;
			return (scattered->direction().dot_prod(record.m_normal) > 0);
		}

		constexpr auto operator=(const Metal& metal) noexcept -> Metal& = default;
		constexpr auto operator=(Metal&& metal) noexcept -> Metal& = default;

	  private:
		Color m_albedo = Color();
	};
	IGNORE_PADDING_STOP

	// Deduction Guides

	template<FloatingPoint T = float>
	Metal(const Color<T>&) -> Metal<T>;

	template<FloatingPoint T = float>
	Metal(Color<T>&&) -> Metal<T>;
} // namespace graphics
