#ifndef CORNFIELD_HPP
#define CORNFIELD_HPP

#include "Geometry/Geometry.hpp"

struct Cornfield : public Geometry {
    Cornfield();

protected:
    void GenerateVertices() override;
};

#endif
