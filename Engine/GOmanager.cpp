
#include "GOmanager.h"
#include <gtc/type_ptr.hpp>
#include "GameObject.h"

GOmanager* GOmanager::m_GOmanager = nullptr;

GOmanager::GOmanager()
{
}


GOmanager::~GOmanager()
{
}

int GOmanager::addGameObject(GameObject* gameObject)
{
	m_GameObjects.push_back(gameObject);
	m_ModelMatrices.push_back(glm::mat4());
	return m_nGameObjectsCreated++;
}

void GOmanager::removeGameObject(GameObject* gameObject){
	m_GameObjects.back()->setID(gameObject->getID());
	m_GameObjects[gameObject->getID()] = m_GameObjects.back();
	m_GameObjects.pop_back();
	m_ModelMatrices[gameObject->getID()] = m_ModelMatrices.back();
	m_ModelMatrices.pop_back();
	m_nGameObjectsCreated--;
}

void GOmanager::drawGameObjects(Engine::GLSLProgram* shader) {

	for(int i=0 ; i < m_GameObjects.size(); i++)
	{
		m_ModelMatrices[i] = m_GameObjects[i]->updateModelMatrix();
	}

	//The second parameter of the glUniformMatrix4fv function specifies how many matrices are to be uploaded, 
	//because you can have arrays of matrices in GLSL.
	//The third parameter specifies whether the specified matrix should be transposed before usage.
	//The last parameter specifies the matrix to upload, 
	//where the glm::value_ptr function converts the matrix class into an array of 16 (4x4) floats.
	glUniformMatrix4fv(shader->getUniformLocation("modelMatrix"), m_GameObjects.size(), GL_FALSE, glm::value_ptr(m_ModelMatrices[0]));

	for (int i=0 ; i < m_GameObjects.size(); i++)
	{
		if (m_GameObjects[i]->getState()) {
			glUniform1i(shader->getUniformLocation("ID"), i);
			m_GameObjects[i]->draw(shader);
		}
	}
}
