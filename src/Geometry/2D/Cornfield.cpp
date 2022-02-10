#include "Geometry/2D/Cornfield.hpp"

//#include <iostream>

Cornfield::Cornfield() {
    Initialize();
}

Cornfield::Cornfield(float len, unsigned int smpl_rt) : length(len), sample_rate(smpl_rt) {
    Initialize();
}

void Cornfield::GenerateVertices() {

    float start = 0;
    float end = start + length;

    for (int i = start; i < end; ++i) {
        for (int j = start; j < end; ++j) {
            float eval_y = EvaluateScore(j, i);
            vertices.push_back(Vertex{static_cast<float>(j), eval_y, static_cast<float>(i)});
        }
    }

    for (int i = 0; i < 0 + length - 1; ++i) {
        for (int j = 0; j < 0 + length - 1; ++j) {
            float v1 = j + (length * i);
            indices.push_back(v1);
            indices.push_back(v1 + length);
            indices.push_back(v1 + length + 1);
            indices.push_back(v1);
            indices.push_back(v1 + length + 1);
            indices.push_back(v1 + 1);
        }
    }

//    std::cout << "vertices: " << vertices.size() << std::endl;
//    std::cout << "indices: " << indices.size() << std::endl;
}

float Cornfield::EvaluateScore(float x, float z) {
    return static_cast<float>(sqrt(pow((x - 100), 2) + pow((z - 100), 2)));
}