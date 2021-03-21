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
			  m_horizontal_axes(calculate_horizontal_axes()),
			  m_vertical_axes(calculate_vertical_axes()), m_lower_left(calculate_lower_left()) {
		}
		constexpr Camera(T aspect_ratio, T viewport_height) noexcept
			: m_aspect_ratio(aspect_ratio),
			  m_viewport_height(calculate_viewport_height(viewport_height)),
			  m_viewport_width(m_aspect_ratio * m_viewport_height),
			  m_horizontal_axes(calculate_horizontal_axes()),
			  m_vertical_axes(calculate_vertical_axes()), m_lower_left(calculate_lower_left()) {
		}
		constexpr Camera(T aspect_ratio, T vertical_fov, T viewport_height) noexcept
			: m_aspect_ratio(aspect_ratio), m_vertical_fov(vertical_fov),
			  m_viewport_height(calculate_viewport_height(viewport_height)),
			  m_viewport_width(m_aspect_ratio * m_viewport_height),
			  m_horizontal_axes(calculate_horizontal_axes()),
			  m_vertical_axes(calculate_vertical_axes()), m_lower_left(calculate_lower_left()) {
		}
		constexpr Camera(T aspect_ratio,
						 T vertical_fov,
						 T viewport_height,
						 T focal_length,
						 T aperture) noexcept
			: m_aspect_ratio(aspect_ratio),
			  m_viewport_height(calculate_viewport_height(viewport_height)),
			  m_viewport_width(m_aspect_ratio * m_viewport_height), m_focal_length(focal_length),
			  m_lens_radius(aperture / narrow_cast<T>(2)), m_vertical_fov(vertical_fov),
			  m_horizontal_axes(calculate_horizontal_axes()),
			  m_vertical_axes(calculate_vertical_axes()), m_lower_left(calculate_lower_left()) {
		}
		explicit constexpr Camera(const Point3& origin) noexcept
			: m_origin(origin), m_w(calculate_w()), m_u(calculate_u()), m_v(calculate_v()),
			  m_horizontal_axes(calculate_horizontal_axes()),
			  m_vertical_axes(calculate_vertical_axes()), m_lower_left(calculate_lower_left()) {
		}
		constexpr Camera(T aspect_ratio, const Point3& origin) noexcept
			: m_aspect_ratio(aspect_ratio), m_viewport_width(m_aspect_ratio * m_viewport_height),
			  m_origin(origin), m_w(calculate_w()), m_u(calculate_u()), m_v(calculate_v()),
			  m_horizontal_axes(calculate_horizontal_axes()),
			  m_vertical_axes(calculate_vertical_axes()), m_lower_left(calculate_lower_left()) {
		}
		constexpr Camera(T aspect_ratio, T viewport_height, const Point3& origin) noexcept
			: m_aspect_ratio(aspect_ratio),
			  m_viewport_height(calculate_viewport_height(viewport_height)),
			  m_viewport_width(m_aspect_ratio * m_viewport_height), m_origin(origin),
			  m_w(calculate_w()), m_u(calculate_u()), m_v(calculate_v()),
			  m_horizontal_axes(calculate_horizontal_axes()),
			  m_vertical_axes(calculate_vertical_axes()), m_lower_left(calculate_lower_left()) {
		}
		constexpr Camera(T aspect_ratio,
						 T vertical_fov,
						 T viewport_height,
						 const Point3& origin) noexcept
			: m_aspect_ratio(aspect_ratio), m_vertical_fov(vertical_fov),
			  m_viewport_height(calculate_viewport_height(viewport_height)),
			  m_viewport_width(m_aspect_ratio * m_viewport_height), m_origin(origin),
			  m_w(calculate_w()), m_u(calculate_u()), m_v(calculate_v()),
			  m_horizontal_axes(calculate_horizontal_axes()),
			  m_vertical_axes(calculate_vertical_axes()), m_lower_left(calculate_lower_left()) {
		}
		constexpr Camera(T aspect_ratio,
						 T vertical_fov,
						 T viewport_height,
						 T focal_length,
						 const Point3& origin) noexcept
			: m_aspect_ratio(aspect_ratio),
			  m_viewport_height(calculate_viewport_height(viewport_height)),
			  m_viewport_width(m_aspect_ratio * m_viewport_height), m_focal_length(focal_length),
			  m_vertical_fov(vertical_fov), m_origin(origin), m_w(calculate_w()),
			  m_u(calculate_u()), m_v(calculate_v()),
			  m_horizontal_axes(calculate_horizontal_axes()),
			  m_vertical_axes(calculate_vertical_axes()), m_lower_left(calculate_lower_left()) {
		}
		constexpr Camera(T aspect_ratio,
						 T vertical_fov,
						 T viewport_height,
						 T focal_length,
						 T aperture,
						 const Point3& origin) noexcept
			: m_aspect_ratio(aspect_ratio),
			  m_viewport_height(calculate_viewport_height(viewport_height)),
			  m_viewport_width(m_aspect_ratio * m_viewport_height), m_focal_length(focal_length),
			  m_lens_radius(aperture / narrow_cast<T>(2)), m_vertical_fov(vertical_fov),
			  m_origin(origin), m_w(calculate_w()), m_u(calculate_u()), m_v(calculate_v()),
			  m_horizontal_axes(calculate_horizontal_axes()),
			  m_vertical_axes(calculate_vertical_axes()), m_lower_left(calculate_lower_left()) {
		}
		constexpr Camera(const Point3& origin, const Point3& focal_point) noexcept
			: m_origin(origin), m_focal_point(focal_point), m_w(calculate_w()), m_u(calculate_u()),
			  m_v(calculate_v()), m_horizontal_axes(calculate_horizontal_axes()),
			  m_vertical_axes(calculate_vertical_axes()), m_lower_left(calculate_lower_left()) {
		}
		constexpr Camera(T aspect_ratio, const Point3& origin, const Point3& focal_point) noexcept
			: m_aspect_ratio(aspect_ratio), m_viewport_width(m_aspect_ratio * m_viewport_height),
			  m_origin(origin), m_focal_point(focal_point), m_w(calculate_w()), m_u(calculate_u()),
			  m_v(calculate_v()), m_horizontal_axes(calculate_horizontal_axes()),
			  m_vertical_axes(calculate_vertical_axes()), m_lower_left(calculate_lower_left()) {
		}
		constexpr Camera(T aspect_ratio,
						 T viewport_height,
						 const Point3& origin,
						 const Point3& focal_point) noexcept
			: m_aspect_ratio(aspect_ratio),
			  m_viewport_height(calculate_viewport_height(viewport_height)),
			  m_viewport_width(m_aspect_ratio * m_viewport_height), m_origin(origin),
			  m_focal_point(focal_point), m_w(calculate_w()), m_u(calculate_u()),
			  m_v(calculate_v()), m_horizontal_axes(calculate_horizontal_axes()),
			  m_vertical_axes(calculate_vertical_axes()), m_lower_left(calculate_lower_left()) {
		}
		constexpr Camera(T aspect_ratio,
						 T vertical_fov,
						 T viewport_height,
						 const Point3& origin,
						 const Point3& focal_point) noexcept
			: m_aspect_ratio(aspect_ratio), m_vertical_fov(vertical_fov),
			  m_viewport_height(calculate_viewport_height(viewport_height)),
			  m_viewport_width(m_aspect_ratio * m_viewport_height), m_origin(origin),
			  m_focal_point(focal_point), m_w(calculate_w()), m_u(calculate_u()),
			  m_v(calculate_v()), m_horizontal_axes(calculate_horizontal_axes()),
			  m_vertical_axes(calculate_vertical_axes()), m_lower_left(calculate_lower_left()) {
		}
		constexpr Camera(T aspect_ratio,
						 T vertical_fov,
						 T viewport_height,
						 T focal_length,
						 const Point3& origin,
						 const Point3& focal_point) noexcept
			: m_aspect_ratio(aspect_ratio),
			  m_viewport_height(calculate_viewport_height(viewport_height)),
			  m_viewport_width(m_aspect_ratio * m_viewport_height), m_focal_length(focal_length),
			  m_vertical_fov(vertical_fov), m_origin(origin), m_focal_point(focal_point),
			  m_w(calculate_w()), m_u(calculate_u()), m_v(calculate_v()),
			  m_horizontal_axes(calculate_horizontal_axes()),
			  m_vertical_axes(calculate_vertical_axes()), m_lower_left(calculate_lower_left()) {
		}
		constexpr Camera(T aspect_ratio,
						 T vertical_fov,
						 T viewport_height,
						 T focal_length,
						 T aperture,
						 const Point3& origin,
						 const Point3& focal_point) noexcept
			: m_aspect_ratio(aspect_ratio),
			  m_viewport_height(calculate_viewport_height(viewport_height)),
			  m_viewport_width(m_aspect_ratio * m_viewport_height), m_focal_length(focal_length),
			  m_lens_radius(aperture / narrow_cast<T>(2)), m_vertical_fov(vertical_fov),
			  m_origin(origin), m_focal_point(focal_point), m_w(calculate_w()), m_u(calculate_u()),
			  m_v(calculate_v()), m_horizontal_axes(calculate_horizontal_axes()),
			  m_vertical_axes(calculate_vertical_axes()), m_lower_left(calculate_lower_left()) {
		}
		constexpr Camera(const Point3& origin,
						 const Point3& focal_point,
						 const Vec3& view_up) noexcept
			: m_origin(origin), m_focal_point(focal_point), m_view_up(view_up), m_w(calculate_w()),
			  m_u(calculate_u()), m_v(calculate_v()),
			  m_horizontal_axes(calculate_horizontal_axes()),
			  m_vertical_axes(calculate_vertical_axes()), m_lower_left(calculate_lower_left()) {
		}
		constexpr Camera(T aspect_ratio,
						 const Point3& origin,
						 const Point3& focal_point,
						 const Vec3& view_up) noexcept
			: m_aspect_ratio(aspect_ratio), m_viewport_width(m_aspect_ratio * m_viewport_height),
			  m_origin(origin), m_focal_point(focal_point), m_view_up(view_up), m_w(calculate_w()),
			  m_u(calculate_u()), m_v(calculate_v()),
			  m_horizontal_axes(calculate_horizontal_axes()),
			  m_vertical_axes(calculate_vertical_axes()), m_lower_left(calculate_lower_left()) {
		}
		constexpr Camera(T aspect_ratio,
						 T viewport_height,
						 const Point3& origin,
						 const Point3& focal_point,
						 const Vec3& view_up) noexcept
			: m_aspect_ratio(aspect_ratio),
			  m_viewport_height(calculate_viewport_height(viewport_height)),
			  m_viewport_width(m_aspect_ratio * m_viewport_height), m_origin(origin),
			  m_focal_point(focal_point), m_view_up(view_up), m_w(calculate_w()),
			  m_u(calculate_u()), m_v(calculate_v()),
			  m_horizontal_axes(calculate_horizontal_axes()),
			  m_vertical_axes(calculate_vertical_axes()), m_lower_left(calculate_lower_left()) {
		}
		constexpr Camera(T aspect_ratio,
						 T vertical_fov,
						 T viewport_height,
						 const Point3& origin,
						 const Point3& focal_point,
						 const Vec3& view_up) noexcept
			: m_aspect_ratio(aspect_ratio), m_vertical_fov(vertical_fov),
			  m_viewport_height(calculate_viewport_height(viewport_height)),
			  m_viewport_width(m_aspect_ratio * m_viewport_height), m_origin(origin),
			  m_focal_point(focal_point), m_view_up(view_up), m_w(calculate_w()),
			  m_u(calculate_u()), m_v(calculate_v()),
			  m_horizontal_axes(calculate_horizontal_axes()),
			  m_vertical_axes(calculate_vertical_axes()), m_lower_left(calculate_lower_left()) {
		}
		constexpr Camera(T aspect_ratio,
						 T vertical_fov,
						 T viewport_height,
						 T focal_length,
						 const Point3& origin,
						 const Point3& focal_point,
						 const Vec3& view_up) noexcept
			: m_aspect_ratio(aspect_ratio), m_vertical_fov(vertical_fov),
			  m_viewport_height(calculate_viewport_height(viewport_height)),
			  m_viewport_width(m_aspect_ratio * m_viewport_height), m_focal_length(focal_length),
			  m_origin(origin), m_focal_point(focal_point), m_view_up(view_up), m_w(calculate_w()),
			  m_u(calculate_u()), m_v(calculate_v()),
			  m_horizontal_axes(calculate_horizontal_axes()),
			  m_vertical_axes(calculate_vertical_axes()), m_lower_left(calculate_lower_left()) {
		}
		constexpr Camera(T aspect_ratio,
						 T vertical_fov,
						 T viewport_height,
						 T focal_length,
						 T aperture,
						 const Point3& origin,
						 const Point3& focal_point,
						 const Vec3& view_up) noexcept
			: m_aspect_ratio(aspect_ratio), m_vertical_fov(vertical_fov),
			  m_viewport_height(calculate_viewport_height(viewport_height)),
			  m_viewport_width(m_aspect_ratio * m_viewport_height), m_focal_length(focal_length),
			  m_lens_radius(aperture / narrow_cast<T>(2)), m_origin(origin),
			  m_focal_point(focal_point), m_view_up(view_up), m_w(calculate_w()),
			  m_u(calculate_u()), m_v(calculate_v()),
			  m_horizontal_axes(calculate_horizontal_axes()),
			  m_vertical_axes(calculate_vertical_axes()), m_lower_left(calculate_lower_left()) {
		}

		constexpr Camera(const Camera& camera) noexcept = default;
		constexpr Camera(Camera&& camera) noexcept = default;
		constexpr ~Camera() noexcept = default;

		constexpr inline auto get_ray(T s, T t) const noexcept -> Ray<T> {
			auto rd = m_lens_radius * Vec3::template random_in_unit_disk<T>();
			auto offset = m_u * rd.x() + m_v * rd.y();
			return {m_origin + offset,
					(m_lower_left + s * m_horizontal_axes + t * m_vertical_axes - m_origin - offset)
						.as_vec()};
		}

		constexpr auto operator=(const Camera& camera) noexcept -> Camera& = default;
		constexpr auto operator=(Camera&& camera) noexcept -> Camera& = default;

	  private:
		static constexpr T DEFAULT_FOV = narrow_cast<T>(90.0);
		T m_aspect_ratio = narrow_cast<T>(16.0 / 9.0);
		T m_vertical_fov = DEFAULT_FOV;
		T m_viewport_height = calculate_default_viewport_height();
		T m_viewport_width = m_aspect_ratio * m_viewport_height;
		T m_focal_length = narrow_cast<T>(1.0);
		T m_lens_radius = narrow_cast<T>(0.25);
		Point3 m_origin = {narrow_cast<T>(0), narrow_cast<T>(0), narrow_cast<T>(0)};
		Point3 m_focal_point = {narrow_cast<T>(0), narrow_cast<T>(0), narrow_cast<T>(-1)};
		Vec3 m_view_up = {narrow_cast<T>(0), narrow_cast<T>(1), narrow_cast<T>(0)};
		Vec3 m_w = calculate_w();
		Vec3 m_u = calculate_u();
		Vec3 m_v = calculate_v();
		Vec3 m_horizontal_axes = calculate_horizontal_axes();
		Vec3 m_vertical_axes = calculate_vertical_axes();
		Point3 m_lower_left = calculate_lower_left();

		[[nodiscard]] inline constexpr auto calculate_lower_left() noexcept -> Point3 {
			return m_origin - m_horizontal_axes / narrow_cast<T>(2.0)
				   - m_vertical_axes / narrow_cast<T>(2.0) - m_focal_length * m_w;
		}

		[[nodiscard]] inline constexpr auto
		calculate_viewport_height(T viewport_height) noexcept -> T {
			const auto theta = degrees_to_radians(m_vertical_fov);
			const auto h = Trig::tan(theta / narrow_cast<T>(2));
			return viewport_height * h;
		}

		[[nodiscard]] inline constexpr auto calculate_default_viewport_height() noexcept -> T {
			constexpr auto theta = degrees_to_radians(DEFAULT_FOV);
			constexpr auto h = Trig::tan(theta / narrow_cast<T>(2));
			return narrow_cast<T>(2) * h;
		}

		[[nodiscard]] inline constexpr auto calculate_horizontal_axes() noexcept -> Vec3 {
			return m_focal_length * m_viewport_width * m_u;
		}

		[[nodiscard]] inline constexpr auto calculate_vertical_axes() noexcept -> Vec3 {
			return m_focal_length * m_viewport_height * m_v;
		}

		[[nodiscard]] inline constexpr auto calculate_w() noexcept -> Vec3 {
			return (m_origin - m_focal_point).as_vec().normalized();
		}

		[[nodiscard]] inline constexpr auto calculate_u() noexcept -> Vec3 {
			return m_view_up.cross_prod(m_w).normalized();
		}

		[[nodiscard]] inline constexpr auto calculate_v() noexcept -> Vec3 {
			return m_w.cross_prod(m_u);
		}
	};
} // namespace graphics
