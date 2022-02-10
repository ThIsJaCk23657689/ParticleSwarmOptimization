#include "Geometry/2D/Cornfield.hpp"

#include <glm/glm.hpp>
#include <cmath>
//#include <iostream>

Cornfield::Cornfield() {
    Initialize();
}

Cornfield::Cornfield(float len, unsigned int smpl_rt) : length(len), sample_rate(smpl_rt) {
    Initialize();
}

void Cornfield::GenerateVertices() {
    // TODO: 加入 sample rate

    float start = -100;
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
    // TODO: 可以嘗試做好幾種模式，比如布林噪音、或是其他最佳化曲面

    // 論文提供的公式，最小值的位置為 (0, 0)。
    // return static_cast<float>(sqrt(pow((x - 0), 2)) + sqrt(pow((z - 0), 2)));

    // 歐基里德距離公式，看起來會很圓滑，最小值的位置為 (0, 0)。
    return static_cast<float>(sqrt(pow((x - 0), 2) + pow((z - 0), 2)));

    // Schaffer's F6
    // return static_cast<float>(0.5 + (pow(glm::sin(sqrt(pow(x, 2) + pow(z, 2))), 2) - 0.5) / pow((1 + 0.001 * (pow(x, 2) + pow(z, 2))), 2) );
}