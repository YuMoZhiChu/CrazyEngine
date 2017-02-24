
#include "GOmanager.h"
#include <gtc/type_ptr.hpp>
#include "GameObject.h"

GOmanager* GOmanager::m_GOmanager = nullptr;

GOmanager::GOmanager() : m_nGameObjects(0)
{
}


GOmanager::~GOmanager()
{
}

int GOmanager::addGameObject(GameObject* gameObject)
{
	m_GameObjects[m_nGameObjects] = gameObject;
	m_ModelMatrices.push_back(glm::mat4());
	m_nGameObjects++;
	return m_nGameObjects - 1;
}



void GOmanager::drawGameObject(Engine::GLSLProgram* shader) {

	int i = m_GameObjects.size();

	for each (auto object in m_GameObjects)
	{
		m_ModelMatrices[object.first] = object.second->updateModelMatrix();
	}

	//The second parameter of the glUniformMatrix4fv function specifies how many matrices are to be uploaded, 
	//because you can have arrays of matrices in GLSL.
	//The third parameter specifies whether the specified matrix should be transposed before usage.
	//The last parameter specifies the matrix to upload, 
	//where the glm::value_ptr function converts the matrix class into an array of 16 (4x4) floats.
	glUniformMatrix4fv(shader->getUniformLocation("modelMatrix"), m_GameObjects.size(), GL_FALSE, glm::value_ptr(m_ModelMatrices[0]));

	for each (auto object in m_GameObjects)
	{
		if (object.second->getState())
		object.second->draw(shader);
	}
}
