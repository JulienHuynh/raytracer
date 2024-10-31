#ifndef GENERATESHAPES_H
#define GENERATESHAPES_H
#include <Light.h>
#include <Plane.h>
#include <Sphere.h>
#include <vector>

#endif // GENERATESHAPES_H

std::vector<Sphere> generate_spheres()
{
    std::vector<Sphere> spheres = {
        Sphere(Vector3(0, 1, 6), 1, Color(1, 0, 0), true),
        Sphere(Vector3(0, 3.5, 6), 1, Color(1, 1, 0), true),
        Sphere(Vector3(2, 1, 9), 1, Color(0, 1, 0), true)};

    return spheres;
}

Plane generate_plane()
{
    return Plane(Vector3(0, -0.5, 0), Vector3(0, 1, 0));
}

std::vector<Light> generate_lights()
{
    std::vector<Light> lights = {
        Light(Vector3(3, 6, 0), Color(1, 1, 1)) // White light
    };
    return lights;
}

std::vector<Cube> generate_cubes()
{
    std::vector<Cube> cubes = {
        Cube(Vector3(5, 0.5, 6), 2, Color(0, 0, 1), true),
        Cube(Vector3(-3, 0.5, 3), 1, Color(0, 1, 0))};

    return cubes;
}