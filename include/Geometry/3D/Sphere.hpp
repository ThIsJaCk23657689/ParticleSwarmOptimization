#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <glad/glad.h>
#include <vector>

#include "Geometry/Geometry.hpp"

struct Sphere : public Geometry {
    Sphere(const float r = 1.0f, const int slices = 30, const int stacks = 30);

protected:
    void GenerateVertices() override;

    float radius;
    unsigned int longitude;
    unsigned int latitude;
};

#endif