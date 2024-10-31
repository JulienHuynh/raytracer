#ifndef RAY_H
#define RAY_H

#include "Color.hpp"
#include "Vector3.h"

class Ray {
public:
    Vector3 origin;
    Vector3 direction;

    Ray(const Vector3& origin, const Vector3& direction)
        : origin(origin), direction(direction.normalized()) {}

    Vector3 getPoint(float t) const {
        return origin + direction * t;
    }
};
#endif