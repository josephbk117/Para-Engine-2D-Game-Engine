#include <Game.h>
#include <GLM\glm.hpp>
#include <fstream>
#include <SceneManager.h>
#include <AudioManager.h>
#include <TextureLoader.h>
#include <Sprite.h>
#include "PlayerMagicController.h"
#include "MagicObjectScaler.h"
#include "ObjectSpawner.h"
#include "SuddenJolt.h"

int main(int argc, char* argv[])
{
	Game game(600, 600, "2D Game Engine");
	game.setCursor("Test Resources\\cursor1.png");
	unsigned int texVal1 = TextureManager::loadTextureFromFile("Test Resources\\frasa.png", "texOne", false);
	unsigned int texVal2 = TextureManager::loadTextureFromFile("Test Resources\\mamma.png", "texTwo", false);
	unsigned int texVal3 = TextureManager::loadTextureFromFile("Test Resources\\lili.jpg", "texThree", false);

	AudioManager::loadAudioFromFile("Test Resources\\Swoosh.wav", "snd_1");
	PhysicsMaterial physicsMaterial1(0.0f, 0.0f, 1.0f, 0.6f, 0.3f);

	GameObject* tempGameObject;
	tempGameObject = GameObject::createGameObject("Camera");
	tempGameObject->addComponent(new Transform(glm::vec2(0, 0), 0.0f, glm::vec2(1, 1)));
	Camera* camera = new Camera;
	camera->init(glm::vec2(10, 10));
	tempGameObject->addComponent(camera);
	tempGameObject->addComponent(new PlayerMagicController);

	tempGameObject = GameObject::createGameObject("BG");
	tempGameObject->addComponent(new Transform(glm::vec2(0, 0), 0.0f, glm::vec2(1, 1)));
	tempGameObject->setLayerOrder(-10);
	Sprite * tempSprite = new Sprite();
	tempSprite->init(10, 10);
	tempSprite->setTextureID(texVal3);
	tempGameObject->addComponent(tempSprite);
	tempGameObject->addComponent(new ObjectSpawner);

	tempGameObject = GameObject::createGameObject("Sammy");
	tempGameObject->addComponent(new Transform(glm::vec2(0, 0), 0.0f, glm::vec2(1, 1)));
	tempGameObject->setLayerOrder(50);
	tempSprite = new Sprite();
	tempSprite->init(0.3f, 0.3f);
	tempSprite->setTextureID(texVal1);
	tempGameObject->addComponent(tempSprite);
	tempGameObject->addComponent(new MagicObjectScaler);

	tempGameObject = GameObject::createGameObject("Lola");
	tempGameObject->setLayerOrder(10);
	tempGameObject->addComponent(new Transform(glm::vec2(-1, -2), 0.0f, glm::vec2(1, 1)));
	tempSprite = new Sprite();
	tempSprite->init(0.5f, 0.5f);
	tempSprite->setTextureID(texVal1);
	tempGameObject->addComponent(tempSprite);

	tempGameObject = GameObject::createGameObject("Babu");
	tempGameObject->addComponent(new Transform(glm::vec2(-0.3f, 5.5f), 0.0f, glm::vec2(1, 1)));
	tempSprite = new Sprite();
	tempSprite->init(1.5f, 1.5f);
	tempSprite->setTextureID(texVal1);
	tempGameObject->addComponent(tempSprite);
	BoxCollider* boxCollider = new BoxCollider();
	boxCollider->init(tempGameObject->getComponent<Transform>()->position, glm::vec2(1.5f, 1.5f),
		physicsMaterial1, PhysicsBody::DYNAMIC);
	tempGameObject->addComponent(boxCollider);

	tempGameObject = GameObject::createGameObject("Galoo");
	tempGameObject->addComponent(new Transform(glm::vec2(-0.3f, -5.0f), 0.0f, glm::vec2(1, 1)));
	tempGameObject->setLayerOrder(20);
	tempSprite = new Sprite();
	tempSprite->init(8.0f, 1.0f);
	tempSprite->setTextureID(texVal2);
	tempGameObject->addComponent(tempSprite);
	boxCollider = new BoxCollider();
	boxCollider->init(tempGameObject->getComponent<Transform>()->position,
		glm::vec2(8.0f, 1.0f), physicsMaterial1, PhysicsBody::STATIC);
	tempGameObject->addComponent(boxCollider);

	SceneManager::SaveSceneData(GameObject::getAllGameObjects(), "s");

	game.initialize();
	game.update();
	game.cleanUp();
	return 0;
}
