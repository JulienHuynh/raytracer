#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>
#include <iostream>

class Vector3
{
public:
    float x, y, z;

    Vector3() : x(0), y(0), z(0) {}
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

    float dot(const Vector3 &other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }
    Vector3 operator+(const Vector3 &other) const
    {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    Vector3 operator-(const Vector3 &other) const
    {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    Vector3 operator-() const
    {
        return Vector3(-x, -y, -z);
    }

    Vector3 operator*(float scalar) const
    {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }

    float length() const
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    Vector3 normalized() const
    {
        float len = length();
        return Vector3(x / len, y / len, z / len);
    }

    friend std::ostream &operator<<(std::ostream &os, const Vector3 &vec)
    {
        os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
        return os;
    }

    Vector3 cross(const Vector3 &other) const
    {
        return Vector3(y * other.z - z * other.y,
                       z * other.x - x * other.z,
                       x * other.y - y * other.x);
    }

    Vector3 reflect(const Vector3 &v, const Vector3 &normal)
    {
        return v - normal * 2 * v.dot(normal);
    }

    const float &operator[](int index) const
    {
        switch (index)
        {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            throw std::out_of_range("Index out of range");
        }
    }
};

#endif