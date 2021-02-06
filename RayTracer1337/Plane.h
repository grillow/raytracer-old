#pragma once
#include "Shape.h"

// Ax + By + Cz + D = 0, Normal is { A, B, C }
// Center is a point (0, 0, - D / C)
class Plane : public Shape {
public:
	Plane(double _A, double _B, double _C, double _D) : Normal(_A, _B, _C), D(_D), Normal_Normalized(Normal.Normalized()) {}
	Plane(Vector3 _ABC, double _D) : Normal(_ABC), D(_D), Normal_Normalized(Normal.Normalized()) {}

	bool Intersect(const Ray& ray, double& t) const {
		double denominator = Vector3::Dot(ray.direction, Normal);
		t = -(Vector3::Dot(ray.origin, Normal) + D) / denominator;
		if (t >= 0)
			return true;
		return false;
	}

	Vector3 normal(const Vector3 p) const {
		return Normal_Normalized;
	}


protected:
	const Vector3 Normal;
	const Vector3 Normal_Normalized;
	const double D;

};