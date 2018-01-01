#pragma once
class b2World;
#include <GLM\glm.hpp>
#include <memory>
#include <functional>
#include <unordered_map>
#include "InputData.h"
#include "Camera.h"
#include "ShaderProgram.h"

class Game
{
public:
	Game() = delete;
	friend class GameObject;
	friend class BoxCollider;
	static void setUpEngine(unsigned int screenWidth, unsigned int screenHeight, const std::string& title);
	static void setCursor(const std::string & cursorImagePath);
	static void hideCursor(bool hide);
	static void lockCursor(bool lock);
	static bool isKeyPressed(Key key);
	static bool isKeyReleased(Key key);
	static const glm::vec2 getWindowSize();
	static const glm::vec2 * getMouseCoords();
	static void cleanUp();
	static void setPostProcessingShader(ShaderProgram program);
	static void addScene(std::function<void()> sceneSetupFunc, const std::string & sceneName);
	static void startScene(const std::string & sceneNameconst, bool isStartScene = false);

	static float getDeltaTime() noexcept
	{
		return deltaTime;
	}
	static float getTimeSinceStartUp() noexcept
	{
		return timeSinceStartUp;
	}
private:
	static bool frameBufferSizeUpated;
	static float deltaTime;
	static float timeSinceStartUp;
	static glm::vec2 mouseCoord;
	static glm::vec2 windowSize;
	static ShaderProgram postProcessor;
	struct InternalAcess;
	static std::unique_ptr<InternalAcess> access;
	struct ContactListener;
	static ContactListener* contactListener;
	static std::unordered_map<std::string, std::function<void()>> scenes;
	static void initialize(std::function<void()> initFunc);
	static std::function<void()> activeSceneInitFunc;
	static void update();
	static b2World* getPhysicsWorld();
};