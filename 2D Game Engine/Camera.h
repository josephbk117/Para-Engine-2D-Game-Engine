#pragma once
#include <GLM\glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>
#include "Component.h"
#include "Transform.h"

using namespace glm;
class Camera : public Component
{
public:
	Camera();
	~Camera();
	void init(vec2 screenDimensions);
	virtual void start();
	virtual void update();
	void setScale(float newScale);
	float getScale()const;
	mat4 getOrthoMatrix()const;
	bool isObjectInCameraView(const vec2 & position, const vec2& dimensions)const;
	void setScreenRatio(vec2 screenDimension);
private:
	vec2 screenDimensions;
	bool needsUpdate;
	Transform* transform;
	Transform previousTransformData;
	mat4 orthographicMatrix;
	mat4 viewMatrix;
	float scale;
};