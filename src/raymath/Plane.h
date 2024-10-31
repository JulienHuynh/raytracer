// Plane.h
#pragma once
#include "Vector3.h"
#include "Ray.h"

class Plane
{
public:
    Vector3 point;   
    Vector3 normal;  

    Plane(const Vector3& p, const Vector3& n) : point(p), normal(n.normalized()) {}

    bool intersect(const Ray& ray, float& t) const
    {
        float denom = normal.dot(ray.direction);
        if (abs(denom) > 1e-4) {  // Vérifie que le rayon n'est pas parallèle au plan
            t = (point - ray.origin).dot(normal) / denom;
            return t >= 0;
        }
        return false;
    }
};
