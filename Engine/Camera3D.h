#pragma once

#include <glm.hpp>

#include "GLSLProgram.h"

class Camera3D
{
    glm::vec3 m_Position;
    float m_ScreenWidth;
    float m_ScreenHeight;
    bool m_NeedUpdate;

    glm::mat4 m_CameraMatrix;

public:
    
    void setPosition(glm::vec3 position) {
        m_Position = position;
        m_NeedUpdate = true;
    }

    const glm::mat4& getCameraMatrix() const {
        return m_CameraMatrix;
    }
    
    Camera3D(glm::vec3 position, float screenWidth, float screenHeight);
    ~Camera3D();

    void update(CrazyEngine::GLSLProgram* shaderProgram);

};

