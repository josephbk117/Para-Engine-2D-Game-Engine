#include <iostream>
#include <chaiscript\chaiscript.hpp>
#include <chaiscript\chaiscript_stdlib.hpp>
#include <Game.h>
#include <GLM\glm.hpp>
#include <TextureLoader.h>
#include <Sprite.h>

void scene1LoadData();

void callFunc(const std::function<void()> &func)
{
	func();
}

void AddSpriteToGameObject(GameObject* gameObj, Sprite* sprite)
{
	gameObj->addComponent(sprite);
}

void AddCameraToGameObject(GameObject* gameObj, Camera* camera)
{
	gameObj->addComponent(camera);
}
void printValue()
{
	std::cout << "\nLOLZ";
}
int main(int argc, char* argv[])
{
	chaiscript::ChaiScript chai(chaiscript::Std_Lib::library());
	chai.add(chaiscript::fun(&AddSpriteToGameObject), "AddSprite");
	chai.add(chaiscript::fun(&Game::setUpEngine), "SetUpEngine");
	chai.add(chaiscript::fun(&Game::cleanUp), "CleanUp");
	chai.add(chaiscript::fun(&Game::addScene) ,"AddScene");
	chai.add(chaiscript::fun(&Game::startScene), "StartScene");

	chai.add(chaiscript::fun(&TextureManager::loadTextureFromFile), "LoadTextureFromFile");
	chai.add(chaiscript::user_type<GameObject>(), "GameObject");
	chai.add(chaiscript::fun(&GameObject::getName), "GetName");
	chai.add(chaiscript::fun(&GameObject::createGameObject), "CreateGameObject");
	chai.add(chaiscript::fun(&GameObject::addComponent), "AddComponent");
	chai.add(chaiscript::fun(&callFunc), "CallFunc");

	//Can get rid of compoents in c++ sense in this case. Can make components in chai itself
	//Might have to make chaiscript version of some classes

	//chai.add(chaiscript::user_type<Component>(), "Component");
	//chai.add(chaiscript::constructor<Component>(), "Component");
	chai.add(chaiscript::fun(&GameObject::getComponent<Transform>), "GetComponentTransform");
	chai.add(chaiscript::user_type<Sprite>(), "Sprite");
	chai.add(chaiscript::constructor<Sprite()>(), "Sprite");
	//chai.add(chaiscript::base_class<Component, Sprite>());
	chai.add(chaiscript::fun(&Sprite::init), "Init");
	chai.add(chaiscript::fun(&Sprite::setTextureID), "SetTextureID");
	chai.add(chaiscript::fun(&Sprite::getTextureID), "GetTextureID");
	chai.add(chaiscript::user_type<Camera>(), "Camera");
	chai.add(chaiscript::constructor<Camera()>(), "Camera");
	chai.add(chaiscript::fun(&Camera::init), "Init");
	chai.add(chaiscript::fun(&scene1LoadData), "scene1LoadData");
	
	chai.eval("SetUpEngine(700,700,\"POOP\")");
	chai.eval(R"!(  
		def scene1()
		{
			CreateGameObject("Onno",false);
			//var obj := CreateGameObject("OBJ1",false);
			var sp = Sprite();
			sp.Init(4.0f,4.0f);
			sp.SetTextureID(LoadTextureFromFile("Test Resources\\paraEngineLogo.png", "logo", false));
			//AddSpriteToGameObject(obj,sp);
		}
		
	)!");

	chai.eval("AddScene(scene1,\"scene2\")");
	chai.eval("StartScene(\"scene2\",true)");
	chai.eval("CleanUp()");
	std::cin.get();
	return 0;
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
}