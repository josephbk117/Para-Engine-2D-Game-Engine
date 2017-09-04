#include "Camera.h"
#include <iostream>

Camera::Camera()
{
	position = vec2(0.0f, 0.0f);
	orthoMatrix = mat4(1.0f);
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
	orthoMatrix = ortho(0.0f, (float)screenDimensions.x, 0.0f, (float)screenDimensions.y);
}

void Camera::setPosition(const vec2& newPosition)
{
	position = newPosition;
	needsUpdate = true;
}

vec2 Camera::getPosition()
{
	return position;
}

void Camera::setScale(float newScale)
{
	needsUpdate = true;
	scale = newScale;
}

float Camera::getScale()
{
	return scale;
}

mat4 Camera::getOrthoMatrix()
{
	return viewMatrix;
}

void Camera::update()
{
	if (needsUpdate)
	{
		viewMatrix *= glm::scale(orthoMatrix, vec3(scale, scale, 0.0f));
		viewMatrix = translate(orthoMatrix, vec3(-position.x, -position.y, 0));
		needsUpdate = false;
	}
}

bool Camera::isObjectInCameraView(const vec2 & position, const vec2 dimensions)
{
	vec2 scaledScreenDimensions = vec2(screenDimensions.x, screenDimensions.y) / (scale * 2.0f);
	//Minimum distance before collision occurs
	const float MIN_DISTANCE_X = dimensions.x / 2.0f + scaledScreenDimensions.x / 2.0f;
	const float MIN_DISTANCE_Y = dimensions.y / 2.0f + scaledScreenDimensions.y / 2.0f;

	//Center position of the parameters
	vec2 centerPos = position + dimensions / 2.0f;
	//Center position of camera
	vec2 centerCameraPos = position;
	//Vector from input of camera
	vec2 distVec = centerPos - centerCameraPos;

	//Get depth of collision
	float xDepth = MIN_DISTANCE_X - abs(distVec.x);
	float yDepth = MIN_DISTANCE_Y - abs(distVec.y);

	//If either depths are greater than 0 then we collided
	if (xDepth > 0 && yDepth > 0)
		return true;
	return false;
}
