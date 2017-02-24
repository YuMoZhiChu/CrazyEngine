#pragma once

#include <glm.hpp>
#include <vector>
#include <map>

#include "GLSLProgram.h"

class GameObject;

class GOmanager
{
	static GOmanager* m_GOmanager;

	std::map<int, GameObject*> m_GameObjects;
	std::vector<glm::mat4> m_ModelMatrices;
	int m_nGameObjects;

	GOmanager();

public:
	~GOmanager();

	static GOmanager* getManager() {
		if (m_GOmanager == nullptr) {
			m_GOmanager = new GOmanager;
		}
		return m_GOmanager;
	}

	int addGameObject(GameObject* gameObject);

	void drawGameObject(Engine::GLSLProgram* shader);
};

