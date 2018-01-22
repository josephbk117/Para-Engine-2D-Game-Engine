#include <iostream>
#include <chaiscript\chaiscript.hpp>
#include <chaiscript\chaiscript_stdlib.hpp>
#include <Game.h>
#include <GLM\glm.hpp>
#include <TextureLoader.h>
#include <AudioManager.h>
#include <InputData.h>
#include <Sprite.h>

Camera* CreateCamera(float width, float height);
Sprite* CreateSprite(unsigned int width, unsigned int height);
void AddCameraToGameObject(GameObject* gameObj, Camera* camera);
void AddSpriteToGameObject(GameObject* gameObj, Sprite* sprite);
void SetUpdateFunction(std::function<void()> update);
bool IsKeyPressed(char key);
float MathFuncSin(float radian);
float MathFuncCos(float radian);
float MathFuncAbs(float value);
float MathFuncPow(float value, float power);
float MathFuncSqrt(float value);

int main(int argc, char* argv[])
{
	chaiscript::ChaiScript chai(chaiscript::Std_Lib::library());
	chai.add(chaiscript::fun(&AddSpriteToGameObject), "AddSprite");
	chai.add(chaiscript::fun(&AddCameraToGameObject), "AddCamera");
	chai.add(chaiscript::fun(&SetUpdateFunction), "SetUpdateFunction");
	chai.add(chaiscript::fun(&IsKeyPressed), "IsKeyPressed");
	//Math Functions
	chai.add(chaiscript::fun(&MathFuncSin), "Sin");
	chai.add(chaiscript::fun(&MathFuncCos), "Cos");
	chai.add(chaiscript::fun(&MathFuncAbs), "Abs");
	chai.add(chaiscript::fun(&MathFuncPow), "Pow");
	chai.add(chaiscript::fun(&MathFuncSqrt), "Sqrt");

	chai.add(chaiscript::fun(&Game::isKeyPressed), "IsKeyPressed");
	chai.add(chaiscript::fun(&Game::setUpEngine), "SetUpEngine");
	chai.add(chaiscript::fun(&Game::cleanUp), "CleanUp");
	chai.add(chaiscript::fun(&Game::addScene), "AddScene");
	chai.add(chaiscript::fun(&Game::startScene), "StartScene");
	chai.add(chaiscript::fun(&Game::setCursor), "SetCursorImage");
	chai.add(chaiscript::fun(&Game::lockCursor), "LockCursor");
	chai.add(chaiscript::fun(&Game::getTimeSinceStartUp), "TimeSinceStartUp");
	chai.add(chaiscript::fun(&Game::getDeltaTime), "DeltaTime");
	chai.add(chaiscript::fun(&Game::setVsync), "SetVsync");

	chai.add(chaiscript::fun(&TextureManager::loadTextureFromFile), "LoadTextureFromFile");
	chai.add(chaiscript::fun(&TextureManager::getTextureIdFromReference), "GetTextureFromReference");
	chai.add(chaiscript::fun(&AudioManager::loadAudioFromFile), "LoadAudioFromFile");
	chai.add(chaiscript::user_type<GameObject>(), "GameObject");
	chai.add(chaiscript::fun(&GameObject::getName), "GetName");
	chai.add(chaiscript::fun(&GameObject::createGameObject), "CreateGameObject");
	chai.add(chaiscript::fun(&GameObject::deleteGameObjectWithName), "DeleteGameObject");
	chai.add(chaiscript::fun(&GameObject::getLayerOrder), "GetLayerOrder");
	chai.add(chaiscript::fun(&GameObject::setLayerOrder), "SetLayerOrder");
	chai.add(chaiscript::fun(&GameObject::addComponent), "AddComponent");

	chai.add(chaiscript::fun(&GameObject::getComponent<Transform>), "GetComponentTransform");
	chai.add(chaiscript::user_type<Sprite>(), "Sprite");
	chai.add(chaiscript::constructor<Sprite()>(), "Sprite");
	chai.add(chaiscript::fun(&CreateSprite), "CreateSprite");
	chai.add(chaiscript::fun(&Sprite::init), "Init");
	chai.add(chaiscript::fun(&Sprite::setTextureID), "SetTextureID");
	chai.add(chaiscript::fun(&Sprite::getTextureID), "GetTextureID");
	chai.add(chaiscript::fun(&Sprite::getDimensions), "GetDimensions");
	chai.add(chaiscript::fun<void, Sprite, float, float>(&Sprite::setDimension), "SetDimension");

	chai.add(chaiscript::user_type<Camera>(), "Camera");
	chai.add(chaiscript::constructor<Camera()>(), "Camera");
	chai.add(chaiscript::fun(&CreateCamera), "CreateCamera");
	chai.add(chaiscript::fun(&Camera::init), "Init");
	chai.add(chaiscript::fun(&Camera::setScale), "SetScale");

	chai.add(chaiscript::user_type<glm::vec2>(), "Vec2");
	chai.add(chaiscript::constructor<glm::vec2()>(), "Vec2");
	chai.add(chaiscript::fun(&glm::vec2::x), "x");
	chai.add(chaiscript::fun(&glm::vec2::y), "y");
	chai.add(chaiscript::user_type<Transform>(), "Transform");
	chai.add(chaiscript::constructor<Transform()>(), "Transform");
	chai.add(chaiscript::constructor<Transform(const Transform &)>(), "Transform");
	chai.add(chaiscript::fun(&Transform::setX), "SetX");
	chai.add(chaiscript::fun(&Transform::setY), "SetY");
	chai.add(chaiscript::fun(&Transform::setScale), "SetScale");
	chai.add(chaiscript::fun(&Transform::getPosition), "GetPosition");
	chai.add(chaiscript::fun<void, Transform, float, float>(&Transform::setPosition), "SetPosition");
	chai.add(chaiscript::fun(&Transform::setParent), "SetParent");
	chai.add(chaiscript::fun(&Transform::getParent), "GetParent");
	chai.add(chaiscript::fun(&Transform::addChild), "AddChild");

	chai.eval_file("Test Resources\\gameData.chai");
	chai.eval("CleanUp();");
	return 0;
}

void AddSpriteToGameObject(GameObject* gameObj, Sprite* sprite)
{
	gameObj->addComponent(sprite);
}

void SetUpdateFunction(std::function<void()> update)
{
	Game::scriptedUpdateFunction = update;
}

bool IsKeyPressed(char key)
{
	return Game::isKeyPressed((Key)((int)key));
}

float MathFuncSin(float radian)
{
	return glm::sin(radian);
}

float MathFuncCos(float radian)
{
	return glm::cos(radian);
}

float MathFuncAbs(float value)
{
	return glm::abs(value);
}

float MathFuncPow(float value, float power)
{
	return glm::pow(value, power);
}

float MathFuncSqrt(float value)
{
	return glm::sqrt(value);
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