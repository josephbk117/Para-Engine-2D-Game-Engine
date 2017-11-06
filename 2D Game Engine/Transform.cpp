#include "Transform.h"
#include <GLM\gtc\matrix_transform.hpp>
const glm::mat4& Transform::getMatrix()const
{
	return modelMatrix;
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
void Transform::setX(const float & xValue)
{
	setPosition(glm::vec2(xValue, position.y));
}
void Transform::setY(const float & yValue)
{
	setPosition(glm::vec2(position.x, yValue));
}
void Transform::setRotation(const float & rotation)
{
	needsUpdate = true;
	this->rotation = rotation;
}
void Transform::setScale(const glm::vec2 scale)
{
	needsUpdate = true;
	this->scale = scale;
}
const glm::vec2 & Transform::getPosition()const
{
	return position;
}
const float & Transform::getRotation()const
{
	return rotation;
}
const glm::vec2 Transform::getScale()const
{
	return scale;
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
	modelMatrix = glm::rotate(modelMatrix, rotation, glm::vec3(0, 0, 1.0f));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(scale.x, scale.y, 0));
}
