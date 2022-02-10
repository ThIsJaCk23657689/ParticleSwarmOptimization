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
                Vertex { { 0.0f,  h,  w } },
                Vertex { { 0.0f, -h,  w } },
                Vertex { { 0.0f, -h, -w } },
                Vertex { { 0.0f,  h, -w } },
            };
            break;

        case Orientation::POS_Y:
            vertices = {
                Vertex { { -w, 0.0f, -h } },
                Vertex { { -w, 0.0f,  h } },
                Vertex { {  w, 0.0f,  h } },
                Vertex { {  w, 0.0f, -h } },
            };
            break;

        case Orientation::POS_Z:
            vertices = {
                Vertex { { -w, -h, 0.0f } },
                Vertex { {  w, -h, 0.0f } },
                Vertex { {  w,  h, 0.0f } },
                Vertex { { -w,  h, 0.0f } },
            };
            break;
    }

    indices = {
        0, 1, 2,
        0, 2, 3,
    };
}