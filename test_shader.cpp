#include <iostream>
#include <vector>
#include "Vector3.h"
#include "Ray.h"
#include "Sphere.h"
#include "Light.h"
#include "Color.hpp"
#include "Scene.h"
#include "Shader.h"

void test_hit_point()
{
    Vector3 cameraOrigin(0, 0, 0);
    Sphere sphere(Vector3(0, 0, 6), 1, Color(1, 0, 0));
    std::vector<Sphere> spheres = {sphere};
    std::vector<Light> lights;

    struct TestCase
    {
        Vector3 rayDirection;
        Vector3 expectedHitPoint;
    };

    std::vector<TestCase> testCases = {
        {Vector3(0, 0, -1).normalized(), Vector3(0, 0, 5)},
        {Vector3(0.01, 0, -1).normalized(), Vector3(0.0500125, 0, 5.00125)},
        {Vector3(0.5, 0.05, -1).normalized(), Vector3(2.63852, 0.263852, 5.27704)}};

    for (const auto &testCase : testCases)
    {
        Ray ray(cameraOrigin, testCase.rayDirection);
        float t;
        int id;
        if (hit(ray, spheres, t, id))
        {
            Vector3 hit_point = ray.origin + ray.direction * t;
            if ((hit_point - testCase.expectedHitPoint).length() < 1e-4)
            {
                std::cout << "Test passed for direction: " << testCase.rayDirection << std::endl;
            }
            else
            {
                std::cout << "Test failed for direction: " << testCase.rayDirection << std::endl;
                std::cout << "Expected: " << testCase.expectedHitPoint << ", but got: " << hit_point << std::endl;
            }
        }
        else
        {
            std::cout << "Test failed for direction: " << testCase.rayDirection << " (no hit)" << std::endl;
        }
    }
}

int main()
{
    test_hit_point();
    return 0;
}