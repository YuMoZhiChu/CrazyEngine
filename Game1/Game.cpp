#include "Game.h"

#include <gtc/type_ptr.hpp>

#include <Engine\GOmanager.h>

Game::Game()
{
	m_CameraShader = new Engine::GLSLProgram;
	m_Camera = new Camera3D(glm::vec3(2.2, 2.2, 1.5), 800, 600);
	m_Player = new Player(TextureCache::getTextureCache()->getTexture("textures/dark_fighter_color.pbm", PBM));
}


Game::~Game()
{
	delete m_CameraShader;
	delete m_Camera;
	delete m_Player;
}

void Game::init()
{
	CompileShaders();
	m_Player->init(m_CameraShader, 10);
}

void Game::update()
{
	m_Player->update();
	draw();
}

void Game::draw()
{
	m_CameraShader->use();
	m_Camera->update();
	updateUniformVariables();
	GOmanager::getManager()->drawGameObject(m_CameraShader);
}

void Game::CompileShaders()
{
	m_CameraShader->compileShaders("Shaders/MeshCamera3D.vert", "Shaders/MeshCamera3D.frag");
	m_CameraShader->linkShader();
}

void Game::updateUniformVariables()
{
	GLint uniCamMatrix = m_CameraShader->getUniformLocation("cameraMatrix");
	if (uniCamMatrix != GL_INVALID_INDEX) {
		// The second parameter of the glUniformMatrix4fv function specifies how many matrices are to be uploaded, 
		// because you can have arrays of matrices in GLSL.
		// The third parameter specifies whether the specified matrix should be transposed before usage.
		// The last parameter specifies the matrix to upload, 
		// where the glm::value_ptr function converts the matrix class into an array of 16 (4x4) floats.
		glUniformMatrix4fv(uniCamMatrix, 1, GL_FALSE, glm::value_ptr(m_Camera->getCameraMatrix()));
	}
}
