#pragma once
#include "Image.h"

Image gradient(const size_t width, const size_t height, Color(*f)(float x, float y, float w, float h)) {
	Image image(width, height);
	for (size_t j = 0; j < height; ++j) {
		for (size_t i = 0; i < width; ++i) {
			image.at(i, j) = f((float)i, (float)j, (float)width, (float)height);
		}
	}
	return image;
}