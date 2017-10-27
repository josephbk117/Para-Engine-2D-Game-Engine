#include <iostream>
#include <Game.h>
#include <GLM\glm.hpp>
#include <fstream>
#include "PlayerMagicController.h"
#include "MagicObjectScaler.h"
#include "ObjectSpawner.h"
#include "SuddenJolt.h"
#include <SceneManager.h>

int main(int argc, char* argv[])
{
	Game game(600, 600, "2D Game Engine");

	unsigned int texVal1 = TextureLoader::loadTextureFromFile("Test Resources\\frasa.png", false);
	unsigned int texVal2 = TextureLoader::loadTextureFromFile("Test Resources\\mamma.png", false);
	unsigned int texVal3 = TextureLoader::loadTextureFromFile("Test Resources\\lili.jpg", false);
	GameObject* tempGameObject;

	tempGameObject = GameObject::createGameObject("Camera");
	tempGameObject->addComponent(new Transform(glm::vec2(0, 0), 0.0f, glm::vec2(1, 1)));
	Camera* camera = new Camera;
	camera->init(glm::vec2(500, 500));
	tempGameObject->addComponent(camera);
	tempGameObject->addComponent(new PlayerMagicController);

	tempGameObject = GameObject::createGameObject("BG");
	tempGameObject->addComponent(new Transform(glm::vec2(0, 0), 0.0f, glm::vec2(1, 1)));
	tempGameObject->setLayerOrder(-10);
	Sprite * tempSprite = new Sprite();
	tempSprite->init(600, 600);
	tempSprite->setTextureID(texVal3);
	tempGameObject->addComponent(tempSprite);
	tempGameObject->addComponent(new ObjectSpawner);

	tempGameObject = GameObject::createGameObject("Sammy");
	tempGameObject->addComponent(new Transform(glm::vec2(0, 0), 0.0f, glm::vec2(1, 1)));
	tempGameObject->setLayerOrder(50);
	tempSprite = new Sprite();
	tempSprite->init(50, 50);
	tempSprite->setTextureID(texVal1);
	tempGameObject->addComponent(tempSprite);
	tempGameObject->addComponent(new MagicObjectScaler);

	tempGameObject = GameObject::createGameObject("Lola");
	tempGameObject->setLayerOrder(10);
	tempGameObject->addComponent(new Transform(glm::vec2(-50, -100), 0.0f, glm::vec2(1, 1)));
	tempSprite = new Sprite();
	tempSprite->init(80, 80);
	tempSprite->setTextureID(texVal1);
	tempGameObject->addComponent(tempSprite);
	//tempGameObject->addComponent(new PlayerMagicController());

	tempGameObject = GameObject::createGameObject("Babu");
	tempGameObject->addComponent(new Transform(glm::vec2(-120, -100), 0.0f, glm::vec2(1, 1)));
	tempSprite = new Sprite();
	tempSprite->init(80, 80);
	tempSprite->setTextureID(texVal1);
	tempGameObject->addComponent(tempSprite);
	BoxCollider* boxCollider = new BoxCollider();
	boxCollider->init(tempGameObject->getComponent<Transform>()->position, glm::vec2(80, 80), PhysicsBody::DYNAMIC, 1.0f);
	tempGameObject->addComponent(boxCollider);
	tempGameObject->addComponent(new SuddenJolt);

	tempGameObject = GameObject::createGameObject("Galoo");
	tempGameObject->addComponent(new Transform(glm::vec2(-120, -250), 0.0f, glm::vec2(1, 1)));
	tempGameObject->setLayerOrder(20);
	tempSprite = new Sprite();
	tempSprite->init(300, 50);
	tempSprite->setTextureID(texVal2);
	tempGameObject->addComponent(tempSprite);
	boxCollider = new BoxCollider();
	boxCollider->init(tempGameObject->getComponent<Transform>()->position,
		glm::vec2(300, 50), PhysicsBody::STATIC, 1.0f);
	tempGameObject->addComponent(boxCollider);

	SceneManager::SaveSceneData(GameObject::getAllGameObjects(), "s");

	game.initialize();
	game.update();

	return 0;
}
