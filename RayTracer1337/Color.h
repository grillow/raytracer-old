#pragma once

struct Color {
public:
	constexpr Color(float r, float g, float b, float a = 1) : r(r), g(g), b(b), a(a) {}
	constexpr Color() : r(0), g(0), b(0), a(1) {}
	constexpr bool operator==(const Color& other) const {
		return r == other.r && g == other.g && b == other.b && a == other.a;
	}
	constexpr bool operator!=(const Color& other) const {
		return r != other.r || g != other.g || b != other.b || a != other.a;
	}
	constexpr Color& operator=(const Color& other) {
		r = other.r;
		g = other.g;
		b = other.b;
		a = other.a;
		return *this;
	}
	constexpr Color operator+(const Color& c) const {
		return Color {r + c.r, g + c.g, b + c.b};
	}
	constexpr Color operator-(const Color& c) const {
		return Color {r - c.r, g +- c.g, b - c.b};
	}

	constexpr Color operator/(const float s) const {
		return Color {r / s, g / s, b / s};
	}
	friend constexpr Color operator*(const Color& c, const float s) {
		return Color {c.r * s, c.g * s, c.b * s, c.a};
	}
	friend constexpr Color operator*(const float s, const Color& c) {
		return Color {c.r * s, c.g * s, c.b * s, c.a};
	}

	Color Clamped() {
		float r0 = r;
		float g0 = g;
		float b0 = b;
		float a0 = a;
		if (r0 < 0)
			r0 = 0;
		if (r0 > 1)
			r0 = 1;
		if (g0 < 0)
			g0 = 0;
		if (g0 > 1)
			g0 = 1;
		if (b0 < 0)
			b0 = 0;
		if (b0 > 1)
			b0 = 1;
		if (a0 < 0)
			a0 = 0;
		if (a0 > 1)
			a0 = 1;
		return { r0, g0, b0, a0 };
	}

	float r;
	float g;
	float b;
	float a;
};
