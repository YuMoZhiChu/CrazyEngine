#include "GameObject.h"

#include <gtc/matrix_transform.hpp>
#include <gtx/rotate_vector.hpp>
#include <gtc/type_ptr.hpp>

#include "GOmanager.h"

GameObject::GameObject(Texture* texture, GameObjectState state) :
	m_ModelMatrixNeedUpdate(false),
	m_State(true)
{
	if (state == CUBE) {
		m_Cube = new Cube(texture);
	}
	else {
		m_Mesh = new Mesh(texture);
	}
	m_ID = GOmanager::getManager()->addGameObject(this);
}

void GameObject::initMesh(Engine::GLSLProgram * shader, const std::string &meshPath)
{
	if (m_Mesh->loadMesh(&meshPath[0])) {
		m_Mesh->loadGPUMesh(shader);
	}
}

void GameObject::initCube(Engine::GLSLProgram * shader)
{
	m_Cube->Init(shader);
}

void GameObject::draw(Engine::GLSLProgram* shader)
{
	glUniform1i(shader->getUniformLocation("ID"), m_ID);
	if (m_Mesh != nullptr) {
		m_Mesh->drawMesh();
	}
	else {
		m_Cube->draw();
	}
}

GameObject::~GameObject()
{
	delete m_Mesh;
}

glm::mat4 GameObject::updateModelMatrix()
{
	if (m_ModelMatrixNeedUpdate) {

		if (m_TempRotation != glm::vec3()) {
			m_ModelMatrix = m_TranslationMatrix * m_TempRotationMatrix * m_RotationMatrix * m_ScaleMatrix;
		}
		else
		{
			m_ModelMatrix = m_TranslationMatrix * m_RotationMatrix * m_ScaleMatrix;
		}
		m_ModelMatrixNeedUpdate = false;
	}	
	return m_ModelMatrix;
}

void GameObject::setPosition(glm::vec3 position)
{	
	m_Position = position;
	m_TranslationMatrix = glm::translate(glm::mat4(), position);
	m_ModelMatrixNeedUpdate = true;
}

void GameObject::move(glm::vec3 position)
{
	m_Position += position;
	m_TranslationMatrix = glm::translate(m_TranslationMatrix, position);
	m_ModelMatrixNeedUpdate = true;
}

void GameObject::setRotation(glm::vec3 axis, float rotation)
{
	m_Rotation += axis * rotation;
	m_RotationMatrix = glm::rotate(m_RotationMatrix, glm::radians(rotation), axis);
	m_ModelMatrixNeedUpdate = true;
}

void GameObject::setScale(glm::vec3 scale)
{
	m_Scale += scale;
	m_ScaleMatrix = glm::scale(m_ScaleMatrix, scale);
	m_ModelMatrixNeedUpdate = true;
}

void GameObject::setTempRotation(glm::vec3 axis, float rotation)
{
	m_TempRotation += axis * rotation;
	m_TempRotationMatrix = glm::rotate(m_TempRotationMatrix, glm::radians(rotation), axis);
	m_ModelMatrixNeedUpdate = true;
}


