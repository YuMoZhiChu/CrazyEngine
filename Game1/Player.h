#pragma once

#include <Engine\GameObject.h>
#include <Engine\Pool.h>
#include <Engine\Cube.h>

class Player : public GameObject
{
	CrazyEngine::GLSLProgram* m_ShaderProgram;
	Engine::Pool<Cube> m_Bullets;

	void inputCheck();

public:
	Player(Texture* texture);
	~Player();

	void init(CrazyEngine::GLSLProgram* shader, int nBullets);

	void update();

	void draw();
};

