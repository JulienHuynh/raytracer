#include <iostream>
#include <vector>
#include <chrono>
#include "Color.hpp"
#include "Image.hpp"
#include "Vector3.h"
#include "Ray.h"
#include "Sphere.h"
#include "Light.h"
#include "Scene.h"
#include "Shader.h"
#include "Plane.h"
#include "Cube.h"
#include "GenerateShapes.h"

using namespace std;

int main()
{

  int width = 1920;
  int height = 1080;
  int antiAliasingSamplesPerPixel = 8;
  Image image(width, height, Color(0, 0, 0));
  float aspectRatio = (float)width / (float)height;

  Vector3 cameraOrigin(0, 5, -10); // Position de la caméra
  float viewportZ = 1.0f;

  // Création des objets de la scène
  Plane floor = generate_plane(); // Plan horizontal (y=0)

  std::vector<Sphere> spheres = generate_spheres();

  std::vector<Light> lights = generate_lights();

  std::vector<Cube> cubes = generate_cubes();

  auto start = std::chrono::high_resolution_clock::now();

  for (int y = 0; y < height; y++)
  {
    for (int x = 0; x < width; x++)
    {
      Color pixelColor(0, 0, 0);

      // Multiéchantillonage pour l'antialiasing
      for (int sample = 0; sample < antiAliasingSamplesPerPixel; sample++)
      {
        // Générer un décalage aléatoire pour chaque sous-échantillon
        float uOffset = static_cast<float>(rand()) / RAND_MAX;
        float vOffset = static_cast<float>(rand()) / RAND_MAX;

        float u = ((x + uOffset) / (float)(width)-0.5) * aspectRatio;
        float v = -((y + vOffset) / (float)(height)) + 0.5;

        Vector3 direction(u, v, viewportZ);
        Ray ray(cameraOrigin, direction.normalized());

        pixelColor += shade(ray, spheres, cubes, lights, floor, 3);
      }

      // Calculer la couleur moyenne des échantillons
      pixelColor /= antiAliasingSamplesPerPixel;
      image.SetPixel(x, y, pixelColor);
    }
  }

  auto end = std::chrono::high_resolution_clock::now();
  // Calculer la durée d'exécution
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

  image.WriteFile("ray_tracing_output.png");
  cout << "Image generated: ray_tracing_output.png" << endl;
  cout << "Time taken to generate image: " << duration << " milliseconds" << endl;

  return 0;
}
