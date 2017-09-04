#pragma once
#include "Sprite.h"
#include <GLM\glm.hpp>
#include <GL\glew.h>
#include <Box2D\Box2D.h>
#include "Box.h"
class GameObject
{
public:
	GameObject();
	~GameObject();
	Sprite sprite;
	Box boxCollider;
	void drawObject();
};

