#include "Player.h"

#include <SDL.h>
#include <Engine\InputManager.h>
#include <Engine\Window.h>

void Player::inputCheck()
{
	if (InputManager::getInpuManager()->isKeyDown(SDLK_a)) {
		GameObject::setPosition(GameObject::getXaxis() * CrazyEngine::Window::getWindow()->getDeltaTime());
		if (GameObject::getTempRotation().y < 20) {
			GameObject::setTempRotation(GameObject::getYaxis(), 90.0f * CrazyEngine::Window::getWindow()->getDeltaTime());
		}
	}
	else {
		if (InputManager::getInpuManager()->isKeyDown(SDLK_d)) {
			GameObject::setPosition(-1.0f * GameObject::getXaxis() * CrazyEngine::Window::getWindow()->getDeltaTime());
			if (GameObject::getTempRotation().y > -20) {
				GameObject::setTempRotation(GameObject::getYaxis(), -90.0f * CrazyEngine::Window::getWindow()->getDeltaTime());
			}		
		}
		else {
			GameObject::resetTempRotation();
		}
	}
}

Player::Player(Texture* texture) : GameObject(texture)
{
}


Player::~Player()
{
}

void Player::init(CrazyEngine::GLSLProgram* shader, int nBullets)
{	
	GameObject::initMesh(shader, "meshes/dark_fighter_6.obj");
	GameObject::setScale(glm::vec3(0.02f, 0.02f, 0.02f));
	GameObject::setRotation(glm::vec3(0.0f, 0.0f, 1.0f), 45);
	m_ShaderProgram = shader;

	for (int i = 0; i < nBullets; i++) {
		Cube* newBullet = new Cube(nullptr);
		newBullet->Init(m_ShaderProgram);
	}
}

void Player::update()
{
	inputCheck();
}

void Player::draw()
{
	m_ShaderProgram->use();
	GameObject::draw(m_ShaderProgram);
}
