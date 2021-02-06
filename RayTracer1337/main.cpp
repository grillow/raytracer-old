#include <iostream>
#include <conio.h>
#include <time.h>
#include <random>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <grillowlib/Vector.h>
#include "SimpleTimer.h"
#include "Image.h"
#include "Camera.h"
#include "Scene.h"
#include "Integrator.h"
#include "RenderOptions.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "LightSource.h"


void load_scene(Scene& scene) {
	SimpleTimer timer(std::cout, "load scene");
	scene.Add(std::make_unique<Mesh>(Material(0.5, 0.0, 0.0, { 0.0, 0.0, 0.0 }), std::make_unique<Plane>(0, 0, 1, 0)));

	const Material sphere_mat(0.0, 0.0, 0.0, { 0, 0.1, 0.1 });
	scene.Add(std::make_unique<Mesh>(sphere_mat, std::make_unique<Sphere>(Vector3{ 0, 0, 7.5 }, 2.5)));
	scene.Add(std::make_unique<Mesh>(sphere_mat, std::make_unique<Sphere>(Vector3{ 2.5, -7.5, 1.25 }, 1.25)));
	scene.Add(std::make_unique<Mesh>(sphere_mat, std::make_unique<Sphere>(Vector3{ -7.5, -5.5, 2.25 }, 2.25)));

	const Material cube_mat(0.5, 0.0, 0.0, {1, 1, 1});
	scene.Add(std::make_unique<Mesh>(cube_mat, std::make_unique<Triangle>(Vector3{ -2.5, -2.5, 0 }, Vector3{ -2.5, +2.5, 0 }, Vector3{ +2.5, +2.5, 0 })));
	scene.Add(std::make_unique<Mesh>(cube_mat, std::make_unique<Triangle>(Vector3{ -2.5, -2.5, 0 }, Vector3{ +2.5, -2.5, 0 }, Vector3{ +2.5, +2.5, 0 })));
	scene.Add(std::make_unique<Mesh>(cube_mat, std::make_unique<Triangle>(Vector3{ -2.5, -2.5, 5 }, Vector3{ -2.5, +2.5, 5 }, Vector3{ +2.5, +2.5, 5 })));
	scene.Add(std::make_unique<Mesh>(cube_mat, std::make_unique<Triangle>(Vector3{ -2.5, -2.5, 5 }, Vector3{ +2.5, -2.5, 5 }, Vector3{ +2.5, +2.5, 5 })));
	scene.Add(std::make_unique<Mesh>(cube_mat, std::make_unique<Triangle>(Vector3{ -2.5, -2.5, 0 }, Vector3{ -2.5, +2.5, 0 }, Vector3{ -2.5, +2.5, 5 })));
	scene.Add(std::make_unique<Mesh>(cube_mat, std::make_unique<Triangle>(Vector3{ -2.5, -2.5, 0 }, Vector3{ -2.5, -2.5, 5 }, Vector3{ -2.5, +2.5, 5 })));
	scene.Add(std::make_unique<Mesh>(cube_mat, std::make_unique<Triangle>(Vector3{ +2.5, -2.5, 0 }, Vector3{ +2.5, +2.5, 0 }, Vector3{ +2.5, +2.5, 5 })));
	scene.Add(std::make_unique<Mesh>(cube_mat, std::make_unique<Triangle>(Vector3{ +2.5, -2.5, 0 }, Vector3{ +2.5, -2.5, 5 }, Vector3{ +2.5, +2.5, 5 })));
	scene.Add(std::make_unique<Mesh>(cube_mat, std::make_unique<Triangle>(Vector3{ -2.5, +2.5, 0 }, Vector3{ +2.5, +2.5, 0 }, Vector3{ +2.5, +2.5, 5 })));
	scene.Add(std::make_unique<Mesh>(cube_mat, std::make_unique<Triangle>(Vector3{ -2.5, +2.5, 0 }, Vector3{ -2.5, +2.5, 5 }, Vector3{ +2.5, +2.5, 5 })));
	scene.Add(std::make_unique<Mesh>(cube_mat, std::make_unique<Triangle>(Vector3{ -2.5, -2.5, 0 }, Vector3{ +2.5, -2.5, 0 }, Vector3{ +2.5, -2.5, 5 })));
	scene.Add(std::make_unique<Mesh>(cube_mat, std::make_unique<Triangle>(Vector3{ -2.5, -2.5, 0 }, Vector3{ -2.5, -2.5, 5 }, Vector3{ +2.5, -2.5, 5 })));

	scene.Add(std::make_unique<LightSource>(Vector3{ +5.0, -10.0, +25.0 }, 5000, Color{ 1, 1, 1 }));
}

void load_deagle(Scene& scene) {
	SimpleTimer timer(std::cout, "load scene with .obj");
	scene.Add(std::make_unique<Mesh>(Material(0.5, 0.0, 0.0, { 0.0, 0.0, 0.0 }), std::make_unique<Plane>(0, 0, 1, 0)));
	scene.LoadFromOBJFile("models/deagle.obj", { -2.5, 0, +2.5 }, { 1, 1, 1 }, { 0, 0, 0 }, Material{ 0.5, 0, 0, Color{1, 1, 1} });
	scene.Add(std::make_unique<Mesh>(Material(0.5, 0.0, 0.0, Color{ 0.73, 0.18, 0.95 }), std::make_unique<Sphere>(Vector3{ -14.5, +5.5, 2.5 }, 2.5)));
	scene.Add(std::make_unique<Mesh>(Material(0.5, 0.0, 0.0, Color{ 0.1, 0.14, 0.98 }), std::make_unique<Sphere>(Vector3{ +13.5, -13.5, 5 }, 5)));
	scene.Add(std::make_unique<LightSource>(Vector3{ +5.0, +10.0, +25.0 }, 3000, Color{ 1, 1, 1 }));
}

void load_birthday(Scene& scene) {
	SimpleTimer timer(std::cout, "load scene with .obj");
	scene.Add(std::make_unique<Mesh>(Material(0.5, 0.0, 0.0, { 0.0, 0.0, 0.0 }), std::make_unique<Plane>(0, 0, 1, 0)));
	scene.LoadFromOBJFile("models/Galina_dr_1.obj", { -16, 0, 0 }, { 5, 5, 5 }, { 0, 0, 0 }, Material{ 0.0, 0, 0, Color{0, 0, 1} });
	scene.LoadFromOBJFile("models/heart.obj", { 0, 0, +3.0 }, { 1, 1, 1 }, { 0, 0, 0 }, Material{ 0.0, 0, 0, Color{1, 0, 0} });
	scene.Add(std::make_unique<LightSource>(Vector3{ +10.0, -5.0, +25.0 }, 3000, Color{ 1, 1, 1 }));

	scene.Add(std::make_unique<Mesh>(Material{ 0.5, 0.0, 0.0, Color{ 0.98, 0.33, 0.06 } }, std::make_unique<Sphere>(Vector3{ -9.00, -11.0, 0.75 }, 0.75)));
	scene.Add(std::make_unique<Mesh>(Material{ 0.5, 0.0, 0.0, Color{ 0.00, 1.00, 0.00 } }, std::make_unique<Sphere>(Vector3{ -26.0, +9.50, 1.50 }, 1.50)));
	scene.Add(std::make_unique<Mesh>(Material{ 0.5, 0.0, 0.0, Color{ 0.93, 0.06, 0.91 } }, std::make_unique<Sphere>(Vector3{ -16.0, +15.50, 3.50 }, 3.50)));
	scene.Add(std::make_unique<Mesh>(Material{ 0.5, 0.0, 0.0, Color{ 0.13, 0.00, 0.23 } }, std::make_unique<Sphere>(Vector3{ +15.0, +17.50, 1.50 }, 1.50)));
}

float rand_float() {
	return (float)rand() / RAND_MAX;
}

void load_spheres(Scene& scene) {
	SimpleTimer timer(std::cout, "load scene with random spheres");
	std::srand(time(0));
	const size_t N = 200;
	for (size_t i = 0; i < N; ++i) {
		const Material material{ rand_float(), 0.0, 0.0, { rand_float(), rand_float(), rand_float() } };
		Vector3 position;
		bool f = true;
		double z;
		while (f) {
			z = rand_float() * 1.5 + 0.5;
			position = { (rand_float() - 0.5) * 100, (rand_float() - 0.5) * 100, z };
			Ray ray(position, { 0, 0, 1 });
			double t;
			Vector3 n;
			Material m;
			f = scene.Intersect(ray, t, n, m);
		}
		scene.Add(std::make_unique<Mesh>(material, std::make_unique<Sphere>(position, z)));
	}
	scene.Add(std::make_unique<Mesh>(Material(0.5, 0.0, 0.0, { 0.0, 0.0, 0.0 }), std::make_unique<Plane>(0, 0, 1, 0)));
	scene.Add(std::make_unique<LightSource>(Vector3{ +0.0, +0.0, +1000.0 }, 0.75 * 10000000, Color{ 1, 1, 1 }));
}

void do_stuff() {
	SimpleTimer timer(std::cout, "whole process");

	Scene scene;
	load_scene(scene);
	//load_obj(scene);
	//load_spheres(scene);
	//load_birthday(scene);


	Camera camera({ 0, -20, 7.5 }, { -M_PI * 1.0 / 8, 0, 0 }, M_PI / 2, 1920, 1080);

	Integrator integrator;

	Image image = integrator.Render(scene, camera, {1, 16});

	image.SavePNG("images/" + std::to_string(time(0)));
}


int main() {
	do_stuff();
	_getch();
	return 0;
}
