#pragma once
#include <vector>
#include <fstream>
#include "GameObject.h"
class SceneManager
{
public:
	SceneManager();
	static void SaveSceneData(std::vector<GameObject*> gameObjects, std::string filePath);
	~SceneManager();
};

