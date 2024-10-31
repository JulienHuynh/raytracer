#pragma once

#include <vector>
#include <cmath> 
#include "Ray.h"
#include "Sphere.h"
#include "Cube.h" 
#include "Light.h"
#include "Color.hpp"
#include "Plane.h"
#include "Scene.h"

Color shade(const Ray &ray, const std::vector<Sphere> &spheres, const std::vector<Cube> &cubes, const std::vector<Light> &lights, const Plane &plane, int depth = 3)
{
    float closest_t = 1e20;
    Color color(0, 0, 0);
    bool hit_anything = false;
    int id;
    bool isCube = false;

    // Vérifier l'intersection avec le plan
    float t_plane;
    if (plane.intersect(ray, t_plane) && t_plane < closest_t)
    {
        hit_anything = true;
        closest_t = t_plane;

        Vector3 hit_point = ray.origin + ray.direction * t_plane;

        // Calcul du damier en fonction de x et z
        int checker_size = 1;
        bool is_black = (static_cast<int>(std::floor(hit_point.x / checker_size) + std::floor(hit_point.z / checker_size)) % 2) == 0;
        color = is_black ? Color(0, 0, 0) : Color(1, 1, 1);

        // Calcul de l'éclairage pour le damier (ombrage)
        for (const auto &light : lights)
        {
            Vector3 light_dir = (light.position - hit_point).normalized();
            Ray shadow_ray(hit_point + light_dir * 1e-4, light_dir);
            float t_shadow;
            int id_shadow;

            bool shadow_hit = hit(shadow_ray, spheres, cubes, t_shadow, id_shadow, isCube);
            if (!shadow_hit || t_shadow > (light.position - hit_point).length())
            {
                Vector3 normal = plane.normal;
                float diff = std::max(0.0f, normal.dot(light_dir));
                color = color * light.color * diff;
            }
            else
            {
                color = Color(0, 0, 0);
            }
        }
    }

    // Vérifier l'intersection avec chaque sphère et chaque cube
    float t_sphere;
    if (hit(ray, spheres, cubes, closest_t, id, isCube))
    {
        hit_anything = true;
        Vector3 hit_point = ray.origin + ray.direction * closest_t;
        Vector3 normal;

        if (isCube) {
            // Intersection avec un cube
            Cube cube = cubes[id];
            Vector3 local_hit = hit_point - cube.center;

            // Déterminer la normale en fonction de la face du cube touchée
            normal = Vector3(
                std::abs(local_hit.x) > cube.size / 2 - 1e-4 ? (local_hit.x > 0 ? 1 : -1) : 0,
                std::abs(local_hit.y) > cube.size / 2 - 1e-4 ? (local_hit.y > 0 ? 1 : -1) : 0,
                std::abs(local_hit.z) > cube.size / 2 - 1e-4 ? (local_hit.z > 0 ? 1 : -1) : 0
            ).normalized();

            color = cube.color * 0.1;

            for (const auto &light : lights)
            {
                Vector3 light_dir = (light.position - hit_point).normalized();
                float diff = std::max(0.0f, normal.dot(light_dir));
                color = color + cube.color * light.color * diff;
            }

            if (cube.reflect && depth > 0)
            {
                Vector3 reflect_dir = ray.direction - normal * 2 * ray.direction.dot(normal);
                Ray reflect_ray(hit_point, reflect_dir);
                color = color + shade(reflect_ray, spheres, cubes, lights, plane, depth - 1) * 0.5;
            }
        }
        else {
            // Intersection avec une sphère
            Sphere sphere = spheres[id];
            normal = (hit_point - sphere.center).normalized();
            color = sphere.color * 0.1;

            for (const auto &light : lights)
            {
                Vector3 light_dir = (light.position - hit_point).normalized();
                float diff = std::max(0.0f, normal.dot(light_dir));
                color = color + sphere.color * light.color * diff;
            }

            if (sphere.reflect && depth > 0)
            {
                Vector3 reflect_dir = ray.direction - normal * 2 * ray.direction.dot(normal);
                Ray reflect_ray(hit_point, reflect_dir);
                color = color + shade(reflect_ray, spheres, cubes, lights, plane, depth - 1) * 0.5;
            }
        }
    }

    return hit_anything ? color : Color(0, 0, 0);
}
