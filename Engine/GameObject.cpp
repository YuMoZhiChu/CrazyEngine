#include "GameObject.h"

#include <gtc/matrix_transform.hpp>
#include <gtx/rotate_vector.hpp>
#include <gtc/type_ptr.hpp>

GameObject::GameObject(Texture* texture) :
	m_ModelMatrixNeedUpdate(false)
{
	m_Mesh = new Mesh(texture);
}

void GameObject::initMesh(CrazyEngine::GLSLProgram * shader, const std::string & meshPath)
{
	if (m_Mesh->loadMesh(&meshPath[0])) {
		m_Mesh->loadGPUMesh(shader);
	}
}

void GameObject::draw(CrazyEngine::GLSLProgram* shader)
{
	updateModelMatrix(shader);
	m_Mesh->drawMesh();
}

GameObject::~GameObject()
{
	delete m_Mesh;
}

void GameObject::updateModelMatrix(CrazyEngine::GLSLProgram* shader)
{
	if (m_ModelMatrixNeedUpdate) {
		glm::mat4 newModelMatrix;
			
		if (m_TempModelMatrixNeedUpdate || m_TempRotation != glm::vec3()) {
			m_TempModelMatrix = m_TranslationMatrix * m_TempRotationMatrix * m_RotationMatrix * m_ScaleMatrix;
			newModelMatrix = m_TempModelMatrix;
			m_TempModelMatrixNeedUpdate = false;
		}
		else
		{
			m_ModelMatrix = m_TranslationMatrix * m_RotationMatrix * m_ScaleMatrix;
			newModelMatrix = m_ModelMatrix;
		}

		GLint uniRotMatrix = shader->getUniformLocation("modelMatrix");
		// The second parameter of the glUniformMatrix4fv function specifies how many matrices are to be uploaded, 
		// because you can have arrays of matrices in GLSL.
		// The third parameter specifies whether the specified matrix should be transposed before usage.
		// The last parameter specifies the matrix to upload, 
		// where the glm::value_ptr function converts the matrix class into an array of 16 (4x4) floats.
		glUniformMatrix4fv(uniRotMatrix, 1, GL_FALSE, glm::value_ptr(newModelMatrix));
		m_ModelMatrixNeedUpdate = false;
	}	
}

void GameObject::setPosition(glm::vec3 position)
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
	m_TempModelMatrixNeedUpdate = true;
}


