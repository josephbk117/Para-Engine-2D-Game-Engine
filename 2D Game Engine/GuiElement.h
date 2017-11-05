#pragma once
#include <string>
#include "Sprite.h"
#include "Transform.h"
class GuiElement
{
public:
	GuiElement();
	~GuiElement();

	void init(glm::vec2 dimensions, unsigned int textureID) { uiSprite.init(dimensions.x, dimensions.y); uiSprite.setTextureID(textureID); };
	void setTextureID(unsigned int textureID) { uiSprite.setTextureID(textureID); };

	void setScreenLocation(const glm::vec2& screenPosition) { transform.position = screenPosition; transform.update(); };
	glm::vec2 getScreenLocation()const { return transform.position; };
	void setDimensions(const glm::vec2& dimension) { uiSprite.setDimension(dimension); };
	glm::vec2 getDimensions()const { return uiSprite.getDimensions(); };
	void draw() { uiSprite.draw(); }
	glm::mat4 getModelMatrix()const { return transform.getModelMatrix(); };

	static GuiElement* createGuiElement(const std::string& name)
	{
		GuiElement* gameObject = new GuiElement;
		//gameObjectMap[name] = gameObject;
		guiElementVector.push_back(gameObject);
		return gameObject;
	}
	static std::vector<GuiElement *> getAllGuiElements()
	{
		return guiElementVector;
	}

private:
	Sprite uiSprite;
	Transform transform;
	static std::vector<GuiElement *> guiElementVector;
};

