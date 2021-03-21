#pragma once

#include "../../base/StandardIncludes.h"
#include "Material.h"

namespace graphics {

	template<FloatingPoint T = float>
	class Metal final : public Material<T> {
	  public:
		using Color = Color<T>;
		using Ray = Ray<T>;
		using HitRecord = HitRecord<T>;

		constexpr Metal() noexcept = default;
		explicit constexpr Metal(T reflection_fuzziness) noexcept
			: m_reflection_fuzz(reflection_fuzziness) {
		}
		explicit constexpr Metal(const Color& albedo) noexcept : m_albedo(albedo) {
		}
		explicit constexpr Metal(Color&& albedo) noexcept : m_albedo(albedo) {
		}
		constexpr Metal(const Color& albedo, T reflection_fuzziness) noexcept
			: m_albedo(albedo), m_reflection_fuzz(reflection_fuzziness) {
		}
		constexpr Metal(Color&& albedo, T reflection_fuzziness) noexcept
			: m_albedo(albedo), m_reflection_fuzz(reflection_fuzziness) {
		}
		constexpr Metal(const Metal& metal) noexcept = default;
		constexpr Metal(Metal&& metal) noexcept = default;
		constexpr ~Metal() noexcept final = default;

		inline constexpr auto scatter(const Ray& ray,
									  const HitRecord& record,
									  NotNull<Color> attenuation,
									  NotNull<Ray> scattered) const noexcept -> bool final {
			auto reflected = ray.direction().normalized().reflected(record.m_normal);

			*scattered = {record.m_point,
						  reflected + m_reflection_fuzz * Vec3<T>::random_in_unit_sphere()};
			*attenuation = m_albedo;
			return (scattered->direction().dot_prod(record.m_normal) > 0);
		}

		constexpr auto operator=(const Metal& metal) noexcept -> Metal& = default;
		constexpr auto operator=(Metal&& metal) noexcept -> Metal& = default;

	  private:
		Color m_albedo = Color();
		T m_reflection_fuzz = narrow_cast<T>(0);
	};

	// Deduction Guides

	template<FloatingPoint T = float>
	Metal(T) -> Metal<T>;

	template<FloatingPoint T = float>
	Metal(const Color<T>&) -> Metal<T>;

	template<FloatingPoint T = float>
	Metal(Color<T>&&) -> Metal<T>;

	template<FloatingPoint T = float>
	Metal(const Color<T>&, T) -> Metal<T>;

	template<FloatingPoint T = float>
	Metal(Color<T>&&, T) -> Metal<T>;
} // namespace graphics
