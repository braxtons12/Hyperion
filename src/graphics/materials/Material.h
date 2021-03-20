#pragma once

#include "../../base/StandardIncludes.h"
#include "../Color.h"
#include "../Ray.h"

namespace graphics {
	template<FloatingPoint T>
	struct HitRecord;

	template<FloatingPoint T = float>
	class Material {
	  public:
		using Ray = Ray<T>;
		using HitRecord = HitRecord<T>;
		using Color = Color<T>;

		constexpr Material() noexcept = default;
		constexpr Material(const Material& material) noexcept = default;
		constexpr Material(Material&& material) noexcept = default;
		virtual constexpr ~Material() noexcept = default;

		virtual constexpr auto scatter(const Ray&,
									   const HitRecord& record,
									   NotNull<Color> attenuation,
									   NotNull<Ray> scattered) const noexcept -> bool
			= 0;
		constexpr auto operator=(const Material& material) noexcept -> Material& = default;
		constexpr auto operator=(Material&& material) noexcept -> Material& = default;
	};

	template<FloatingPoint T = float>
	class DefaultMaterial final : public Material<T> {
	  public:
		using Ray = Ray<T>;
		using HitRecord = HitRecord<T>;
		using Color = Color<T>;

		constexpr DefaultMaterial() noexcept = default;
		constexpr DefaultMaterial(const DefaultMaterial& material) noexcept = default;
		constexpr DefaultMaterial(DefaultMaterial&& material) noexcept = default;
		constexpr ~DefaultMaterial() noexcept final = default;

		inline constexpr auto scatter(const Ray& ray,
									  const HitRecord& record,
									  NotNull<Color> attenuation,
									  NotNull<Ray> scattered) const noexcept -> bool final {
			ignore(ray, record, attenuation, scattered);
			return false;
		}

		constexpr auto
		operator=(const DefaultMaterial& material) noexcept -> DefaultMaterial& = default;
		constexpr auto operator=(DefaultMaterial&& material) noexcept -> DefaultMaterial& = default;
	};
} // namespace graphics
