#pragma once

#include <grillowlib/vector.h>

struct Ray {
public:
	Ray(Vector3& _origin, Vector3& _direction) : origin(_origin), direction(_direction) {}
	Ray(Vector3 _origin, Vector3 _direction) : origin(_origin), direction(_direction) {}
	Ray() : origin(), direction() {}
	Vector3 origin;
	Vector3 direction;
};