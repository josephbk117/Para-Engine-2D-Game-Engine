#include <iostream>
#include <chaiscript\chaiscript.hpp>
#include <chaiscript\chaiscript_stdlib.hpp>
#include <Game.h>
#include <GLM\glm.hpp>
#include <TextureLoader.h>
#include <Sprite.h>

Camera* CreateCamera(float width, float height);
Sprite* CreateSprite(unsigned int width, unsigned int height);
void AddCameraToGameObject(GameObject* gameObj, Camera* camera);
void AddSpriteToGameObject(GameObject* gameObj, Sprite* sprite);

int main(int argc, char* argv[])
{
	chaiscript::ChaiScript chai(chaiscript::Std_Lib::library());
	chai.add(chaiscript::fun(&AddSpriteToGameObject), "AddSprite");
	chai.add(chaiscript::fun(&AddCameraToGameObject), "AddCamera");
	chai.add(chaiscript::fun(&Game::setUpEngine), "SetUpEngine");
	chai.add(chaiscript::fun(&Game::cleanUp), "CleanUp");
	chai.add(chaiscript::fun(&Game::addScene), "AddScene");
	chai.add(chaiscript::fun(&Game::startScene), "StartScene");

	chai.add(chaiscript::fun(&TextureManager::loadTextureFromFile), "LoadTextureFromFile");
	chai.add(chaiscript::user_type<GameObject>(), "GameObject");
	chai.add(chaiscript::fun(&GameObject::getName), "GetName");
	chai.add(chaiscript::fun(&GameObject::createGameObject), "CreateGameObject");
	chai.add(chaiscript::fun(&GameObject::addComponent), "AddComponent");

	//Can get rid of compoents in c++ sense in this case. Can make components in chai itself
	//Might have to make chaiscript version of some classes

	chai.add(chaiscript::fun(&GameObject::getComponent<Transform>), "GetComponentTransform");
	chai.add(chaiscript::user_type<Sprite>(), "Sprite");
	chai.add(chaiscript::constructor<Sprite()>(), "Sprite");
	chai.add(chaiscript::fun(&CreateSprite), "CreateSprite");
	chai.add(chaiscript::fun(&Sprite::init), "Init");
	chai.add(chaiscript::fun(&Sprite::setTextureID), "SetTextureID");
	chai.add(chaiscript::fun(&Sprite::getTextureID), "GetTextureID");
	chai.add(chaiscript::fun(&Sprite::getDimensions), "GetDimensions");
	chai.add(chaiscript::fun(&Sprite::setDimension), "SetDimensions");

	chai.add(chaiscript::user_type<Camera>(), "Camera");
	chai.add(chaiscript::constructor<Camera()>(), "Camera");
	chai.add(chaiscript::fun(&CreateCamera), "CreateCamera");
	chai.add(chaiscript::fun(&Camera::init), "Init");
	chai.add(chaiscript::fun(&Camera::setScale), "SetScale");

	chai.add(chaiscript::user_type<glm::vec2>(), "Vec2");
	chai.add(chaiscript::constructor<glm::vec2()>(), "Vec2");
	chai.add(chaiscript::fun(&glm::vec2::x), "x");
	chai.add(chaiscript::fun(&glm::vec2::y), "y");
	chai.add(chaiscript::fun(&Transform::setX), "SetX");
	chai.add(chaiscript::fun(&Transform::setY), "SetY");
	chai.add(chaiscript::fun(&Transform::setScale), "SetScale");
	chai.add(chaiscript::fun(&Transform::getPosition), "GetPosition");
	chai.add(chaiscript::fun(&Transform::setPosition), "SetPosition");
	chai.add(chaiscript::fun(&Transform::setParent), "SetParent");
	chai.add(chaiscript::fun(&Transform::getParent), "GetParent");
	chai.add(chaiscript::fun(&Transform::addChild), "AddChild");

	chai.eval_file("Test Resources\\gameData.chai");
	chai.eval_file("CleanUp()");
	return 0;
}

void AddSpriteToGameObject(GameObject* gameObj, Sprite* sprite)
{
	gameObj->addComponent(sprite);
}

void AddCameraToGameObject(GameObject* gameObj, Camera* camera)
{
	gameObj->addComponent(camera);
}

Sprite* CreateSprite(unsigned int width, unsigned int height)
{
	Sprite* sp = new Sprite;
	sp->init(width, height);
	return sp;
}

Camera* CreateCamera(float width, float height)
{
	Camera* camera = new Camera;
	camera->init(glm::vec2(width, height));
	return camera;
}