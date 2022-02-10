#ifndef CORNFIELD_HPP
#define CORNFIELD_HPP

#include "Geometry/Geometry.hpp"

struct Cornfield : public Geometry {
    Cornfield();
    Cornfield(float len, unsigned int smpl_rt);

protected:
    void GenerateVertices() override;

private:
    float length = 200.0f;
    unsigned int sample_rate = 100;

    float EvaluateScore(float x, float z);
};

#endif
