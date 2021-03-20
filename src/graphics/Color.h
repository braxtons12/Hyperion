#pragma once

#include <iostream>

#include "../base/StandardIncludes.h"

namespace graphics {
	enum class ColorChannel : size_t
	{
		R = static_cast<size_t>(Vec3Idx::X),
		G = static_cast<size_t>(Vec3Idx::Y),
		B = static_cast<size_t>(Vec3Idx::Z)
	};

	template<FloatingPoint T = float>
	class Color {
	  public:
		constexpr Color() noexcept = default;
		constexpr Color(T r, T g, T b) noexcept : m_vec(r, g, b) {
		}
		template<SignedNumeric TT = T>
		explicit constexpr Color(const Vec3<TT>& vec) noexcept
			: m_vec(narrow_cast<T>(vec.x()), narrow_cast<T>(vec.y()), narrow_cast<T>(vec.z())) {
		}
		template<SignedNumeric TT = T>
		explicit constexpr Color(Vec3<TT>&& vec) noexcept
			: m_vec(narrow_cast<T>(vec.x()), narrow_cast<T>(vec.y()), narrow_cast<T>(vec.z())) {
		}
		constexpr Color(const Color& color) noexcept = default;
		constexpr Color(Color&& color) noexcept = default;
		constexpr ~Color() noexcept = default;

		inline constexpr auto r() const noexcept -> const T& {
			return m_vec.x();
		}
		inline constexpr auto r() noexcept -> T& {
			return m_vec.x();
		}

		inline constexpr auto g() const noexcept -> const T& {
			return m_vec.y();
		}
		inline constexpr auto g() noexcept -> T& {
			return m_vec.y();
		}

		inline constexpr auto b() const noexcept -> const T& {
			return m_vec.z();
		}
		inline constexpr auto b() noexcept -> T& {
			return m_vec.z();
		}

		inline constexpr auto as_vec() noexcept -> Vec3<T> {
			return m_vec;
		}

		inline constexpr auto
		write(std::ostream& out, size_t samples_per_pixel, T gamma) noexcept -> void {
			Color col{*this};

			const auto scale = narrow_cast<T>(1.0) / narrow_cast<T>(samples_per_pixel);
			// constexpr auto scale = narrow_cast<T>(1.0);
			col *= scale;
			T& r = col.r();
			T& g = col.g();
			T& b = col.b();
			r = Exponentials::pow(r, narrow_cast<T>(1.0) / gamma);
			g = Exponentials::pow(g, narrow_cast<T>(1.0) / gamma);
			b = Exponentials::pow(b, narrow_cast<T>(1.0) / gamma);

			out << col;
		}

		constexpr auto operator=(const Color& color) noexcept -> Color& = default;
		constexpr auto operator=(Color&& color) noexcept -> Color& = default;

		inline constexpr auto operator[](ColorChannel channel) noexcept -> T& {
			const auto elem = static_cast<Vec3Idx>(channel);
			return m_vec[elem];
		}
		inline constexpr auto operator[](ColorChannel channel) const noexcept -> T {
			const auto elem = static_cast<Vec3Idx>(channel);
			return m_vec[elem];
		}

		template<SignedNumeric TT = T>
		inline constexpr auto operator+(const Color<TT>& color) const noexcept -> Color {
			return Color(m_vec + color.m_vec);
		}

		template<SignedNumeric TT = T>
		inline constexpr auto operator+=(const Color<TT>& color) noexcept -> Color& {
			m_vec += color.m_vec;
			return *this;
		}

		template<SignedNumeric TT = T>
		inline constexpr auto operator-(const Color<TT>& color) const noexcept -> Color {
			return Color(m_vec - color.m_vec);
		}

		template<SignedNumeric TT = T>
		inline constexpr auto operator-=(const Color<TT>& color) noexcept -> Color& {
			m_vec -= color.m_vec;
			return *this;
		}

		inline constexpr auto operator*(SignedNumeric auto s) const noexcept -> Color {
			return Color(m_vec * s);
		}

		friend inline constexpr auto
		operator*(SignedNumeric auto lhs, const Color& rhs) noexcept -> Color {
			return rhs * lhs;
		}

		template<FloatingPoint TT = float>
		inline constexpr auto operator*(const Color<TT>& rhs) const noexcept -> Color<TT> {
			Color<TT> temp = {narrow_cast<TT>(r()), narrow_cast<TT>(g()), narrow_cast<TT>(b())};
			temp.r() *= rhs.r();
			temp.g() *= rhs.g();
			temp.b() *= rhs.b();

			return temp;
		}

		template<SignedIntegral TT = int>
		inline constexpr auto operator*(const Color<TT>& rhs) const noexcept -> Color<TT> {
			Color<TT> temp = rhs;
			temp.r() = narrow_cast<TT>(narrow_cast<T>(temp.r()) * r());
			temp.g() = narrow_cast<TT>(narrow_cast<T>(temp.g()) * g());
			temp.b() = narrow_cast<TT>(narrow_cast<T>(temp.b()) * b());

			return temp;
		}

		template<SignedNumeric TT = float>
		inline auto operator*=(const Color<TT>& rhs) noexcept -> Color& {
			*this = *this * rhs;
			return *this;
		}

		inline constexpr auto operator*=(SignedNumeric auto s) noexcept -> Color& {
			m_vec *= s;
			return *this;
		}

		inline constexpr auto operator/(SignedNumeric auto s) const noexcept -> Color {
			return Color(m_vec / s);
		}

		friend inline constexpr auto
		operator/(SignedNumeric auto lhs, const Color& rhs) noexcept -> Color {
			return rhs / lhs;
		}

		inline constexpr auto operator/=(SignedNumeric auto s) noexcept -> Color& {
			m_vec /= s;
			return *this;
		}

		friend inline constexpr auto
		operator<<(std::ostream& out, const Color& color) noexcept -> std::ostream& {
			return out << narrow_cast<int>(
					   narrow_cast<T>(256)
					   * clamp<T>(color.r(), narrow_cast<T>(0), narrow_cast<T>(0.999)))
					   << ' '
					   << narrow_cast<int>(
							  narrow_cast<T>(256)
							  * clamp<T>(color.g(), narrow_cast<T>(0), narrow_cast<T>(0.999)))
					   << ' '
					   << narrow_cast<int>(
							  narrow_cast<T>(256)
							  * clamp<T>(color.b(), narrow_cast<T>(0), narrow_cast<T>(0.999)))
					   << '\n';
		}

	  private:
		Vec3<T> m_vec = Vec3<T>();
	};

	template<FloatingPoint T>
	explicit Color(T, T, T) -> Color<T>;

	template<FloatingPoint T = float>
	Color() -> Color<float>;

} // namespace graphics
