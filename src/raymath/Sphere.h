#pragma once

#include "Vector3.h"
#include "Ray.h"
#include "Color.hpp"

class Sphere
{
public:
    Vector3 center;
    float radius;
    Color color;
    bool reflect = false;

    Sphere(const Vector3 &c, float r, const Color &col, bool refl = false)
        : center(c), radius(r), color(col), reflect(refl) {}

    bool intersect(const Ray &ray, float &t) const
    {
        Vector3 oc = center - ray.origin;
        float dotProd = oc.dot(ray.direction);

        if (dotProd < 0)
        {
            return false;
        }

        Vector3 op = ray.direction * dotProd;
        Vector3 p = ray.origin + op;
        Vector3 cp = p - center;
        float distance = cp.length();
        if (distance <= radius)
        {
            t = dotProd - sqrt(radius * radius - distance * distance);
            return true;
        }
        return false;
    }
};