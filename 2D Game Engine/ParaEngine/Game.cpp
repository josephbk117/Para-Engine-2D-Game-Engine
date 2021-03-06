#define IMGUI_USEN
#include <GL\glew.h>
#include "Game.h"
#include <iostream>
#include <vector>
#include <random>
#include <typeinfo>
#include <Yse\yse.hpp>
#include <Box2D\Box2D.h>
#include <memory>
#include <chrono>
#include <thread>
#include <functional>

#ifdef IMGUI_USE
#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"
#endif 

#include "stb_image_write.h"
#include "AudioManager.h"
#include "Transform.h"
#include "AudioManager.h"
#include "TextureLoader.h"
#include "ShaderProgram.h"
#include "Box.h"
#include "Sprite.h"
#include "GameObject.h"
#include "Camera.h"
#include <GLFW\glfw3.h>
#include "Text.h"

bool Game::frameBufferSizeUpdated;
float Game::deltaTime;
float Game::timeSinceStartUp;
ShaderProgram Game::postProcessor;
glm::vec2 Game::mouseCoord;
glm::vec2 Game::windowSize;
glm::vec3 Game::clearColour = glm::vec3(0.15f, 0.15f, 0.15f);
std::unordered_map<std::string, std::function<void()>> Game::scenes;
std::function<void()> Game::activeSceneInitFunc;
std::function<void()> Game::scriptedUpdateFunction = NULL;

struct Game::InternalAcess
{
	friend class BoxCollider;
	std::chrono::steady_clock clockTime;
	GLFWwindow* window;
	GLFWcursor* cursor;
	static std::vector<GameObject *> gameObjects;
	static std::unique_ptr<b2World> world;
	static Camera* camera;
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};

struct Game::ContactListener : public b2ContactListener
{
	void BeginContact(b2Contact* contact)
	{
		GameObject* gameObjRefA = static_cast<GameObject *>(contact->GetFixtureA()->GetBody()->GetUserData());
		GameObject* gameObjRefB = static_cast<GameObject *>(contact->GetFixtureB()->GetBody()->GetUserData());

		std::vector<Component *> components = gameObjRefA->getAttachedComponents();
		unsigned int sizeValue = components.size();
		for (unsigned int i = 0; i < sizeValue; i++)
			components[i]->collisionStarted(gameObjRefB);

		components = gameObjRefB->getAttachedComponents();
		sizeValue = components.size();
		for (unsigned int i = 0; i < sizeValue; i++)
			components[i]->collisionStarted(gameObjRefA);
	}
	void EndContact(b2Contact* contact)
	{
		GameObject* gameObjRefA = static_cast<GameObject *>(contact->GetFixtureA()->GetBody()->GetUserData());
		GameObject* gameObjRefB = static_cast<GameObject *>(contact->GetFixtureB()->GetBody()->GetUserData());

		for (unsigned int i = 0; i < GameObject::objectsMarkedForDeletion.size(); i++)
		{
			if (gameObjRefA == GameObject::objectsMarkedForDeletion[i] ||
				gameObjRefB == GameObject::objectsMarkedForDeletion[i])
				return;
		}
		std::vector<Component *> components = gameObjRefA->getAttachedComponents();
		unsigned int sizeValue = components.size();
		for (unsigned int i = 0; i < sizeValue; i++)
			components[i]->collisionEnded(gameObjRefB);
		components = gameObjRefB->getAttachedComponents();
		sizeValue = components.size();
		for (unsigned int i = 0; i < sizeValue; i++)
			components[i]->collisionEnded(gameObjRefA);
	}
};

std::unique_ptr<Game::InternalAcess> Game::access;
Game::ContactListener* Game::contactListener;
std::vector<GameObject *> Game::InternalAcess::gameObjects;
std::unique_ptr<b2World> Game::InternalAcess::world;
Camera* Game::InternalAcess::camera;

//_____LOCAL DATA_____//
Sprite screenPostProcessingElement;
unsigned int fbo;
void Game::setUpEngine(unsigned int screenWidth, unsigned int screenHeight, const std::string& title)
{
	access->world = std::make_unique<b2World>(b2Vec2(0, -9.81f));
	contactListener = new ContactListener;

	windowSize = glm::vec2(screenWidth, screenHeight);
	glfwInit();
	access = std::make_unique<InternalAcess>();
	access->window = glfwCreateWindow(screenWidth, screenHeight, title.c_str(), NULL, NULL);
	if (access->window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(access->window);
	glfwSetInputMode(access->window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetFramebufferSizeCallback(access->window, access->framebuffer_size_callback);

	GLenum err = glewInit();
#if _DEBUG
	if (GLEW_OK != err)
		std::cout << "Error: %s\n" << glewGetErrorString(err);
	else
		std::cout << " Glew initialsed" << std::endl;
#endif
#ifdef IMGUI_USE
	IMGUI_INIT(access->window, true);
#endif // IMGUI_USE
	YSE::System().init();

	//_________FBO SET UP_________
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	// create a color attachment texture
	unsigned int textureColorbuffer;
	glGenTextures(1, &textureColorbuffer);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, windowSize.x, windowSize.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
	// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, windowSize.x, windowSize.y); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
																								  // now that we actually created the framebuffer and added all attachments 
	//we want to check if it is actually complete now
#if _DEBUG
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!";
#endif
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	screenPostProcessingElement.init(2, 2);
	screenPostProcessingElement.setTextureID(textureColorbuffer);
	activeSceneInitFunc = NULL;
	glEnable(GL_CULL_FACE);
}

void Game::initialize(std::function<void()> initFunc)
{
	access->camera = nullptr;
	GameObject::clearGameObjectData();
	initFunc();
	access->gameObjects = GameObject::getAllGameObjects();
	unsigned int size = access->gameObjects.size();
	for (unsigned int i = 0; i < size; i++)
	{
		access->gameObjects[i]->hasStartBeenCalled = true;
		std::vector<Component*> componentsAttachedToObject = access->gameObjects[i]->getAttachedComponents();
		unsigned int componentCount = componentsAttachedToObject.size();
		if (access->camera == nullptr)
		{
			Camera* camera = access->gameObjects[i]->getComponent<Camera>();
			if (camera != nullptr)
				access->camera = camera;
		}
		for (unsigned int i = 0; i < componentCount; i++)
			(*componentsAttachedToObject[i]).start();
	}
	if (access->camera == nullptr)
	{
#if _DEBUG
		std::cout << "\nNo Camera Has Been Attached To An Object\nProviding Default Camera\n";
#endif
		access->camera = new Camera();
		int width, height;
		glfwGetWindowSize(access->window, &width, &height);
		access->camera->init(glm::vec2(width, height));
	}
	std::stable_sort(access->gameObjects.begin(), access->gameObjects.end(), [](GameObject* a, GameObject* b)
	{ return a->getLayerOrder() < b->getLayerOrder(); });
	access->world.get()->SetContactListener(contactListener);
}
//ImVec4 clearColour;
GLint postProcesBrightnessLocation;
void Game::update()
{
	ShaderProgram shaderGameObjectsBase;
	shaderGameObjectsBase.compileShaders("Test Resources\\Shaders\\spriteBase.vs", "Test Resources\\Shaders\\spriteBase.fs");
	shaderGameObjectsBase.addAttribute("vertexPosition");
	shaderGameObjectsBase.linkShaders();

	ShaderProgram shaderUiElementBase;
	shaderUiElementBase.compileShaders("Test Resources\\Shaders\\uiElementBase.vs", "Test Resources\\Shaders\\uiElementBase.fs");
	shaderUiElementBase.addAttribute("vertexPosition");
	shaderUiElementBase.linkShaders();

	postProcessor.compileShaders("Test Resources\\Shaders\\postProcess.vs", "Test Resources\\Shaders\\postProcess.fs");
	postProcessor.linkShaders();

	GLint textureGameObjectLocation = shaderGameObjectsBase.getUniformLocation("textureOne");
	GLint uniformProjectionMatrixGameObjectLocation = shaderGameObjectsBase.getUniformLocation("projection");
	GLint uniformModelMatrixGameObjectLocation = shaderGameObjectsBase.getUniformLocation("model");

	GLint textureUiLocation = shaderUiElementBase.getUniformLocation("textureOne");
	GLint uniformModelMatrixUiLocation = shaderUiElementBase.getUniformLocation("model");

	postProcesBrightnessLocation = postProcessor.getUniformLocation("brightness");

	std::chrono::steady_clock::time_point start = access->clockTime.now();
	std::chrono::steady_clock::time_point initialTime = start;
	deltaTime = 0.0f;
	timeSinceStartUp = 0.0f;

	while (!glfwWindowShouldClose(access->window))
	{
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glClearColor(Game::clearColour.x, Game::clearColour.y, Game::clearColour.z, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (activeSceneInitFunc != NULL)
		{
			initialize(activeSceneInitFunc);
			activeSceneInitFunc = NULL;
		}
		else
			access->world->SetContactListener(contactListener);
		if (frameBufferSizeUpdated)
		{
			int width, height;
			glfwGetWindowSize(access->window, &width, &height);
#if _DEBUG
			std::cout << "\nUpdated to : " << width << " ," << height;
#endif
			access->camera->setScreenRatio(glm::vec2(width * ((float)width / height), height));
			frameBufferSizeUpdated = false;
		}
		YSE::System().update();
		if (GameObject::isDirty)
		{
			GameObject::isDirty = false;
			GameObject::removeAllObjectsMarkedForDeletion();
			access->gameObjects = GameObject::getAllGameObjects();
			unsigned int sizeValue = access->gameObjects.size();
			for (unsigned int i = 0; i < sizeValue; i++)
			{
				GameObject* gameObjRef = access->gameObjects[i];
				if (!gameObjRef->hasStartBeenCalled)
				{
					gameObjRef->hasStartBeenCalled = true;
					std::vector<Component*> componentsAttachedToObject = gameObjRef->getAttachedComponents();
					unsigned int componentCount = componentsAttachedToObject.size();
					for (unsigned int i = 0; i < componentCount; i++)
						(*componentsAttachedToObject[i]).start();
				}
			}
			std::stable_sort(access->gameObjects.begin(), access->gameObjects.end(), [](GameObject* a, GameObject* b)
			{return a->getLayerOrder() < b->getLayerOrder(); });
		}
#ifdef IMGUI_USE
		IMGUI_NEWFRAME();
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
			ImGui::GetIO().Framerate);
#endif // IMGUI_USE

		std::vector<GameObject *> uiGameobjs;
		shaderGameObjectsBase.use();
		ShaderProgram::applyShaderUniformMatrix(uniformProjectionMatrixGameObjectLocation, access->camera->getOrthoMatrix());
		glUniform1i(textureGameObjectLocation, 0);
		for (unsigned int i = 0; i < access->gameObjects.size(); i++)
		{
			if (access->gameObjects[i]->isPartOfUI)
				uiGameobjs.push_back(access->gameObjects[i]);
			else
			{
				Transform *transformRef = access->gameObjects[i]->getComponent<Transform>();
				BoxCollider* boxcolBody = access->gameObjects[i]->getComponent<BoxCollider>();
				if (boxcolBody != nullptr)
				{
					transformRef->setPosition(glm::vec2(boxcolBody->getPosition().x, boxcolBody->getPosition().y));
					transformRef->setRotation(boxcolBody->getAngle());
				}
				std::vector<Component*> componentsAttachedToObject =
					GameObject::getGameObjectWithName(access->gameObjects[i]->getName())->getAttachedComponents();
				for (unsigned int i = 0; i < componentsAttachedToObject.size(); i++)
					(*componentsAttachedToObject[i]).update();
				if (access->camera->isObjectInCameraView(transformRef->getPosition(), transformRef->getScale()))
				{
					ShaderProgram::applyShaderUniformMatrix(uniformModelMatrixGameObjectLocation, transformRef->getWorldSpaceTransform());
					Sprite* spriteToDraw = access->gameObjects[i]->getComponent<Sprite>();
					if (spriteToDraw != nullptr)
						spriteToDraw->draw();
				}
			}
		}

		//TODO:
		//Shader manager stuff
		//Fix issues with ,.;"' symbols in fonts
		//Add Font manager as well
		//make gui element less dependant on gameobject or merge them together
		//---can implicitly make them gui elements if attached to canvas object etc
		//can add gui elements (game objects) to another vector and then render them separatly
		//Make sound source as component

		shaderGameObjectsBase.unuse();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		postProcessor.use();
		glUniform1f(postProcesBrightnessLocation, (-1.0f + sin(Game::getTimeSinceStartUp())) / 2.0f);
		screenPostProcessingElement.draw();
		postProcessor.unuse();

		glBindTexture(GL_TEXTURE_2D, 0);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		unsigned int size = uiGameobjs.size();
		for (unsigned int i = 0; i < size; i++)
		{
			shaderUiElementBase.use();
			glm::mat4 matrix = uiGameobjs[i]->getComponent<Transform>()->getMatrix();
			shaderUiElementBase.applyShaderUniformMatrix(uniformModelMatrixUiLocation, matrix);
			const std::vector<Component *>guiComponents = uiGameobjs[i]->getAttachedComponents();
			unsigned int componentSize = guiComponents.size();
			if (uiGameobjs[i]->getComponent<Sprite>() != nullptr)
				uiGameobjs[i]->getComponent<Sprite>()->draw();
			shaderUiElementBase.unuse();
			for (unsigned int i = 0; i < componentSize; i++)
				guiComponents[i]->update();
		}
		if(scriptedUpdateFunction != NULL)
			scriptedUpdateFunction();
		glDisable(GL_BLEND);

#ifdef IMGUI_USE
		ImGui::Render();
#endif // IMGUI_USE

		glfwSwapBuffers(access->window);
		glfwPollEvents();

		std::chrono::duration<float> frameTime = access->clockTime.now() - start;
		deltaTime = frameTime.count();
		access->world->Step(deltaTime, 4, 5);
		std::chrono::duration<float> sinceStart = access->clockTime.now() - initialTime;
		timeSinceStartUp = sinceStart.count();

		start = access->clockTime.now();
	}
#ifdef IMGUI_USE
	IMGUI_SHUTDOWN();
#endif // IMGUI_USE
	YSE::System().close();
	access->world.get()->SetContactListener(nullptr);
	delete contactListener;
	glfwTerminate();
	return;
}
void Game::setCursor(const std::string & cursorImagePath)
{
	glfwSetInputMode(access->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	std::vector<unsigned char>pixels;
	int w, h;
	TextureManager::getRawImageDataFromFile(cursorImagePath, pixels, w, h, false);

	GLFWimage image;
	image.width = w;
	image.height = h;
	image.pixels = &pixels[0];

	access->cursor = glfwCreateCursor(&image, 0, 0);
	glfwSetCursor(access->window, access->cursor);
}
void Game::hideCursor(bool hide)
{
	if (hide)
		glfwSetInputMode(access->window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	else
		glfwSetInputMode(access->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}
void Game::lockCursor(bool lock)
{
	if (lock)
		glfwSetInputMode(access->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	else
		glfwSetInputMode(access->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}
bool pressed = false;

void Game::cleanUp()
{
	GameObject::removeAllGameObjectsFromMemory();
	AudioManager::removeLoadedAudioFromMemory();
	TextureManager::unloadTexturesFromMemory();
	if (access->cursor != nullptr)
		glfwDestroyCursor(access->cursor);
}

void Game::setPostProcessingShader(const ShaderProgram &program)
{
}

void Game::addScene(const std::function<void()> &sceneSetupFunc, const std::string & sceneName)
{
	scenes[sceneName] = sceneSetupFunc;
}

void Game::startScene(const std::string & sceneName, bool isStartScene)
{
	std::vector<GameObject *> gameObjs = GameObject::getAllGameObjects();
	unsigned int sizeValue = gameObjs.size();
	for (unsigned int i = 0; i < sizeValue; i++)
		GameObject::deleteGameObjectWithName(gameObjs[i]->getName());
	if (isStartScene)
	{
		initialize(scenes[sceneName]);
		update();
	}
	else
		activeSceneInitFunc = scenes[sceneName];
}

float Game::getDeltaTime() noexcept
{
	return deltaTime;
}

float Game::getTimeSinceStartUp() noexcept
{
	return timeSinceStartUp;
}

void Game::setVsync(int syncRate) noexcept
{
	glfwSwapInterval(syncRate);
}

bool Game::isKeyPressed(const Key& key)
{
	if (glfwGetKey(access->window, (int)key) == GLFW_PRESS)
		return true;
	return false;
}
bool Game::isKeyReleased(const Key& key)
{
	if (glfwGetKey(access->window, (int)key) == GLFW_RELEASE)
		return true;
	return false;
}
void Game::setClearColour(const glm::vec3 colour)
{
	clearColour = colour;
}
const glm::vec2 Game::getWindowSize()
{
	return windowSize;
}
const glm::vec2* Game::getMouseCoords()
{
	double x, y;
	glfwGetCursorPos(access->window, &x, &y);
	mouseCoord.x = (float)x;
	mouseCoord.y = (float)y;
	return &mouseCoord;
}
b2World* Game::getPhysicsWorld()
{
	return access->world.get();
}

void Game::InternalAcess::framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	windowSize = glm::vec2(width, height);
	glViewport(0, 0, width, height);
	frameBufferSizeUpdated = true;
}
