#pragma once

#include "Vector3.h"
#include "Ray.h"
#include "Color.hpp"


class Cube
{
public:
    Vector3 center;
    float size;
    Color color;
    bool reflect;

    Cube(const Vector3 &c, float s, const Color &col, bool refl = false)
        : center(c), size(s), color(col), reflect(refl) {}

    bool intersect(const Ray &ray, float &t) const
    {
        float t_min = -1e20, t_max = 1e20;

        // Calculer les plans de chaque face du cube pour tester les intersections
        for (int i = 0; i < 3; ++i)
        {
            float invD = 1.0f / ray.direction[i];
            float t0 = ((center[i] - size / 2) - ray.origin[i]) * invD;
            float t1 = ((center[i] + size / 2) - ray.origin[i]) * invD;

            if (invD < 0.0f) std::swap(t0, t1);
            t_min = t0 > t_min ? t0 : t_min;
            t_max = t1 < t_max ? t1 : t_max;

            if (t_max <= t_min)
                return false;
        }

        t = t_min;
        return true;
    }
};
