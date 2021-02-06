#pragma once
#include "Ray.h"

class Shape {
public:
	virtual bool Intersect(const Ray& ray, double& t) const = 0;
	virtual Vector3 normal(const Vector3 p) const = 0;
};