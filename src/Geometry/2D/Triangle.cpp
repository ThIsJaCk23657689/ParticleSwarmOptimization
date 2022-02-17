#include "Geometry/2D/Triangle.hpp"

Triangle::Triangle() {
    Initialize();
}

void Triangle::GenerateVertices() {
    vertices = {
        Vertex { {-0.5f, -0.5f,  0.0f }, { 0.0, 0.0, 1.0 } },
        Vertex { { 0.5f, -0.5f,  0.0f }, { 0.0, 0.0, 1.0 } },
        Vertex { { 0.0f,  0.5f,  0.0f }, { 0.0, 0.0, 1.0 } },
    };

    indices = {
        0, 1, 2,
    };
}