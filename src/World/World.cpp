#include "World/World.hpp"

void World::create() {
    // Geometry
    my_triangle = std::make_unique<Triangle>();
    my_rectangle = std::make_unique<Rectangle>(200.0f, 200.0f, Orientation::POS_Y);
    my_cornfield = std::make_unique<Cornfield>();

    // Camera
    my_camera = std::make_unique<Camera>(glm::vec3(0.0f, 250.0f, 50.0f), true);

    // Light
    my_spotlight = std::make_unique<Light>(glm::vec3(0.0f, 5.0f, 5.0f), glm::vec3(0.0f, -0.5f, -1.0f), true);
    my_spotlight->linear = 0.0f;
}