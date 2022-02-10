#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "Geometry/Geometry.hpp"

// Adjust the orientation of normal which this rectangle has. POS means "Positive".
enum Orientation : unsigned int {
    POS_X = 0,
    POS_Y = 1,
    POS_Z = 2,
};

struct Rectangle : public Geometry {
    Rectangle();
    Rectangle(float w, float h, Orientation orien = Orientation::POS_Z);

protected:
    void GenerateVertices() override;

private:
    float width = 1.0f;
    float height = 1.0f;
    Orientation orientation = Orientation::POS_Z;
};

#endif