#pragma once
#include "Shape.h"

class Box : public Shape {
public:
	Box(Vector3 _p0, Vector3 _p1) {
		p_min = {std::min(_p0.X, _p1.X), std::min(_p0.Y, _p1.Y), std::min(_p0.Z, _p1.Z)};
		p_max = {std::max(_p0.X, _p1.X), std::max(_p0.Y, _p1.Y), std::max(_p0.Z, _p1.Z)};
	}

	Box(Vector3& _p0, Vector3& _p1) {
		p_min = {std::min(_p0.X, _p1.X), std::min(_p0.Y, _p1.Y), std::min(_p0.Z, _p1.Z)};
		p_max = {std::max(_p0.X, _p1.X), std::max(_p0.Y, _p1.Y), std::max(_p0.Z, _p1.Z)};
	}

	bool Intersect(const Ray& ray, double& t) const {
		Vector3 inv_dir = { 1.0 / ray.direction.X, 1.0 / ray.direction.Y, 1.0 / ray.direction.Z };
		double t_min, t_max;
		double lo = inv_dir.X * (p_min.X - ray.origin.X);
		double hi = inv_dir.X * (p_max.X - ray.origin.X);
		t_min = std::min(lo, hi);
		t_max = std::max(lo, hi);

		double lo1 = inv_dir.Y * (p_min.Y - ray.origin.Y);
		double hi1 = inv_dir.Y * (p_max.Y - ray.origin.Y);
		t_min = std::max(t_min, std::max(lo1, hi1));
		t_max = std::min(t_max, std::max(lo1, hi1));

		double lo2 = inv_dir.Z * (p_min.Z - ray.origin.Z);
		double hi2 = inv_dir.Z * (p_max.Z - ray.origin.Z);

		t_min = std::max(t_min, std::min(lo2, hi2));
		t_max = std::min(t_max, std::max(lo2, hi2));

		t = t_min;

		return (t_min <= t_max) && (t_max > 0.0);
	}

	///TODO
	Vector3 normal(const Vector3 p) const {
		return {0, 0, 0};
	}

protected:
	Vector3 p_min;
	Vector3 p_max;
};