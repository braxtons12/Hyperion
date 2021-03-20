#include <iostream>
#include <tuple>

#include "base/StandardIncludes.h"
#include "graphics/Camera.h"
#include "graphics/Color.h"
#include "graphics/Geometry.h"
#include "graphics/GeometryList.h"
#include "graphics/Ray.h"
#include "graphics/Sphere.h"
#include "graphics/materials/Lambertian.h"
#include "graphics/materials/Metal.h"
#include "math/Point3.h"
#include "math/Random.h"
#include "math/Vec3.h"

using Camera = graphics::Camera<float>;
using Color = graphics::Color<float>;
using Ray = graphics::Ray<float>;
using Geometry = graphics::Geometry<float>;
using GeometryList = graphics::GeometryList<float>;
using HitRecord = graphics::HitRecord<float>;
using Sphere = graphics::Sphere<float>;
using Lambertian = graphics::Lambertian<float>;
using Metal = graphics::Metal<float>;

inline constexpr auto
color_at(const Ray& ray, const GeometryList& geometries, size_t depth) noexcept -> Color {
	if(depth == 0) {
		return {0.0F, 0.0F, 0.0F};
	}

	HitRecord record;
	if(geometries.intersected(ray, 0.0F, Constants<float>::infinity, &record)) {
		// auto val = 0.5F * (record.m_normal + Vec3(1.0F, 1.0F, 1.0F));
		// return {val.x(), val.y(), val.z()};
		Ray scattered;
		Color attenuation;
		if(record.m_material->scatter(ray, record, &attenuation, &scattered)) {
			return attenuation * color_at(scattered, geometries, depth - 1);
		}
		return {0.0F, 0.0F, 0.0F};
	}

	const auto normalized_dir = ray.direction().normalized();
	const auto length = 0.5F * (normalized_dir.y() + 1.0F);
	return (1.0F - length) * Color(1.0F, 1.0F, 1.0F) + length * Color(0.5F, 0.7F, 1.0F);
}

auto main(int argc, char** argv) noexcept -> int {
	std::ignore = argc;
	std::ignore = argv;

	constexpr auto aspect_ratio = 16.0F / 9.0F;
	constexpr auto image_width = 800;
	constexpr auto image_height = narrow_cast<int>(narrow_cast<float>(image_width) / aspect_ratio);
	constexpr auto samples_per_pixel = 50;
	constexpr auto max_depth = 50ULL;
	constexpr auto gamma = 1.5F;

	constexpr Camera camera(aspect_ratio, 2.0F, 1.0F);

	GeometryList list(
		std::make_unique<Sphere>(Point3(0.0F, -100.5F, -1.0F),
								 100.0F,
								 std::make_unique<Lambertian>(Color(0.8F, 0.8F, 0.0F))));
	list.add<Sphere>(
		std::make_unique<Sphere>(Point3(0.0F, 0.0F, -1.0F),
								 0.5F,
								 std::make_unique<Lambertian>(Color(0.7F, 0.3F, 0.3F))));
	list.add<Sphere>(std::make_unique<Sphere>(Point3(-1.0F, 0.0F, -1.0F),
											  0.5F,
											  std::make_unique<Metal>(Color(0.8F, 0.8F, 0.8F))));
	list.add<Sphere>(std::make_unique<Sphere>(Point3(1.0F, 0.0F, -1.0F),
											  0.5F,
											  std::make_unique<Metal>(Color(0.8F, 0.6F, 0.2F))));

	Ray ray;
	Color pixel;
	auto u = 0.0F;
	auto v = 0.0F;

	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
	for(auto y = image_height - 1; y >= 0; --y) {
		std::cerr << "\rScanlines remaining: " << y << ' ' << std::flush;
		for(auto x = 0; x < image_width; ++x) {
			pixel = Color(0.0F, 0.0F, 0.0F);
			for(auto sample = 0; sample < samples_per_pixel; ++sample) {
				u = (narrow_cast<float>(x) + random_value()) / narrow_cast<float>(image_width - 1);
				v = (narrow_cast<float>(y) + random_value()) / narrow_cast<float>(image_height - 1);
				ray = camera.get_ray(u, v);
				pixel += color_at(ray, list, max_depth);
			}
			pixel.write(std::cout, samples_per_pixel, gamma);
		}
	}

	std::cerr << "\nDone\n";
	return 0;
}
