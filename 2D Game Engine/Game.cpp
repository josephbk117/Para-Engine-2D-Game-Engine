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
//#include "imgui.h"
//#include "imgui_impl_glfw_gl3.h"
#include "stb_image_write.h"
#include "AudioManager.h"
#include "Transform.h"
#include "AudioManager.h"
#include "TextureLoader.h"
#include "ShaderProgram.h"
#include "Box.h"
#include "Sprite.h"
#include "GameObject.h"
#include <GLFW\glfw3.h>
#include "GuiElement.h"

bool Game::frameBufferSizeUpated;
float Game::deltaTime;
float Game::timeSinceStartUp;
Camera* Game::camera;
glm::vec2 Game::mouseCoord;
glm::vec2 Game::windowSize;

struct Game::InternalAcess
{
	std::chrono::steady_clock clockTime;
	GLFWwindow* window;
	GLFWcursor* cursor;
	static std::vector<GameObject *> gameObjects;
	static std::unique_ptr<b2World> world;
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};
std::unique_ptr<Game::InternalAcess> Game::access;
std::vector<GameObject *> Game::InternalAcess::gameObjects;
std::unique_ptr<b2World> Game::InternalAcess::world;

void Game::setUpEngine(unsigned int screenWidth, unsigned int screenHeight, std::string title)
{
	access->world = std::make_unique<b2World>(b2Vec2(0, -9.81f));
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
	if (GLEW_OK != err)
		std::cout << "Error: %s\n" << glewGetErrorString(err);
	else
		std::cout << " Glew initialsed" << std::endl;
	//IMGUI_INIT(acess->window, true);
	YSE::System().init();
}

void Game::initialize()
{
	access->gameObjects = GameObject::getAllGameObjects();
	unsigned int size = access->gameObjects.size();
	for (unsigned int i = 0; i < size; i++)
	{
		std::vector<Component*> componentsAttachedToObject = access->gameObjects[i]->getAttachedComponents();
		unsigned int componentCount = componentsAttachedToObject.size();
		if (camera == nullptr)
		{
			if (access->gameObjects[i]->hasComponent<Camera>())
				camera = access->gameObjects[i]->getComponent<Camera>();
		}
		for (unsigned int i = 0; i < componentCount; i++)
			(*componentsAttachedToObject[i]).start();
	}
	if (camera == nullptr)
	{
		std::cout << "\nNo Camera Has Been Attached To An Object\nProviding Default Camera\n";
		camera = new Camera();
		int width, height;
		glfwGetWindowSize(access->window, &width, &height);
		camera->init(glm::vec2(width, height));
	}
	std::stable_sort(access->gameObjects.begin(), access->gameObjects.end(), [](GameObject* a, GameObject* b)
	{return a->getLayerOrder() < b->getLayerOrder(); });
}
//ImVec4 clearColour;
void Game::update()
{
	ShaderProgram shaderGameObjectsBase;
	shaderGameObjectsBase.compileShaders("Test Resources\\spriteBase.vs", "Test Resources\\spriteBase.fs");
	shaderGameObjectsBase.addAttribute("vertexPosition");
	shaderGameObjectsBase.linkShaders();

	ShaderProgram shaderUiElementBase;
	shaderUiElementBase.compileShaders("Test Resources\\uiElementBase.vs", "Test Resources\\uiElementBase.fs");
	shaderUiElementBase.addAttribute("vertexPosition");
	shaderUiElementBase.linkShaders();

	GLint textureGameObjectLocation = shaderGameObjectsBase.getUniformLocation("textureOne");
	GLint uniformProjectionMatrixGameObjectLocation = shaderGameObjectsBase.getUniformLocation("projection");
	GLint uniformModelMatrixGameObjectLocation = shaderGameObjectsBase.getUniformLocation("model");

	GLint textureUiLocation = shaderUiElementBase.getUniformLocation("textureOne");
	GLint uniformModelMatrixUiLocation = shaderUiElementBase.getUniformLocation("model");

	std::chrono::steady_clock::time_point start = access->clockTime.now();
	std::chrono::steady_clock::time_point initialTime = access->clockTime.now();
	deltaTime = 0.0f;
	timeSinceStartUp = 0.0f;

	GuiElement* guiEle = GuiElement::createGuiElement("gui_1");
	guiEle->init(glm::vec2(0.5f, 0.05f), TextureManager::getTextureFromReference("translu"));
	guiEle->setScreenLocation(glm::vec2(-0.5f, 0.95f));

	while (!glfwWindowShouldClose(access->window))
	{
		if (frameBufferSizeUpated)
		{
			int width, height;
			glfwGetWindowSize(access->window, &width, &height);
			std::cout << "\nUpdated to : " << width << " ," << height;
			camera->setScreenRatio(glm::vec2(width, height));
			frameBufferSizeUpated = false;
		}
		YSE::System().update();
		if (access->gameObjects.size() != GameObject::getAllGameObjects().size())
		{
			unsigned int gameObjectCollectionSize = GameObject::getAllGameObjects().size();
			int sizeDiff = gameObjectCollectionSize - access->gameObjects.size();
			if (sizeDiff > 0)
			{
				for (int i = 1; i <= sizeDiff; i++)
				{
					GameObject* gameObjRef = GameObject::getAllGameObjects()[gameObjectCollectionSize - i];
					access->gameObjects.push_back(gameObjRef);
					std::vector<Component*> componentsAttachedToObject = gameObjRef->getAttachedComponents();
					unsigned int componentCount = componentsAttachedToObject.size();
					for (unsigned int i = 0; i < componentCount; i++)
						(*componentsAttachedToObject[i]).start();
				}
			}
			std::stable_sort(access->gameObjects.begin(), access->gameObjects.end(), [](GameObject* a, GameObject* b)
			{return a->getLayerOrder() < b->getLayerOrder(); });
		}
		//IMGUI_NEWFRAME();

		glClear(GL_COLOR_BUFFER_BIT);
		//processInput(window);

		/*for (unsigned int i = 0; i < gameObjects.size(); i++)
		{
			Transform * temp = gameObjects[i]->getComponent<Transform>();
			ImGui::Text("OBJECT : %s is at position = ( %.2f , %.2f ) | Rotation is : %.2f", gameObjects[i]->getName().c_str(),
				temp->position.x, temp->position.y, temp->rotation);
		}
		ImGui::ColorEdit3("BG COLOUR", (float*)&clearColour);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);*/

		//glClearColor(clearColour.x, clearColour.y, clearColour.z, 1.0f);
		glClearColor(0.25f, 0.45f, 0.15f, 1.0f);

		shaderGameObjectsBase.use();
		glm::mat4 matrixTransform;
		glm::mat4 cameraMatrix = camera->getOrthoMatrix();
		glUniformMatrix4fv(uniformProjectionMatrixGameObjectLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));
		glUniform1i(textureGameObjectLocation, 0);

		for (unsigned int i = 0; i < access->gameObjects.size(); i++)
		{
			Transform *transformRef = access->gameObjects[i]->getComponent<Transform>();
			if (access->gameObjects[i]->hasComponent<BoxCollider>())
			{
				BoxCollider* boxcolBody = access->gameObjects[i]->getComponent<BoxCollider>();
				transformRef->position = glm::vec2(boxcolBody->getPosition().x, boxcolBody->getPosition().y);
				transformRef->rotation = boxcolBody->getAngle();
			}
			std::vector<Component*> componentsAttachedToObject =
				GameObject::getGameObjectWithName(access->gameObjects[i]->getName())->getAttachedComponents();
			for (unsigned int i = 0; i < componentsAttachedToObject.size(); i++)
				(*componentsAttachedToObject[i]).update();
			if (camera->isObjectInCameraView(transformRef->position, transformRef->scale))
			{
				glUniformMatrix4fv(uniformModelMatrixGameObjectLocation, 1, GL_FALSE, &(transformRef->getMatrix()[0][0]));
				if (access->gameObjects[i]->hasComponent<Sprite>())
					access->gameObjects[i]->getComponent<Sprite>()->draw();
			}
		}

		//TODO:
		//Make transform component automatically take care of it's physics
		//Maybe each sprite should have reference to it's transform( or modelMatrixLocation and shader used)
		//Attach frame buffer stuff and shader code for screen to camera
		//Shader manager stuff
		//gameobjects in game dynamic deletion support
		shaderGameObjectsBase.unuse();
		glBindTexture(GL_TEXTURE_2D, 0);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		shaderUiElementBase.use();
		std::vector<GuiElement *> elements = GuiElement::getAllGuiElements();
		unsigned int size = elements.size();
		for (int i = 0; i < size; i++)
		{
			glm::mat4 matrix = elements[i]->getMatrix();
			glUniformMatrix4fv(uniformModelMatrixUiLocation, 1, GL_FALSE, &(matrix[0][0]));
			elements[i]->draw();
		}		
		shaderUiElementBase.unuse();
		glDisable(GL_BLEND);
		//ImGui::Render();
		glfwSwapBuffers(access->window);
		glfwPollEvents();

		std::chrono::duration<float> frameTime = access->clockTime.now() - start;
		deltaTime = frameTime.count();
		access->world->Step(deltaTime, 4, 5);
		std::chrono::duration<float> sinceStart = access->clockTime.now() - initialTime;
		timeSinceStartUp = sinceStart.count();

		start = access->clockTime.now();

	}
	//IMGUI_SHUTDOWN();
	YSE::System().close();
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

bool Game::isKeyPressed(Key key)
{
	if (glfwGetKey(access->window, (int)key) == GLFW_PRESS)
		return true;
	return false;
}
bool Game::isKeyReleased(Key key)
{
	if (glfwGetKey(access->window, (int)key) == GLFW_RELEASE)
		return true;
	return false;
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
	frameBufferSizeUpated = true;
}
