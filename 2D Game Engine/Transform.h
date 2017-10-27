#pragma once
#include <GLM\glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>
#include "Component.h"

class Transform : public Component
{
public:
	glm::vec2 position;
	float rotation;
	glm::vec2 scale;
	Transform(glm::vec2 _position, float _rotation, glm::vec2 _scale)
	{
		position = _position;
		rotation = _rotation;
		scale = _scale;
		setModelMatrix();
	}
	Transform()
	{
		position = glm::vec2(0, 0);
		rotation = 0.0f;
		scale = glm::vec2(1.0f, 1.0f);
		setModelMatrix();
	}
	glm::mat4 getModelMatrix();
	virtual void update();
	bool operator==(const Transform& transform);
	bool operator!=(const Transform& transform);
	~Transform() {};
private:
	glm::mat4 modelMatrix;
	void setModelMatrix();
};