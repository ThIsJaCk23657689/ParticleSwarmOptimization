#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <glad/glad.h>

#include <vector>

#include "Model/Vertex.hpp"

constexpr float PI = 3.14159265359f;

enum Attributes : int {
    Position = 0
};

struct Geometry {
    GLuint vao, vbo, ebo;
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

    Geometry() = default;
    ~Geometry();

    void Initialize();
    void UpdateVertices();
    void Draw();

protected:
    virtual void GenerateVertices() = 0;
    virtual void BufferInitialize();
    void Clear();
};

#endif
