#pragma once

#include "Test.h"
#include <Engine\GLSLProgram.h>
#include <Engine\Camera3D.h>
#include <Engine\Mesh.h>
#include <Engine\TextureCache.h>

class MeshTest : public Test
{
    CrazyEngine::GLSLProgram* m_ShaderProgram;
    Camera3D* m_Camera;
    Mesh* m_Mesh;
    TextureCache* m_TextureCache;

public:
    MeshTest();
    ~MeshTest();

    virtual void Init();
    virtual void draw();

    void CompileShaders();

    void MeshTest::updateUniformVariables();
};

