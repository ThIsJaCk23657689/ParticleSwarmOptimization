#include "Geometry/3D/Sphere.hpp"

Sphere::Sphere(const float r, const int slices, const int stacks) :
    radius(r), longitude(slices), latitude(stacks) {
    Initialize();
}

void Sphere::GenerateVertices() {

    for (unsigned int i = 0; i <= latitude; ++i) {
        float theta = i * PI / latitude;
        float sinTheta = sin(theta);
        float cosTheta = cos(theta);
        for (unsigned int j = 0; j <= longitude; ++j) {
            float phi = j * 2.0f * PI / longitude;
            float sinPhi = sin(phi);
            float cosPhi = cos(phi);

            // vertices order must follow counter-clockwise rules.
            float x = sinPhi * sinTheta;
            float y = cosTheta;
            float z = cosPhi * sinTheta;

            vertices.push_back(Vertex{
                    {radius * x, radius * y, radius * z},
                    {x, y, z}
            });

            // texture coordinate (u, v) range between [0, 1]
            // float u = j / static_cast<float>(longitude);
            // float v = i / static_cast<float>(latitude);
            // AddTexCoord(u, v);
        }
    }

    for (unsigned int i = 0; i < latitude; ++i) {
        for (unsigned int j = 0; j < longitude; ++j) {
            int first = i * (longitude + 1) + j;
            int second = first + longitude + 1;

            // counter-clockwise
            indices.push_back(first);
            indices.push_back(second);
            indices.push_back(first + 1);

            indices.push_back(first + 1);
            indices.push_back(second);
            indices.push_back(second + 1);
        }
    }
}