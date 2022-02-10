#ifndef WORLD_HPP
#define WORLD_HPP

#include <glm/glm.hpp>

#include <array>
#include <memory>

#include "Geometry/2D/Triangle.hpp"
#include "Geometry/2D/Rectangle.hpp"

#include "Camera.hpp"

struct World {
    // Geometry Shapes
    std::unique_ptr<Triangle> my_triangle = nullptr;
    std::unique_ptr<Rectangle> my_rectangle = nullptr;

    // Camera
    std::unique_ptr<Camera> my_camera = nullptr;

    bool culling = false;

    void create();
};
#endif
