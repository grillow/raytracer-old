#pragma once
#include "Color.h"
#include "3rdparty/lodepng.h"
#include <algorithm>


struct Image {
public:
	Image(size_t w, size_t h) : width(w), height(h) {
		c = new Color[w * h];
	}

	Image(const Image& image) : Image(image.width, image.height) {
		std::copy(image.c, image.c + width * height, c);
	}

	bool operator==(Image& other) {
		if (width != other.width || height != other.height)
			return false;
		for (size_t i = 0; i < height; ++i) {
			for (size_t j = 0; j < width; ++j) {
				if (c[i * width + j] != other.c[i * width + j])
					return false;
			}
		}
		return true;
	}

	Color& at(const int i, const int j) {
		return c[j*width + i];
	}

	void SavePNG(std::string filename) {
		unsigned char* pixels = new unsigned char[width * height * 4];
		for (size_t i = 0; i < width * height; ++i) {
			Color p = c[i];
			pixels[sizeof(Color) / sizeof(float) * i + 0] = (unsigned char)(p.r * (float)255);
			pixels[sizeof(Color) / sizeof(float) * i + 1] = (unsigned char)(p.g * (float)255);
			pixels[sizeof(Color) / sizeof(float) * i + 2] = (unsigned char)(p.b * (float)255);
			pixels[sizeof(Color) / sizeof(float) * i + 3] = (unsigned char)(p.a * (float)255);
			//pixels[sizeof(Color)  / sizeof(float) * i + 3] = 255;
		}
		lodepng::encode(filename + ".png", pixels, width, height);
		delete[] pixels;
	}

	~Image() {
		delete[] c;
	}


private:
	const size_t width;
	const size_t height;
	Color* c;
};
