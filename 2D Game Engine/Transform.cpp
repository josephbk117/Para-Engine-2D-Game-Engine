#include <iostream>
#include "Transform.h"
#include <GLM\gtc\matrix_transform.hpp>

Transform::Transform(const glm::vec2 & _position, const float & _rotation, const glm::vec2 & _scale) noexcept
{
	position = _position;
	rotation = _rotation;
	scale = _scale;
	setModelMatrix();
}

Transform::Transform() noexcept
{
	setModelMatrix();
}

const glm::mat4& Transform::getMatrix()const
{
	return modelMatrix;
}
void Transform::start()
{
}
void Transform::update()
{
	if (needsUpdate)
	{
		setModelMatrix();
		needsUpdate = false;
	}
}
void Transform::setPosition(const glm::vec2 & position)
{
	needsUpdate = true;
	this->position = position;
}
const glm::mat4 Transform::getWorldSpaceTransform()
{
	glm::mat4 worldTransform = modelMatrix;
	Transform* parentTransform = parent;
	while (parentTransform != nullptr)
	{
		worldTransform = parentTransform->modelMatrix * worldTransform;
		parentTransform = parentTransform->parent;
	}
	return worldTransform;
}
void Transform::setX(float xValue)
{
	setPosition(glm::vec2(xValue, position.y));
}
void Transform::setY(float yValue)
{
	setPosition(glm::vec2(position.x, yValue));
}
void Transform::setRotation(float rotation)
{
	needsUpdate = true;
	this->rotation = rotation;
}
void Transform::setScale(const glm::vec2& scale)
{
	needsUpdate = true;
	this->scale = scale;
}
const glm::vec2 & Transform::getPosition()const
{
	return position;
}
float Transform::getRotation()const
{
	return rotation;
}
const glm::vec2& Transform::getScale()const
{
	return scale;
}
void Transform::setParent(Transform * parentTransform)
{
	parentTransform->children.push_back(this);
	if (parent != nullptr)
	{
		auto it = std::find(parent->children.begin(), parent->children.end(), this);
		if (it != parent->children.end())
			parent->children.erase(it);
	}
	parent = parentTransform;
}
const Transform * Transform::getParent()
{
	return parent;
}
void Transform::addChild(Transform * child)
{
	child->parent = this;
	children.push_back(child);
}
bool Transform::operator==(const Transform & transform)const
{
	return (position == transform.position && rotation == transform.rotation && scale == transform.scale);
}
bool Transform::operator!=(const Transform & transform)const
{
	return (position != transform.position || rotation != transform.rotation || scale != transform.scale);
}
void Transform::setModelMatrix()
{
	modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0));
	modelMatrix = glm::rotate(modelMatrix, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(scale.x, scale.y, 0));
}
