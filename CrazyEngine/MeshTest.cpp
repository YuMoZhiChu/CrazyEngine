#include "MeshTest.h"

#include <gtc/type_ptr.hpp>

MeshTest::MeshTest()
{
    m_ShaderProgram = new CrazyEngine::GLSLProgram;
    m_Camera = new Camera3D(glm::vec3(1.2, 30.2, 1.2), 800, 600);
    m_TextureCache = new TextureCache;
    m_Mesh = new Mesh(m_TextureCache->getTexture("textures/dark_fighter_color.pbm", PBM));
    //m_Mesh = new Mesh(m_TextureCache->getTexture("textures/ronnie.jpg"));
}


MeshTest::~MeshTest()
{
}

void MeshTest::Init()
{
    CompileShaders();

    if (m_Mesh->loadMesh("meshes/dark_fighter_6.obj")) {
        m_Mesh->loadGPUMesh(m_ShaderProgram);
    }
}

void MeshTest::draw()
{
    m_ShaderProgram->use();
    m_Camera->update(m_ShaderProgram);
    updateUniformVariables();
    m_Mesh->drawMesh();
}


void MeshTest::CompileShaders()
{
    m_ShaderProgram->compileShaders("Shaders/MeshCamera3D.vert", "Shaders/MeshCamera3D.frag");
    m_ShaderProgram->linkShader();
}

void MeshTest::updateUniformVariables() {

    GLint uniCamMatrix = m_ShaderProgram->getUniformLocation("cameraMatrix");
    // The second parameter of the glUniformMatrix4fv function specifies how many matrices are to be uploaded, 
    // because you can have arrays of matrices in GLSL.
    // The third parameter specifies whether the specified matrix should be transposed before usage.
    // The last parameter specifies the matrix to upload, 
    // where the glm::value_ptr function converts the matrix class into an array of 16 (4x4) floats.
    glUniformMatrix4fv(uniCamMatrix, 1, GL_FALSE, glm::value_ptr(m_Camera->getCameraMatrix()));
}