#include "Camera.h"
#include <iostream>
using namespace glm;
Camera::Camera()
{
	orthographicMatrix = mat4(1.0f);
	viewMatrix = mat4(1.0f);
	scale = 1.0f;
	needsUpdate = true;
	screenDimensions = vec2(500, 500);
}

Camera::~Camera()
{

}

void Camera::init(vec2 screenDimensions)
{
	this->screenDimensions = screenDimensions;
	orthographicMatrix = ortho(-((float)screenDimensions.x / 2.0f), ((float)screenDimensions.x / 2.0f), -((float)screenDimensions.y / 2.0f), ((float)screenDimensions.y / 2.0f));
}

void Camera::start()
{
	transform = attachedGameObject->getComponent<Transform>();
	previousTransformData.setRotation(transform->getRotation() + 5);
}

void Camera::setScale(float newScale)
{
	needsUpdate = true;
	scale = newScale;
}

const float& Camera::getScale()const
{
	return scale;
}

const mat4& Camera::getOrthoMatrix()const
{
	return viewMatrix;
}

void Camera::update()
{
	if (*transform != previousTransformData)
	{
		previousTransformData = *transform;
		viewMatrix = glm::scale(orthographicMatrix, vec3(scale, scale, 0.0f));
		viewMatrix = glm::rotate(viewMatrix, transform->getRotation(), glm::vec3(0, 0, 1));
		viewMatrix = glm::translate(viewMatrix, vec3(-transform->getPosition().x, -transform->getPosition().y, 0));
	}
}

bool Camera::isObjectInCameraView(const vec2 & spritePosition, const vec2& spriteDimensions)const
{
	vec2 scaledScreenDimensions = vec2((float)screenDimensions.x, (float)screenDimensions.y) / (float)scale;

	const float MIN_DISTANCE_X = scaledScreenDimensions.x + (float)spriteDimensions.x;
	const float MIN_DISTANCE_Y = scaledScreenDimensions.y + (float)spriteDimensions.y;

	vec2 distVec = spritePosition - transform->getPosition();

	//Get depth of collision
	float xDepth = MIN_DISTANCE_X - abs(distVec.x);
	float yDepth = MIN_DISTANCE_Y - abs(distVec.y);

	//If both depths are greater than 0 then we collided
	if (xDepth > 0 && yDepth > 0)
		return true;
	return false;
}

void Camera::setScreenRatio(const vec2& screenDimension)
{
	orthographicMatrix = ortho(-((float)screenDimensions.x / 2.0f) * (screenDimension.x / screenDimension.y), ((float)screenDimensions.x / 2.0f), -((float)screenDimensions.y / 2.0f), ((float)screenDimensions.y / 2.0f)*(screenDimension.y / screenDimension.x));
	needsUpdate = true;
}

const glm::vec2 Camera::convertScreenPointToWorldPoint(const glm::vec2 & screenPosition, const glm::vec2& screenDimensions)
{
	mat4 model = translate(mat4(1.0f), glm::vec3(-transform->getPosition().x, transform->getPosition().y, 0.0f));
	model = rotate(model, -transform->getRotation(), glm::vec3(0, 0, 1.0f));
	vec4 viewport(0.0f, 0.0f, screenDimensions.x, screenDimensions.y);
	vec3 unprojected = glm::unProject(glm::vec3(screenPosition.x, screenPosition.y, 0.0f), model, orthographicMatrix, viewport);
	return glm::vec2(unprojected.x, -unprojected.y);
}
