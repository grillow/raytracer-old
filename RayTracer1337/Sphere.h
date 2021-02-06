#pragma once
#include "Shape.h"

class Sphere : public Shape {
public:
	Sphere(Vector3 _position, double _radius) : center(_position), radius(_radius) {}

	bool Intersect(const Ray& ray, double& t) const {
		Vector3 k = ray.origin - center;
		double b = Vector3::Dot(k, ray.direction);
		double c = k.MagnitudeSqr() - radius * radius;
		double d = b * b - c;

		if (d >= 0) {
			double sqrtd = sqrt(d);
			double t1 = -b + sqrtd;
			double t2 = -b - sqrtd;
			double t_min = std::min(t1, t2);
			double t_max = std::max(t1, t2);
			t = (t_min >= 0) ? t_min : t_max;
			return t > 0;
		}

		return false;
	}

	Vector3 normal(const Vector3 p) const {
		return (p - center) / radius;
	}

protected:
	Vector3 center;
	double radius;

};