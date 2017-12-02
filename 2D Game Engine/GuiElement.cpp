#include "GuiElement.h"

std::vector<GuiElement *> GuiElement::guiElementVector;
GuiElement::GuiElement()
{
}

GuiElement::~GuiElement()
{
}

void GuiElement::addGuiComponent(GuiComponent * component)
{
	component->attachedGuiObject = this;
	guiComponents.push_back(component);
}
