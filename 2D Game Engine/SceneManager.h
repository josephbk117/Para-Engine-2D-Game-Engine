#pragma once
#include "GameObject.h"
class SceneManager
{
public:
	SceneManager() = delete;
	static void SaveSceneData(std::vector<GameObject*> gameObjects, std::string filePath);
};

