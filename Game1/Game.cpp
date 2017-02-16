#include "Game.h"

#include <gtc/type_ptr.hpp>


Game::Game()
{
	m_Camera = new Camera3D(glm::vec3(2.2, 2.2, 1.5), 800, 600);
	m_Player = new Player(TextureCache::getTextureCache()->getTexture("textures/dark_fighter_color.pbm", PBM));
}


Game::~Game()
{
	for each (auto var in m_ShaderPrograms)
	{
		delete var;
	}
	delete m_Camera;
	delete m_Player;
}

void Game::init()
{
	CompileShaders();
	m_Player->init(m_ShaderPrograms[0], 10);
}

void Game::update()
{
	m_Player->update();
	draw();
}

void Game::draw()
{
	m_Camera->update();
	updateUniformVariables();
	m_Player->draw();
}

void Game::CompileShaders()
{
	CrazyEngine::GLSLProgram* newShader = new CrazyEngine::GLSLProgram;
	newShader->compileShaders("Shaders/MeshCamera3D.vert", "Shaders/MeshCamera3D.frag");
	newShader->linkShader();
	m_ShaderPrograms.push_back(newShader);
}

void Game::updateUniformVariables()
{
	for each (auto shader in m_ShaderPrograms)
	{
		GLint uniCamMatrix = shader->getUniformLocation("cameraMatrix");
		if (uniCamMatrix != GL_INVALID_INDEX) {
			// The second parameter of the glUniformMatrix4fv function specifies how many matrices are to be uploaded, 
			// because you can have arrays of matrices in GLSL.
			// The third parameter specifies whether the specified matrix should be transposed before usage.
			// The last parameter specifies the matrix to upload, 
			// where the glm::value_ptr function converts the matrix class into an array of 16 (4x4) floats.
			glUniformMatrix4fv(uniCamMatrix, 1, GL_FALSE, glm::value_ptr(m_Camera->getCameraMatrix()));
		}
	}
}
