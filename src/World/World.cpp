#include "World/World.hpp"

void World::create() {
    my_triangle = std::make_unique<Triangle>();
    my_rectangle = std::make_unique<Rectangle>(1.0f, 1.0f, Orientation::POS_Y);

    my_camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 5.0f), true);
}