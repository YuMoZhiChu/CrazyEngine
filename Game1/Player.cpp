#include "Player.h"

#include <SDL.h>
#include <Engine\InputManager.h>
#include <Engine\Window.h>

void Player::inputCheck()
{
	if (InputManager::getInpuManager()->isKeyDown(SDLK_a)) {
		GameObject::move(GameObject::getXaxis() * Engine::Window::getWindow()->getDeltaTime());
		if (GameObject::getTempRotation().y < 20) {
			GameObject::setTempRotation(GameObject::getYaxis(), 90.0f * Engine::Window::getWindow()->getDeltaTime());
		}
	}
	else {
		if (InputManager::getInpuManager()->isKeyDown(SDLK_d)) {
			GameObject::move(-1.0f * GameObject::getXaxis() * Engine::Window::getWindow()->getDeltaTime());
			if (GameObject::getTempRotation().y > -20) {
				GameObject::setTempRotation(GameObject::getYaxis(), -90.0f * Engine::Window::getWindow()->getDeltaTime());
			}		
		}
		else {
			GameObject::resetTempRotation();
		}
	}

	if (InputManager::getInpuManager()->isKeyPressed(SDL_BUTTON_LEFT)) {
		Engine::PoolObject<GameObject>* bullet = m_Bullets.getElement();
		if (bullet != nullptr) {
			bullet->getElement()->enableGameObject();
			bullet->getElement()->setPosition(GameObject::getPosition());
			m_ActiveBullets.push_back(bullet);
		}
	}
}


Player::Player(Texture* texture) : GameObject(texture)
{
}


Player::~Player()
{
}

void Player::init(Engine::GLSLProgram* shader, int nBullets)
{	
	GameObject::initMesh(shader, "meshes/dark_fighter_6.obj");
	GameObject::setScale(glm::vec3(0.02f, 0.02f, 0.02f));
	GameObject::setRotation(glm::vec3(0.0f, 0.0f, 1.0f), 45);
	
	for (int i = 0; i < nBullets; i++) {
		GameObject* newBullet = new GameObject(TextureCache::getTextureCache()->getTexture("textures/ronnie.jpg"), 
												GameObjectState::CUBE);
		newBullet->initCube(shader);
		newBullet->setScale(glm::vec3(0.02f, 0.02f, 0.02f));
		newBullet->disableGameObject();
		m_Bullets.addElement(newBullet);
	}
}

void Player::update()
{
	inputCheck();
	updateBullets();
}

void Player::updateBullets()
{
	for (int i =0 ; i < m_ActiveBullets.size(); i++)
	{
		m_ActiveBullets[i]->getElement()->move(- GameObject::getYaxis() * Engine::Window::getWindow()->getDeltaTime());
		glm::vec3 position = m_ActiveBullets[i]->getElement()->getPosition();
		if (position.y <= -5)
		{
			m_ActiveBullets[i]->getElement()->disableGameObject();
			m_Bullets.returnElement(m_ActiveBullets[i]);
			m_ActiveBullets[i] = m_ActiveBullets.back();
			m_ActiveBullets.pop_back();
		}
	}
}


