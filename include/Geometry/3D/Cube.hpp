#ifndef CUBE_HPP
#define CUBE_HPP

#include <glad/glad.h>
#include <vector>

#include "Geometry/Geometry.hpp"

struct Cube : public Geometry {
    Cube();

protected:
    void GenerateVertices() override;
};
#endif
