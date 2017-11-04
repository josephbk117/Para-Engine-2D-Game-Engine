#pragma once
#include <string>
#include <GL\glew.h>
#include "Transform.h"
class GuiElement
{
public:
	GuiElement();
	~GuiElement();

	void setLayerOrder(int order) { this->layerOrder = order; }
	int getLayerOrder()const { return layerOrder; }
	void setName(const std::string & name) { this->name = name; }
	std::string getName()const { return name; }
	void setScreenLocation(const glm::vec2& screenPosition) { transform.position = screenPosition; };
	glm::vec2 getScreenLocation()const { return transform.position; };
	void setDimensions(const glm::vec2& dimensions) { transform.scale = dimensions; };
	glm::vec2 getDimensions()const { return transform.scale; };
	void display(unsigned int textID)
	{
		glColor4f(0.4f, 0.7f, 0.25f, 0.7f);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glBindTexture(GL_TEXTURE_2D,textID);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex2f(transform.position.x, transform.position.y);
		glTexCoord2f(0, 1);
		glVertex2f(transform.position.x, transform.position.y + transform.scale.y);
		glTexCoord2f(1, 1);
		glVertex2f(transform.position.x + transform.scale.x, transform.position.y + transform.scale.y);
		glTexCoord2f(1, 0);
		glVertex2f(transform.position.x + transform.scale.x, transform.position.y);
		glEnd();
		glDisable(GL_BLEND);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
private:
	std::string name;
	int layerOrder;
	Transform transform;
};

