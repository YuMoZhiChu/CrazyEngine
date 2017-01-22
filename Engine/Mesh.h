#pragma once

#include <vector>
#include <glm.hpp>
#include "GLSLProgram.h"
#include "TextureCache.h"
#include "Texture.h"

struct VertexMesh {
    glm::vec3 pos;
    glm::vec3 norm;
    glm::vec2 uv;
};

struct Triangle {
    int i, j, k;
    Triangle(int _i, int _j, int _k) :i(_i), j(_j), k(_k) {}
};

class Mesh
{
    std::vector<VertexMesh> m_Vertices;
    std::vector<Triangle> m_Triangles;

    GLuint m_VBO; //Vertex Buffer Object
    GLuint m_VAO; //Vertex Array Object
    GLuint m_EBO; //Element array

    Texture* m_Texture;

    int m_nElements;

public:
    Mesh();
    Mesh(const std::string& texturePath);
    Mesh(Texture* texture);
    ~Mesh();

    bool loadMesh(char* path);

    void loadGPUMesh(CrazyEngine::GLSLProgram* shaderProgram);

    void drawMesh();

    bool loadTexture(const std::string& texturePath);
};

