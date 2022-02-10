#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <glad/glad.h>
#include <vector>

#include "Geometry/Geometry.hpp"

struct Triangle : public Geometry {
    Triangle();

protected:
    void GenerateVertices() override;
};

#endif
