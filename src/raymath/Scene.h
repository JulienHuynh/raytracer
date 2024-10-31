#pragma once

#include <vector>
#include "Sphere.h"
#include "Cube.h"
#include "Ray.h"

bool hit(const Ray& ray, const std::vector<Sphere>& spheres, const std::vector<Cube>& cubes, float& t, int& id, bool& isCube) {
    t = 1e20;
    bool hit_anything = false;

    // Vérifier les intersections avec les sphères
    for (int i = 0; i < spheres.size(); ++i) {
        float t_temp;
        if (spheres[i].intersect(ray, t_temp) && t_temp < t) {
            hit_anything = true;
            t = t_temp;
            id = i;
            isCube = false;
        }
    }

    // Vérifier les intersections avec les cubes
    for (int i = 0; i < cubes.size(); ++i) {
        float t_temp;
        if (cubes[i].intersect(ray, t_temp) && t_temp < t) {
            hit_anything = true;
            t = t_temp;
            id = i;
            isCube = true;
        }
    }

    return hit_anything;
}
