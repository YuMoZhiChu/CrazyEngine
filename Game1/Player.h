#pragma once

#include <Engine\GameObject.h>
#include <Engine\Pool.h>
#include <Engine\Cube.h>

class Player : public GameObject
{
	Engine::Pool<GameObject> m_Bullets;

	std::vector<Engine::PoolObject<GameObject>*> m_ActiveBullets;

	void inputCheck();

	void updateBullets();

public:
	Player(Texture* texture);
	~Player();

	void init(Engine::GLSLProgram* shader, int nBullets);

	void update();
};

