#pragma once

#include <iostream>

class Color
{
private:
    float r = 0;
    float g = 0;
    float b = 0;

public:
    Color();
    Color(float r, float g, float b);
    ~Color();

    float R() const;
    float G() const;
    float B() const;

    Color operator+(Color const &col) const;
    Color operator*(float const &f) const;
    Color operator*(Color const &other) const;
    Color &operator=(Color const &col);
    Color &operator+=(Color const &col)
    {
        r += col.r;
        g += col.g;
        b += col.b;
        return *this;
    }
    Color &operator/=(float const &f)
    {
        r /= f;
        g /= f;
        b /= f;
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &_stream, Color const &col);
};