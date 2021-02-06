#pragma once
#include <grillowlib/Vector.h>

class LightSource {
public:
	LightSource(Vector3 _Position, float _Intensity, Color _color) : Position(_Position), Intensity(_Intensity), color(_color) {}
	LightSource(Vector3& _Position, float _Intensity, Color _color) : Position(_Position), Intensity(_Intensity), color(_color) {}

	Vector3 Position;
	float Intensity;
	Color color;

protected:

};