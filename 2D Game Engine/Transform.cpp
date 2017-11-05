#include "Transform.h"
#include <GLM\gtc\matrix_transform.hpp>
glm::mat4 Transform::getMatrix()const
{
	return modelMatrix;
}
void Transform::update()
{
	setModelMatrix();
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
