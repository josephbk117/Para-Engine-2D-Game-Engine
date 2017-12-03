#include "GuiElement.h"

std::vector<GuiElement *> GuiElement::guiElementVector;
GuiElement::GuiElement()
{
}

GuiElement::~GuiElement()
{
}

void GuiElement::addGuiComponent(Component * component)
{
	component->attachedGameObject = this;
	guiComponents.push_back(component);
}
