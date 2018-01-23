#pragma once
#include <Texture.h>
#include <vector>
#include "HierarchyPanel.h"
class PropertyPanel
{
public:
	static PropertyPanel instance;
	PropertyPanel();
	PropertyPanel(const PropertyPanel&) = delete;
	void display(int screenWidth, int screenHeight);
	void addTexture(const Texture & texture);
	~PropertyPanel();
private:
	std::vector<Texture> textures;
	HierarchyPanel* hierarchyPanel = nullptr;
};

