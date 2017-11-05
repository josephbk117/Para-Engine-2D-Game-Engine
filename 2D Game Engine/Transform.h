#pragma once
#include <GLM\glm.hpp>
#include "Component.h"

class Transform : public Component
{
public:
	glm::vec2 position = glm::vec2(0.0f, 0.0f);
	float rotation = 0.0f;
	glm::vec2 scale = glm::vec2(1.0f, 1.0f);
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
	glm::mat4 getMatrix()const;
	virtual void update();
	bool operator==(const Transform& transform)const;
	bool operator!=(const Transform& transform)const;
	~Transform() {};
private:
	glm::mat4 modelMatrix = glm::mat4(1.0);
	void setModelMatrix();
};