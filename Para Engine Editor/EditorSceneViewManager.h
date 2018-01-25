#pragma once
#include <Game.h>
#include <Camera.h>
class EditorSceneViewManager
{
public:
	static EditorSceneViewManager instance;
	EditorSceneViewManager();
	~EditorSceneViewManager();
	void updateSceneView();
private:
	std::vector<GameObject *> gameObjects;
	Camera camera;
};