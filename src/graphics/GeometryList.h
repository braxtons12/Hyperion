#pragma once

#include <memory>
#include <vector>

#include "../base/StandardIncludes.h"
#include "../utils/Concepts.h"
#include "Geometry.h"

namespace graphics {

	template<FloatingPoint T = float>
	class GeometryList final : public Geometry<T> {
		using Geometry = Geometry<T>;
		using Ray = Ray<T>;
		using HitRecord = HitRecord<T>;

	  public:
		constexpr GeometryList() noexcept = default;
		explicit constexpr GeometryList(std::unique_ptr<Geometry>&& geometry) noexcept {
			m_geometries.push_back(std::move(geometry));
		}
		constexpr GeometryList(const GeometryList& list) noexcept = default;
		constexpr GeometryList(GeometryList&& list) noexcept = default;
		constexpr ~GeometryList() noexcept final = default;

		inline constexpr auto clear() noexcept -> void {
			m_geometries.clear();
		}

		template<typename GeometryType>
		requires Derived<GeometryType, Geometry>
		inline constexpr auto add(std::unique_ptr<GeometryType>&& geometry) noexcept -> void {
			m_geometries.push_back(std::move(geometry));
		}
		template<typename GeometryType, typename... Args>
		requires utils::concepts::Derived<GeometryType, Geometry> && utils::concepts::
			ConstructibleFrom<GeometryType, Args...>
		inline constexpr auto add(Args&&... args) noexcept -> void {
			m_geometries.push_back(std::make_unique<GeometryType>(args...));
		}

		inline constexpr auto intersected(const Ray& ray,
										  T min_length,
										  T max_length,
										  NotNull<HitRecord> record) const noexcept -> bool final {
			HitRecord temp_record = {};
			auto hit_found = false;
			auto closest = max_length;

			for(const auto& geometry : m_geometries) {
				if(geometry->intersected(ray, min_length, closest, &temp_record)) {
					hit_found = true;
					closest = temp_record.m_length;
					*record = temp_record;
				}
			}

			return hit_found;
		}

		constexpr auto operator=(const GeometryList& list) noexcept -> GeometryList& = default;
		constexpr auto operator=(GeometryList&& list) noexcept -> GeometryList& = default;

	  private:
		std::vector<std::unique_ptr<Geometry>> m_geometries;
	};
} // namespace graphics
