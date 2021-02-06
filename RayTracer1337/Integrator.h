#pragma once
#include "Image.h"
#include "Scene.h"
#include "Camera.h"
#include "RenderOptions.h"

#include <iostream>
#include "SimpleTimer.h"

class Integrator {
public:
	Image Render(const Scene& scene, const Camera& camera, const RenderOptions options) {
		SimpleTimer timer(std::cout, "Render");
		total_rays = 0;
		const size_t width = camera.get_width();
		const size_t height = camera.get_height();
		Image image(width, height);

		for (size_t i = 0; i < width; ++i) {
			for (size_t j = 0; j < height; ++j) {
				Color c;
				for (size_t i0 = 0; i0 < options.rays_per_pixel_side; ++i0) {
					for (size_t j0 = 0; j0 < options.rays_per_pixel_side; ++j0) {
						Ray ray = camera.buildRaySuperSampling(i, j, i0, j0, options.rays_per_pixel_side);
						c = c + Trace(scene, ray, options.ray_depth);
					}
					
				}
				image.at(i, j) = c / (options.rays_per_pixel);
			}
			if ((i + 1) % (width / 10) == 0) {
				std::cout << "% " << (((double)i + 1) / (double)width) * 100 << "\n";
			}
		}

		std::cout << "Image: " << width << "x" << height << "(SSAA:" << options.rays_per_pixel << ")" << std::endl;
		std::cout << "Total primary rays:     " << width * height * options.rays_per_pixel << std::endl;
		std::cout << "Total rays:             " << total_rays << std::endl;
		std::cout << "Rays per primary ray:   " << 100 * (double)total_rays / ((double)width * (double)height * options.rays_per_pixel) << "%" << std::endl;
		return image;
	}


	///TODO
	// 1) primary ray
	// 2) hit -> shadow rays + reflected ray + refracted ray
	// 3) math / physics calculations

	const Color miss { 0, 0, 0 };
	Color Trace(const Scene& scene, Ray& ray, size_t depth) {
		--depth;
		if (depth < 0)
			return miss;

		++total_rays;
		double t;
		Vector3 normal;
		Material material;
		if (!scene.Intersect(ray, t, normal, material))
			return miss;

		const Color self = material.color * (1 - material.k_reflection - material.k_refraction);
		const Color light = Shade(scene, ray.origin + t * ray.direction, normal);
		Color reflection;
		
		
		if (material.k_reflection > 0) {
			Ray reflected;
			reflected.origin = ray.origin + t * ray.direction;
			reflected.direction = reflection_direction(ray.direction, normal);
			reflected.origin = reflected.origin + 0.000001 * reflected.direction;
			reflection = Trace(scene, reflected, depth) * material.k_reflection;
		}

		return (self + light + reflection).Clamped();
	}

	Vector3 reflection_direction(const Vector3& direction, const Vector3& normal) {
		return (direction - 2 * Vector3::Dot(direction, normal) * normal).Normalized();
	}

	Color Shade(const Scene& scene, const Vector3 point, const Vector3 N) {
		Color color;
		Vector3 normal;
		Material material;
		for (size_t i = 0; i < scene.light_sources.size(); ++i) {
			double t = DBL_MAX;
			Ray ray;
			ray.direction = scene.light_sources[i]->Position - point;
			ray.origin = point + 0.000001 * ray.direction;
			const double t_max = ray.direction.Magnitude();
			ray.direction /= t_max;
			const bool isect = scene.Intersect(ray, t, normal, material);
			if (!isect || (isect && t >= t_max)) {
				//double shade_cos = std::max(0.0, Vector3::AngleBetweenCos(N, ray.direction)); //Dima's
				const double shade_cos = abs(Vector3::Dot(N, ray.direction));
				color = color + scene.light_sources[i]->color * (scene.light_sources[i]->Intensity / (4 * M_PI * t_max * t_max)) * shade_cos;
			}
		}
		return color;
	}

	/*Color Shade(const Scene& scene, const Vector3 point, Vector3 N, const Vector3 view) {
		Color color;
		Vector3 normal;
		Material material;
		for (size_t i = 0; i < scene.light_sources.size(); ++i) {
			double t = DBL_MAX;
			Ray ray;
			ray.direction = scene.light_sources[i]->Position - point;
			ray.origin = point + 0.000001 * ray.direction;
			const double t_max = ray.direction.Magnitude();
			ray.direction /= t_max;
			const bool isect = scene.Intersect(ray, t, normal, material);
			if (!isect || (isect && t >= t_max)) {
				if (Vector3::Dot(-view, N) > 0)
					N = -N;
				const double k = std::pow(std::max(Vector3::Dot(N, (ray.direction + view).Normalized()), 0.0), 16);

				//color = color + scene.light_sources[i]->color * (scene.light_sources[i]->Intensity / (4 * M_PI * t_max * t_max)) * shade_cos;
				color = color + scene.light_sources[i]->color * k * scene.light_sources[i]->Intensity / (4 * M_PI * t_max * t_max);
			}
		}
		return color;
	}*/



	///TODO refraction


private:
	unsigned long long total_rays = 0;

};