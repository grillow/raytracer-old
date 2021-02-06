#pragma once
#include "Color.h"

struct Material {
public:
	Material() : k_reflection(0), k_refraction(0), refractive_index(1), color(0, 0, 0) {};
	Material(float _k_reflection, float _k_refraction, float _refractive_index, Color _color) : k_reflection(_k_reflection), k_refraction(_k_refraction), refractive_index(_refractive_index), color(_color) {}
	float k_reflection;
	float k_refraction;
	float refractive_index;
	Color color;
};
