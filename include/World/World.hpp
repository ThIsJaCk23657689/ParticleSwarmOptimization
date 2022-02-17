#ifndef WORLD_HPP
#define WORLD_HPP

#include <glm/glm.hpp>

#include <array>
#include <memory>

#include "Geometry/2D/Triangle.hpp"
#include "Geometry/2D/Rectangle.hpp"
#include "Geometry/2D/Cornfield.hpp"

#include "Camera.hpp"

#include "Light/Light.hpp"

struct World {
    // Geometry Shapes
    std::unique_ptr<Triangle> my_triangle = nullptr;
    std::unique_ptr<Rectangle> my_rectangle = nullptr;
    std::unique_ptr<Cornfield> my_cornfield = nullptr;

    // Camera
    std::unique_ptr<Camera> my_camera = nullptr;

    // Material
    float shininess = 4.0f;

    // Lighting
    std::unique_ptr<Light> my_spotlight = nullptr;

    bool culling = false;
    bool wire_mode = false;

    void create();
};
#endif
