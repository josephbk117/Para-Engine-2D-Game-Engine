#include "Camera.h"
#include <iostream>

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
}

void Camera::setScale(float newScale)
{
	needsUpdate = true;
	scale = newScale;
}

float Camera::getScale()const
{
	return scale;
}

mat4 Camera::getOrthoMatrix()const
{
	return viewMatrix;
}

void Camera::update()
{
	if (*transform != previousTransformData)
	{
		previousTransformData = *transform;
		viewMatrix = glm::scale(orthographicMatrix, vec3(scale, scale, 0.0f));
		viewMatrix = glm::rotate(viewMatrix, transform->rotation, glm::vec3(0, 0, 1));
		viewMatrix = glm::translate(viewMatrix, vec3(-transform->position.x, -transform->position.y, 0));
	}
}

bool Camera::isObjectInCameraView(const vec2 & spritePosition, const vec2& spriteDimensions)const
{
	vec2 scaledScreenDimensions = vec2((float)screenDimensions.x, (float)screenDimensions.y) / (float)scale;

	const float MIN_DISTANCE_X = scaledScreenDimensions.x + (float)spriteDimensions.x;
	const float MIN_DISTANCE_Y = scaledScreenDimensions.y + (float)spriteDimensions.y;

	vec2 distVec = spritePosition - transform->position;

	//Get depth of collision
	float xDepth = MIN_DISTANCE_X - abs(distVec.x);
	float yDepth = MIN_DISTANCE_Y - abs(distVec.y);

	//If both depths are greater than 0 then we collided
	if (xDepth > 0 && yDepth > 0)
		return true;
	return false;
}

void Camera::setScreenRatio(vec2 screenDimension)
{
	orthographicMatrix = ortho(-((float)screenDimensions.x / 2.0f) * (screenDimension.x / screenDimension.y), ((float)screenDimensions.x / 2.0f), -((float)screenDimensions.y / 2.0f), ((float)screenDimensions.y / 2.0f)*(screenDimension.y / screenDimension.x));
	needsUpdate = true;
}
