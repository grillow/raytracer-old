#pragma once
#include "Shape.h"

class Triangle : public Shape {
public:
	Triangle(Vector3 _v0, Vector3 _v1, Vector3 _v2) : v0(_v0), v1(_v1), v2(_v2) { Normal = Vector3::Cross(v1 - v0, v2 - v0).Normalized(); }

	bool Intersect(const Ray& ray, double& t) const {
		const Vector3 v0v1 = v1 - v0;
		const Vector3 v0v2 = v2 - v0;
		const Vector3 pvec = Vector3::Cross(ray.direction, v0v2);
		const double det = Vector3::Dot(v0v1, pvec);
		const double invdet = 1.0 / det;
		const Vector3 tvec = ray.origin - v0;
		const double u = Vector3::Dot(tvec, pvec) * invdet;
		if (u < 0 || u > 1)
			return false;
		const Vector3 qvec = Vector3::Cross(tvec, v0v1);
		const double v = Vector3::Dot(ray.direction, qvec) * invdet;
		if (v < 0 || u + v > 1)
			return false;
		t = Vector3::Dot(v0v2, qvec) * invdet;
		return t > 0;
	}

	///TODO -Normal under some conditions?
	Vector3 normal(const Vector3 p) const {
		return Normal;
	}

private:
	Vector3 v0;
	Vector3 v1;
	Vector3 v2;
	Vector3 Normal;
};