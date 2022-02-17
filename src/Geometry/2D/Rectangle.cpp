#include "Geometry/2D/Rectangle.hpp"

Rectangle::Rectangle() {
    Initialize();
}

Rectangle::Rectangle(float w, float h, Orientation orien) :
    width(w), height(h), orientation(orien) {
    Initialize();
}

void Rectangle::GenerateVertices() {
    float w = width / 2.0f;
    float h = height / 2.0f;

    switch (orientation) {
        case Orientation::POS_X:
            vertices = {
                Vertex { { 0.0f,  h,  w }, { 1.0, 0.0, 0.0 } },
                Vertex { { 0.0f, -h,  w }, { 1.0, 0.0, 0.0 } },
                Vertex { { 0.0f, -h, -w }, { 1.0, 0.0, 0.0 } },
                Vertex { { 0.0f,  h, -w }, { 1.0, 0.0, 0.0 } },
            };
            break;

        case Orientation::POS_Y:
            vertices = {
                Vertex { { -w, 0.0f, -h }, { 0.0, 1.0, 0.0 } },
                Vertex { { -w, 0.0f,  h }, { 0.0, 1.0, 0.0 } },
                Vertex { {  w, 0.0f,  h }, { 0.0, 1.0, 0.0 } },
                Vertex { {  w, 0.0f, -h }, { 0.0, 1.0, 0.0 } },
            };
            break;

        case Orientation::POS_Z:
            vertices = {
                Vertex { { -w, -h, 0.0f }, { 0.0, 0.0, 1.0 } },
                Vertex { {  w, -h, 0.0f }, { 0.0, 0.0, 1.0 } },
                Vertex { {  w,  h, 0.0f }, { 0.0, 0.0, 1.0 } },
                Vertex { { -w,  h, 0.0f }, { 0.0, 0.0, 1.0 } },
            };
            break;
    }

    indices = {
        0, 1, 2,
        0, 2, 3,
    };
}