#include <Game.h>
#include <GLM\glm.hpp>
#include <SceneManager.h>
#include <AudioManager.h>
#include <TextureLoader.h>
#include <Sprite.h>
#include <Text.h>
#include "PlayerMagicController.h"
#include "MagicObjectScaler.h"
#include "ObjectSpawner.h"
#include "SuddenJolt.h"
#include "InitialSceneLogic.h"
unsigned int texVal1;
unsigned int texVal2;
unsigned int texVal3;

void scene2LoadData();
void scene1LoadData();

int main(int argc, char* argv[])
{
	Game::setUpEngine(720, 720, "Para Engine - Game v1.1");
	//Game::setCursor("Test Resources\\cursor.png");
	//game.lockCursor(true);
	//game.hideCursor(true);
	texVal1 = TextureManager::loadTextureFromFile("Test Resources\\frasa.png", "texOne", false);
	texVal2 = TextureManager::loadTextureFromFile("Test Resources\\mamma.png", "texTwo", false);
	texVal3 = TextureManager::loadTextureFromFile("Test Resources\\lili.jpg", "texThree", false);
	TextureManager::loadTextureFromFile("Test Resources\\goli.png", "translu", false);
	AudioManager::loadAudioFromFile("Test Resources\\Swoosh.wav", "snd_1");

	Game::addScene(scene2LoadData, "scene1");
	Game::addScene(scene1LoadData, "scene2");
	Game::startScene("scene2", true);

	Game::cleanUp();
	return 0;
}
void scene2LoadData()
{
	PhysicsMaterial physicsMaterial1(0.0f, 0.0f, 1.0f, 0.6f, 0.5f);
	GameObject* tempGameObject;
	tempGameObject = GameObject::createGameObject("Camera");
	Camera* camera = new Camera;
	camera->init(glm::vec2(10, 10));
	tempGameObject->addComponent(camera);
	tempGameObject->addComponent(new PlayerMagicController);

	Text* textGui = new Text();
	textGui->init("Test Resources\\arial.ttf");
	textGui->text = "This got loaded up in this scene";

	tempGameObject = GameObject::createGameObject("textelement", true);
	tempGameObject->setLayerOrder(1500);
	tempGameObject->getComponent<Transform>()->setPosition(glm::vec2(-380, 450));
	tempGameObject->addComponent(textGui);

	tempGameObject = GameObject::createGameObject("BG");
	tempGameObject->setLayerOrder(-10);
	Sprite * tempSprite = new Sprite();
	tempSprite->init(10, 10);
	tempSprite->setTextureID(texVal3);
	tempGameObject->addComponent(tempSprite);
	tempGameObject->addComponent(new ObjectSpawner);

	tempGameObject = GameObject::createGameObject("Lola");
	tempGameObject->setLayerOrder(10);
	tempGameObject->getComponent<Transform>()->setPosition(glm::vec2(-1, -2));
	tempSprite = new Sprite();
	tempSprite->init(0.5f, 0.5f);
	tempSprite->setTextureID(texVal1);
	tempGameObject->addComponent(tempSprite);

	tempGameObject = GameObject::createGameObject("FollowMouse");
	tempGameObject->setLayerOrder(10);
	tempSprite = new Sprite();
	tempSprite->init(0.5f, 0.5f);
	tempSprite->setTextureID(texVal1);
	tempGameObject->addComponent(tempSprite);
	tempGameObject->addComponent(new MagicObjectScaler);

	Transform* followMouseTransform = tempGameObject->getComponent<Transform>();

	tempGameObject = GameObject::createGameObject("ChildOfFollowMouse");
	tempGameObject->getComponent<Transform>()->setRotation(glm::radians(45.0f));
	tempGameObject->getComponent<Transform>()->setPosition(glm::vec2(1, 0));

	tempGameObject->getComponent<Transform>()->setParent(followMouseTransform);
	tempGameObject->setLayerOrder(15);
	tempSprite = new Sprite();
	tempSprite->init(0.5f, 0.5f);
	tempSprite->setTextureID(texVal1);
	tempGameObject->addComponent(tempSprite);
	
	tempGameObject = GameObject::createGameObject("Babu");
	tempGameObject->getComponent<Transform>()->setPosition(glm::vec2(-0.3f, 5.5f));
	tempSprite = new Sprite();
	tempSprite->init(1.5f, 1.5f);
	tempSprite->setTextureID(texVal1);
	tempGameObject->addComponent(tempSprite);
	BoxCollider* boxCollider = new BoxCollider();
	boxCollider->init(tempGameObject->getComponent<Transform>()->getPosition(),
		glm::vec2(1.5f, 1.5f), physicsMaterial1, PhysicsBody::DYNAMIC);
	tempGameObject->addComponent(boxCollider);

	tempGameObject = GameObject::createGameObject("PhyMove");
	tempGameObject->getComponent<Transform>()->setPosition(glm::vec2(0.0f, 3.5f));
	tempSprite = new Sprite();
	tempSprite->init(0.4f, 0.4f);
	tempSprite->setTextureID(texVal2);
	tempGameObject->addComponent(tempSprite);
	boxCollider = new BoxCollider();
	boxCollider->init(tempGameObject->getComponent<Transform>()->getPosition(),
		glm::vec2(0.4f, 0.4f), physicsMaterial1, PhysicsBody::KINEMATIC);
	tempGameObject->addComponent(boxCollider);

	tempGameObject = GameObject::createGameObject("Galoo");
	tempGameObject->getComponent<Transform>()->setPosition(glm::vec2(0.0f, -5.0f));
	tempGameObject->setLayerOrder(20);
	tempSprite = new Sprite();
	tempSprite->init(10.0f, 1.0f);
	tempSprite->setTextureID(texVal2);
	tempGameObject->addComponent(tempSprite);
	boxCollider = new BoxCollider();
	boxCollider->init(tempGameObject->getComponent<Transform>()->getPosition(),
		glm::vec2(10.0f, 1.0f), physicsMaterial1, PhysicsBody::STATIC);
	tempGameObject->addComponent(boxCollider);

	tempGameObject = GameObject::createGameObject("Galoo1");
	tempGameObject->getComponent<Transform>()->setPosition(glm::vec2(-5.5f, -0.0f));
	tempGameObject->setLayerOrder(20);
	tempSprite = new Sprite();
	tempSprite->init(1.0f, 10.0f);
	tempSprite->setTextureID(texVal2);
	tempGameObject->addComponent(tempSprite);
	boxCollider = new BoxCollider();
	boxCollider->init(tempGameObject->getComponent<Transform>()->getPosition(),
		glm::vec2(1.0f, 10.0f), physicsMaterial1, PhysicsBody::STATIC);
	tempGameObject->addComponent(boxCollider);

	tempGameObject = GameObject::createGameObject("Galoo2");
	tempGameObject->getComponent<Transform>()->setPosition(glm::vec2(5.5f, -0.0f));
	tempGameObject->setLayerOrder(20);
	tempSprite = new Sprite();
	tempSprite->init(1.0f, 10.0f);
	tempSprite->setTextureID(texVal2);
	tempGameObject->addComponent(tempSprite);
	boxCollider = new BoxCollider();
	boxCollider->init(tempGameObject->getComponent<Transform>()->getPosition(),
		glm::vec2(1.0f, 10.0f), physicsMaterial1, PhysicsBody::STATIC);
	tempGameObject->addComponent(boxCollider);
}

void scene1LoadData()
{
	int logoTexValue = TextureManager::loadTextureFromFile("Test Resources\\paraEngineLogo.png", "logo", false);
	GameObject* tempGameObject;
	tempGameObject = GameObject::createGameObject("Logo");
	Sprite* sprite = new Sprite;
	sprite->init(4.0f, 4.0f);
	sprite->setTextureID(logoTexValue);
	tempGameObject->addComponent(sprite);

	//UI
	tempGameObject = GameObject::createGameObject("gui_1", true);
	tempGameObject->setLayerOrder(1800);
	sprite = new Sprite;
	sprite->init(1.0f, 0.15f);
	sprite->setTextureID(TextureManager::getTextureFromReference("translu"));
	tempGameObject->addComponent(sprite);
	tempGameObject->getComponent<Transform>()->setPosition(glm::vec2(-0.5f, 0.925f));

	tempGameObject = GameObject::createGameObject("Camera");
	Camera* camera = new Camera;
	camera->init(glm::vec2(10, 10));
	tempGameObject->addComponent(camera);
	tempGameObject->addComponent(new InitialSceneLogic);
}
