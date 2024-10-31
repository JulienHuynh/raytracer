
#pragma once

#include "Color.hpp"
#include "Vector3.h"

class Light {
public:
    Vector3 position;
    Color color;

    Light(const Vector3& pos, const Color& col) : position(pos), color(col) {}

    
};

