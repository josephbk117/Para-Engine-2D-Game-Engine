#pragma once
#include <Game.h>
#include <Camera.h>
#include <ShaderProgram.h>
#include <GL\glew.h>
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
	ShaderProgram shaderGameObjectsBase;
	GLint textureGameObjectLocation;
	GLint uniformProjectionMatrixGameObjectLocation;
	GLint uniformModelMatrixGameObjectLocation;
};