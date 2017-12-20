#pragma once
#include <GLM\glm.hpp>
#include "Component.h"

class Transform : public Component
{
public:
	
	Transform(const glm::vec2& _position, const float& _rotation, const glm::vec2& _scale) noexcept
	{
		position = _position;
		rotation = _rotation;
		scale = _scale;
		setModelMatrix();
	}
	Transform() noexcept
	{
		setModelMatrix();
	}
	const glm::mat4& getMatrix()const;
	virtual void start();
	virtual void update();
	void setPosition(const glm::vec2& position);
	void setX(float xValue);
	void setY(float yValue);
	void setRotation(float rotation);
	void setScale(const glm::vec2& scale);
	const glm::vec2& getPosition()const;
	float getRotation()const;
	const glm::vec2& getScale()const;
	bool operator==(const Transform& transform)const;
	bool operator!=(const Transform& transform)const;
private:
	glm::mat4 modelMatrix = glm::mat4(1.0);
	glm::vec2 scale = glm::vec2(1.0f, 1.0f);
	glm::vec2 position = glm::vec2(0.0f, 0.0f);
	float rotation = 0.0f;
	bool needsUpdate = true;
	void setModelMatrix();
};