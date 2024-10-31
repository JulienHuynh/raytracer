#include <iostream> 
#include <vector>
#include "Vector3.h"
#include "Ray.h"
#include "Sphere.h"
#include "Light.h"
#include "Color.hpp"
#include "Scene.h"


Color shade(const Ray &ray, const std::vector<Sphere> &spheres, const std::vector<Light> &lights, int depth = 3)
{
    float t;
    int id;

    if (hit(ray, spheres, t, id))
    {
        Vector3 hit_point = ray.origin + ray.direction * t;
        Vector3 normal = (hit_point - spheres[id].center).normalized();
        Color color = spheres[id].color * 0.1; // Ambient light

        for (const auto &light : lights)
        {
            Vector3 light_dir = (light.position - hit_point).normalized();
            float diff = std::max(0.0f, normal.dot(light_dir));
            color = color + spheres[id].color * light.color * diff;
        }

        if (spheres[id].reflect && depth > 0)
        {
            Vector3 reflect_dir = ray.direction - normal * 2 * ray.direction.dot(normal);
            //Debug info
            std::cout << "Point d'impact: " << hit_point.x << ", " << hit_point.y << ", " << hit_point.z << std::endl;
            std::cout << "Normale: " << normal.x << ", " << normal.y << ", " << normal.z << std::endl;
            std::cout << "Direction d'origine du rayon: " << ray.direction.x << ", " << ray.direction.y << ", " << ray.direction.z << std::endl;
            std::cout << "Direction du reflet: " << reflect_dir.x << ", " << reflect_dir.y << ", " << reflect_dir.z << std::endl;

            Ray reflect_ray(hit_point, reflect_dir); 
            color = color + shade(reflect_ray, spheres, lights, depth - 1) * 0.5; 
        }
        return color;
    }
    return Color(0, 0, 0); // Background color
}
