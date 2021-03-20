#pragma once

#include "../base/StandardIncludes.h"
#include "../math/Point3.h"
#include "../math/Vec3.h"
#include "Ray.h"

namespace graphics {
	template<FloatingPoint T = float>
	class Camera {
	  public:
		using Point3 = math::Point3<T>;
		using Vec3 = math::Vec3<T>;
		constexpr Camera() noexcept = default;
		explicit constexpr Camera(T aspect_ratio) noexcept
			: m_aspect_ratio(aspect_ratio), m_viewport_width(m_aspect_ratio * m_viewport_height),
			  m_horizontal_axes(m_viewport_width, narrow_cast<T>(0), narrow_cast<T>(0)),
			  m_lower_left(calculate_lower_left()) {
		}
		constexpr Camera(T aspect_ratio, T viewport_height) noexcept
			: m_aspect_ratio(aspect_ratio), m_viewport_height(viewport_height),
			  m_viewport_width(m_aspect_ratio * m_viewport_height),
			  m_horizontal_axes(m_viewport_width, narrow_cast<T>(0), narrow_cast<T>(0)),
			  m_vertical_axes(narrow_cast<T>(0), m_viewport_height, narrow_cast<T>(0)),
			  m_lower_left(calculate_lower_left()) {
		}
		constexpr Camera(T aspect_ratio, T viewport_height, T focal_length) noexcept
			: m_aspect_ratio(aspect_ratio), m_viewport_height(viewport_height),
			  m_viewport_width(m_aspect_ratio * m_viewport_height), m_focal_length(focal_length),
			  m_horizontal_axes(m_viewport_width, narrow_cast<T>(0), narrow_cast<T>(0)),
			  m_vertical_axes(narrow_cast<T>(0), m_viewport_height, narrow_cast<T>(0)),
			  m_lower_left(calculate_lower_left()) {
		}
		constexpr Camera(T aspect_ratio, T viewport_height, T focal_length, Point3 origin) noexcept
			: m_aspect_ratio(aspect_ratio), m_viewport_height(viewport_height),
			  m_viewport_width(m_aspect_ratio * m_viewport_height), m_focal_length(focal_length),
			  m_horizontal_axes(m_viewport_width, narrow_cast<T>(0), narrow_cast<T>(0)),
			  m_vertical_axes(narrow_cast<T>(0), m_viewport_height, narrow_cast<T>(0)),
			  m_origin(origin), m_lower_left(calculate_lower_left()) {
		}
		constexpr Camera(const Camera& camera) noexcept = default;
		constexpr Camera(Camera&& camera) noexcept = default;
		constexpr ~Camera() noexcept = default;

		constexpr inline auto get_ray(T u, T v) const noexcept -> Ray<T> {
			return {
				m_origin,
				(m_lower_left + u * m_horizontal_axes + v * m_vertical_axes - m_origin).as_vec()};
		}

		constexpr auto operator=(const Camera& camera) noexcept -> Camera& = default;
		constexpr auto operator=(Camera&& camera) noexcept -> Camera& = default;

	  private:
		T m_aspect_ratio = narrow_cast<T>(16.0 / 9.0);
		T m_viewport_height = narrow_cast<T>(2.0);
		T m_viewport_width = m_aspect_ratio * m_viewport_height;
		T m_focal_length = narrow_cast<T>(1.0);
		Vec3 m_horizontal_axes = {m_viewport_width, narrow_cast<T>(0), narrow_cast<T>(0)};
		Vec3 m_vertical_axes = {narrow_cast<T>(0), m_viewport_height, narrow_cast<T>(0)};
		Point3 m_origin = {narrow_cast<T>(0), narrow_cast<T>(0), narrow_cast<T>(0)};
		Point3 m_lower_left = calculate_lower_left();

		constexpr inline auto calculate_lower_left() noexcept -> Point3 {
			return m_origin - m_horizontal_axes / narrow_cast<T>(2.0)
				   - m_vertical_axes / narrow_cast<T>(2.0)
				   - Vec3(narrow_cast<T>(0), narrow_cast<T>(0), m_focal_length);
		}
	};
} // namespace graphics
