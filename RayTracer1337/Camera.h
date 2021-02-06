#pragma once
#include <grillowlib/Vector.h>
#include "Ray.h"


class Camera {
public:
	Camera(Vector3 _position, Vector3 _angles, double _FoV, size_t _width, size_t _height) : Position(_position), Angles(_angles), FoV(_FoV), img_width(_width), img_height(_height) {
		ComputeForward();
		ComputeRight();
		ComputeUp();
		ComputePlaneCenter();
		ComputeLeftUp();
	}

	Ray buildRay(const size_t i, const size_t j) const {
		return { Position, (left_up + ((double)i + 0.5) * right - ((double)j + 0.5) * up).Normalized() };
	}

	Ray buildRaySuperSampling(const size_t i, const size_t j, const size_t i0, const size_t j0, const size_t rays_per_side) const {
		const double x = i + (((double)i0 + 0.5) / (double)rays_per_side);
		const double y = j + (((double)j0 + 0.5) / (double)rays_per_side);
		return { Position, (left_up + x * right - y * up).Normalized() };
	}

	const size_t get_width() const {
		return img_width;
	}

	const size_t get_height() const {
		return img_height;
	}

protected:
	const Vector3 Position;
	const Vector3 Angles;
	const double FoV;

	const size_t img_width;
	const size_t img_height;

private:
	Vector3 right;
	Vector3 forward;
	Vector3 up;
	Vector3 plane_center;
	Vector3 left_up;

	void ComputeRight() {
		right = Vector3::Rotate({ 1, 0, 0 }, { 0, 0, 1 }, Angles.Z);
		right = Vector3::Rotate(right, forward, Angles.Y);
	}

	void ComputeForward() {
		forward = Vector3::Rotate({0, 1, 0}, { 1, 0, 0 }, Angles.X);
		forward = Vector3::Rotate(forward, { 0, 0, 1 }, Angles.Z);
	}

	void ComputeUp() {
		up = Vector3::Rotate({0, 0, 1}, { 1, 0, 0 }, Angles.X);
		up = Vector3::Rotate(up, { 0, 0, 1 }, Angles.Z);
		up = Vector3::Rotate(up, forward, Angles.Y);
	}

	void ComputePlaneCenter() {
		const double d = (img_width / 2) / tan(FoV / 2);
		plane_center = Position + forward * d;
	}

	void ComputeLeftUp() {
		left_up = {-(double)img_width / 2, 0, +(double)img_height / 2};
		left_up = Vector3::Rotate(left_up, { 1, 0, 0 }, Angles.X);
		left_up = Vector3::Rotate(left_up, { 0, 0, 1 }, Angles.Z);
		left_up = Vector3::Rotate(left_up, forward, Angles.Y);
		left_up += plane_center;
		left_up -= Position;
	}

};