#pragma once

struct RenderOptions {
public:
	RenderOptions(size_t _super_sampling, size_t _ray_depth = 16) : rays_per_pixel_side((size_t)std::pow(2, _super_sampling)), rays_per_pixel(rays_per_pixel_side * rays_per_pixel_side), ray_depth(_ray_depth) {}
	const size_t rays_per_pixel_side;
	const size_t rays_per_pixel;
	const size_t ray_depth;
};