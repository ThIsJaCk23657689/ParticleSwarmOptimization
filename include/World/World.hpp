#ifndef WORLD_HPP
#define WORLD_HPP

#include <glm/glm.hpp>

#include <array>
#include <memory>

#include "Geometry/2D/Triangle.hpp"

struct World {
    // Geometry Shapes
    std::unique_ptr<Triangle> my_triangle = nullptr;

    bool culling = false;

    void create();
};
#endif
