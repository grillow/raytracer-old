#pragma once
#include <vector>
#include <memory>
#include "Mesh.h"
#include "Color.h"
#include "LightSource.h"
#include <limits>
#include <cfloat>

#include "3rdparty/OBJ_Loader.h"
#include "Triangle.h"

class Scene {
public:
	friend class Integrator;
	void Add(std::unique_ptr<Mesh> _mesh) {
		meshes.push_back(std::move(_mesh));
	}

	void Add(std::unique_ptr<LightSource> _light_source) {
		light_sources.push_back(std::move(_light_source));
	}

	void LoadFromOBJFile(const std::string filename, const Vector3 offset, const Vector3 scale, const Vector3 angles, const Material material) {
		objl::Loader loader;
		loader.LoadFile(filename);
		for (size_t i = 0; i < loader.LoadedMeshes.size(); ++i) {
			std::vector<objl::Vertex>& vertexes = loader.LoadedMeshes[i].Vertices;
			for (size_t j = 0; j < vertexes.size(); j = j + 3) {
				Vector3 v0 = { vertexes[j + 0].Position.X, vertexes[j + 0].Position.Y, vertexes[j + 0].Position.Z };
				v0.X *= scale.X; v0.Y *= scale.Y; v0.Z *= scale.Z;
				v0 = Vector3::Rotate(v0, { 1, 0, 0 }, angles.X); v0 = Vector3::Rotate(v0, { 0, 1, 0 }, angles.Y); v0 = Vector3::Rotate(v0, { 0, 0, 1 }, angles.Z);
				v0 += offset;
				Vector3 v1 = { vertexes[j + 1].Position.X, vertexes[j + 1].Position.Y, vertexes[j + 1].Position.Z };
				v1.X *= scale.X; v1.Y *= scale.Y; v1.Z *= scale.Z;
				v1 = Vector3::Rotate(v1, { 1, 0, 0 }, angles.X); v1 = Vector3::Rotate(v1, { 0, 1, 0 }, angles.Y); v1 = Vector3::Rotate(v1, { 0, 0, 1 }, angles.Z);
				v1 += offset;
				Vector3 v2 = { vertexes[j + 2].Position.X, vertexes[j + 2].Position.Y, vertexes[j + 2].Position.Z };
				v2.X *= scale.X; v2.Y *= scale.Y; v2.Z *= scale.Z;
				v2 = Vector3::Rotate(v2, { 1, 0, 0 }, angles.X); v2 = Vector3::Rotate(v2, { 0, 1, 0 }, angles.Y); v2 = Vector3::Rotate(v2, { 0, 0, 1 }, angles.Z);
				v2 += offset;

				meshes.push_back(std::make_unique<Mesh>(material, std::make_unique<Triangle>(v0, v1, v2)));
			}
		}
	}

	bool Intersect(const Ray& ray, double& t, Vector3& normal, Material& material) const {
		bool intersects = false;
		double tMin = DBL_MAX;
		size_t i_min = 0;
		for (size_t i = 0; i < meshes.size(); ++i) {
			double t_i;
			if (meshes[i]->Intersect(ray, t_i)) {
				intersects = true;
				if (t_i <= tMin) {
					tMin = t_i;
					i_min = i;
				}
			}
		}

		if (intersects) {
			t = tMin;
			normal = meshes[i_min]->normal(ray.origin + t * ray.direction);
			material = meshes[i_min]->material;
			return true;
		}
		return false;
	}

private:
	std::vector<std::unique_ptr<Mesh>> meshes;
	std::vector<std::unique_ptr<LightSource>> light_sources;

};
