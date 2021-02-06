#pragma once
#include "Material.h"
#include "Shape.h"

#include <memory>

class Mesh {
public:
	Mesh(Material _material, std::unique_ptr<Shape> _shape) : material(_material), shape(std::move(_shape)) {}

	bool Intersect(const Ray& ray, double& t) {
		return shape->Intersect(ray, t);
	}
	Vector3 normal(Vector3 p) {
		return shape->normal(p);
	}

	const Material material;
private:
	const std::unique_ptr<Shape> shape;
};