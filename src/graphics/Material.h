#pragma once

#include "../../base/StandardIncludes.h"
#include "../Color.h"
#include "../Ray.h"

namespace graphics {
	template<FloatingPoint T = float>
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

		virtual constexpr auto scatter(const Ray&,
									   const HitRecord& record,
									   not_null<Color*> attenuation,
									   not_null<Ray*> scattered) const noexcept -> bool
			= 0;
		constexpr auto operator=(const Material& material) noexcept -> Material& = default;
		constexpr auto operator=(Material&& material) noexcept -> Material& = default;
	};
} // namespace graphics
