#include <iostream>
#include <Game.h>
#include <GLM\glm.hpp>
#include <Box2D\Box2D.h>
#include "PlayerMagicController.h"

int main(int argc, char* argv[])
{
	Game game(600, 600, "2D Game Engine");

	unsigned int texVal1 = TextureLoader::loadTextureFromFile("Test Resources\\frasa.png", false);
	unsigned int texVal2 = TextureLoader::loadTextureFromFile("Test Resources\\mamma.png", false);
	GameObject* tempGameObject;

	tempGameObject = GameObject::createGameObject("Sammy");
	tempGameObject->addComponent(new Transform(glm::vec2(0, 0), 0.0f, glm::vec2(1, 1)));
	Sprite * tempSprite = new Sprite();
	tempSprite->init(0, 0, 50, 50);
	tempSprite->setTextureID(texVal1);
	tempGameObject->addComponent(tempSprite);

	tempGameObject = GameObject::createGameObject("Lola");
	tempGameObject->setLayerOrder(10);
	tempGameObject->addComponent(new Transform(glm::vec2(-50, -100), 0.0f, glm::vec2(1, 1)));
	tempSprite = new Sprite();
	tempSprite->init(0, 0, 80, 80);
	tempSprite->setTextureID(texVal1);
	tempGameObject->addComponent(tempSprite);
	tempGameObject->addComponent(new PlayerMagicController());

	tempGameObject = GameObject::createGameObject("Babu");
	tempGameObject->addComponent(new Transform(glm::vec2(-120, -100), 0.0f, glm::vec2(1, 1)));
	tempSprite = new Sprite();
	tempSprite->init(0, 0, 80, 80);
	tempSprite->setTextureID(texVal1);
	tempGameObject->addComponent(tempSprite);
	Box* boxCollider = new Box();
	boxCollider->init(game.getPhysicsWorld(), tempGameObject->getComponent<Transform>()->position, glm::vec2(80, 80), b2BodyType::b2_dynamicBody, 1.0f);
	tempGameObject->addComponent(boxCollider);

	tempGameObject = GameObject::createGameObject("Galoo");
	tempGameObject->addComponent(new Transform(glm::vec2(-120, -250), 0.0f, glm::vec2(1, 1)));
	tempSprite = new Sprite();
	tempSprite->init(0, 0, 300, 50);
	tempSprite->setTextureID(texVal2);
	tempGameObject->addComponent(tempSprite);
	boxCollider = new Box();
	boxCollider->init(game.getPhysicsWorld(), tempGameObject->getComponent<Transform>()->position,
		glm::vec2(300, 50), b2BodyType::b2_staticBody, 1.0f);
	tempGameObject->addComponent(boxCollider);

	game.initialize();
	game.update();
	return 0;
}
