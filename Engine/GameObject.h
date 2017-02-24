#pragma once

#include "Mesh.h"
#include "Texture.h"
#include "GLSLProgram.h"
#include "Cube.h"

#include <glm.hpp>
 
enum GameObjectState {
	CUBE, MESH
};

class GameObject
{
	int m_ID;

	Mesh* m_Mesh;

	Cube* m_Cube;

	glm::mat4 m_ModelMatrix;
	glm::mat4 m_TranslationMatrix;
	glm::mat4 m_RotationMatrix;
	glm::mat4 m_ScaleMatrix;

	glm::mat4 m_TempRotationMatrix;

	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	glm::vec3 m_Scale;
	glm::vec3 m_TempRotation;

	bool m_ModelMatrixNeedUpdate;

	bool m_State;

public:

	void setPosition(glm::vec3 position);
	void move(glm::vec3 position);
	void setRotation(glm::vec3 axis, float rotation);
	void setScale(glm::vec3 scale);

	void setTempRotation(glm::vec3 axis, float rotation);

	glm::vec3 getPosition() {
		//return glm::vec4(m_Position, 0.0) * glm::inverse(m_ModelMatrix);
		return m_Position;
	}

	glm::mat4 getRotationMatrix() {
		return m_RotationMatrix;
	}

	glm::vec3 getRotation() {
		glm::vec3 rotation(glm::vec3(int(m_Rotation.x) % 360, (int)m_Rotation.y % 360, (int)m_Rotation.z % 360));
		return rotation;
	}

	glm::vec3 getXaxis() {
		glm::vec4 xAxis = glm::vec4(1.0, 0.0, 0.0, 0.0) * m_RotationMatrix;
		return glm::vec3 (xAxis.x, xAxis.y, xAxis.z);
	}

	glm::vec3 getYaxis() {
		glm::vec4 yAxis = glm::vec4(0.0, 1.0, 0.0, 0.0) * m_RotationMatrix;
		return glm::vec3(yAxis.x, yAxis.y, yAxis.z);
	}

	glm::vec3 getZaxis() {
		glm::vec4 zAxis = glm::vec4(0.0, 0.0, 1.0, 0.0) * m_RotationMatrix;
		return glm::vec3(zAxis.x, zAxis.y, zAxis.z);
	}

	glm::vec3 getTempRotation() {
		glm::vec3 rotation(glm::vec3(int(m_TempRotation.x) % 360, (int)m_TempRotation.y % 360, (int)m_TempRotation.z % 360));
		return rotation;
	}

	void resetTempRotation() {
		if (m_TempRotation != glm::vec3()) {
			m_TempRotation = glm::vec3();
			m_TempRotationMatrix = glm::mat4();
			m_ModelMatrixNeedUpdate = true;
		}
	}

	void initMesh(Engine::GLSLProgram* shader, const std::string& meshPath);
	
	void initCube(Engine::GLSLProgram* shader);

	glm::mat4 updateModelMatrix();

	void draw(Engine::GLSLProgram* shader);

	void enableGameObject() {
		m_State = true;
	}

	void disableGameObject() {
		m_State = false;
	}

	bool getState() {
		return m_State;
	}

	GameObject(Texture* texture, GameObjectState state = MESH);
	~GameObject();
};

