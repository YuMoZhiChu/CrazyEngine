#pragma once

#include <Engine\GLSLProgram.h>
#include <Engine\Camera3D.h>
#include <Engine\Mesh.h>
#include <Engine\TextureCache.h>
#include <Engine\Window.h>
#include <Engine\Cube.h>

#include "Player.h"

class Game
{
	std::vector<CrazyEngine::GLSLProgram*> m_ShaderPrograms;
	Camera3D* m_Camera;
	Player* m_Player;

	void draw();
	void CompileShaders();
	void updateUniformVariables();

public:
	Game();
	~Game();

	void init();

	void update();

};

