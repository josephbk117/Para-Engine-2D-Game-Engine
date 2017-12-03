#include <Game.h>
#include <GLM\glm.hpp>
#include <SceneManager.h>
#include <AudioManager.h>
#include <TextureLoader.h>
#include <Sprite.h>
#include <GuiElement.h>
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
	Game::setUpEngine(600, 600, "Para Engine - Game v0.5");
	Game::setCursor("Test Resources\\cursor.png");
	//game.lockCursor(true);
	//game.hideCursor(true);
	texVal1 = TextureManager::loadTextureFromFile("Test Resources\\frasa.png", "texOne", false);
	texVal2 = TextureManager::loadTextureFromFile("Test Resources\\mamma.png", "texTwo", false);
	texVal3 = TextureManager::loadTextureFromFile("Test Resources\\lili.jpg", "texThree", false);
	TextureManager::loadTextureFromFile("Test Resources\\goli.png", "translu", false);
	AudioManager::loadAudioFromFile("Test Resources\\Swoosh.wav", "snd_1");

	Game::addScene(scene2LoadData, "scene1");
	Game::addScene(scene1LoadData, "scene2");
	Game::startScene("scene2",true);

	//SceneManager::SaveSceneData(GameObject::getAllGameObjects(), "s");

	Game::cleanUp();
	return 0;
}
void scene2LoadData()
{
	Text* textGui = new Text();
	textGui->init("Test Resources\\arial.ttf", -380, 450);
	textGui->text = "This got loaded up in this scene";

	GuiElement* guiElementWithText = GuiElement::createGuiElement("textelement");
	guiElementWithText->setScreenLocation(glm::vec2(-0.5f, 0.95f));
	guiElementWithText->addGuiComponent(textGui);

	PhysicsMaterial physicsMaterial1(0.0f, 0.0f, 1.0f, 0.6f, 0.5f);
	GameObject* tempGameObject;
	tempGameObject = GameObject::createGameObject("Camera");
	tempGameObject->addComponent(new Transform());
	Camera* camera = new Camera;
	camera->init(glm::vec2(10, 10));
	tempGameObject->addComponent(camera);
	tempGameObject->addComponent(new PlayerMagicController);

	tempGameObject = GameObject::createGameObject("BG");
	tempGameObject->addComponent(new Transform());
	tempGameObject->setLayerOrder(-10);
	Sprite * tempSprite = new Sprite();
	tempSprite->init(10, 10);
	tempSprite->setTextureID(texVal3);
	tempGameObject->addComponent(tempSprite);
	tempGameObject->addComponent(new ObjectSpawner);

	tempGameObject = GameObject::createGameObject("Lola");
	tempGameObject->setLayerOrder(10);
	tempGameObject->addComponent(new Transform(glm::vec2(-1, -2), 0.0f, glm::vec2(1, 1)));
	tempSprite = new Sprite();
	tempSprite->init(0.5f, 0.5f);
	tempSprite->setTextureID(texVal1);
	tempGameObject->addComponent(tempSprite);

	tempGameObject = GameObject::createGameObject("FollowMouse");
	tempGameObject->setLayerOrder(10);
	tempGameObject->addComponent(new Transform);
	tempSprite = new Sprite();
	tempSprite->init(0.5f, 0.5f);
	tempSprite->setTextureID(texVal1);
	tempGameObject->addComponent(tempSprite);
	tempGameObject->addComponent(new MagicObjectScaler);

	tempGameObject = GameObject::createGameObject("Babu");
	tempGameObject->addComponent(new Transform(glm::vec2(-0.3f, 5.5f), 0.0f, glm::vec2(1, 1)));
	tempSprite = new Sprite();
	tempSprite->init(1.5f, 1.5f);
	tempSprite->setTextureID(texVal1);
	tempGameObject->addComponent(tempSprite);
	BoxCollider* boxCollider = new BoxCollider();
	boxCollider->init(tempGameObject->getComponent<Transform>()->getPosition(), glm::vec2(1.5f, 1.5f),
		physicsMaterial1, PhysicsBody::DYNAMIC);
	tempGameObject->addComponent(boxCollider);

	tempGameObject = GameObject::createGameObject("PhyMove");
	tempGameObject->addComponent(new Transform(glm::vec2(0.0f, 3.5f), 0.0f, glm::vec2(1, 1)));
	tempSprite = new Sprite();
	tempSprite->init(0.4f, 0.4f);
	tempSprite->setTextureID(texVal2);
	tempGameObject->addComponent(tempSprite);
	boxCollider = new BoxCollider();
	boxCollider->init(tempGameObject->getComponent<Transform>()->getPosition(), glm::vec2(0.4f, 0.4f),
		physicsMaterial1, PhysicsBody::KINEMATIC);
	tempGameObject->addComponent(boxCollider);

	tempGameObject = GameObject::createGameObject("Galoo");
	tempGameObject->addComponent(new Transform(glm::vec2(0.0f, -5.0f), 0.0f, glm::vec2(1, 1)));
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
	tempGameObject->addComponent(new Transform(glm::vec2(-5.5f, -0.0f), 0.0f, glm::vec2(1, 1)));
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
	tempGameObject->addComponent(new Transform(glm::vec2(5.5f, -0.0f), 0.0f, glm::vec2(1, 1)));
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
	GuiElement* guiEle = GuiElement::createGuiElement("gui_1");
	Sprite* guiSprite = new Sprite;
	guiSprite->init(1.0f, 0.15f);
	guiSprite->setTextureID(TextureManager::getTextureFromReference("translu"));
	guiEle->addGuiComponent(guiSprite);
	guiEle->setScreenLocation(glm::vec2(-0.5f, 0.925f));

	int logoTexValue = TextureManager::loadTextureFromFile("Test Resources\\paraEngineLogo.png", "logo", false);
	GameObject* tempGameObject;
	tempGameObject = GameObject::createGameObject("Logo");
	tempGameObject->addComponent(new Transform);
	Sprite* sprite = new Sprite;
	sprite->init(4.0f, 4.0f);
	sprite->setTextureID(logoTexValue);
	tempGameObject->addComponent(sprite);

	tempGameObject = GameObject::createGameObject("Camera");
	tempGameObject->addComponent(new Transform());
	Camera* camera = new Camera;
	camera->init(glm::vec2(10, 10));
	tempGameObject->addComponent(camera);
	tempGameObject->addComponent(new InitialSceneLogic);
}
