#pragma once
#include <ParaEngine/Texture.h>
#include <vector>
#include "HierarchyPanel.h"
class PropertyPanel
{
public:
	static PropertyPanel instance;
	PropertyPanel();
	PropertyPanel(const PropertyPanel&) = delete;
	int yLimiter = 180;
	void display(int screenWidth, int screenHeight);
	void addTexture(const Texture & texture);
	void handleInputData();
	~PropertyPanel();
private:
	std::vector<Texture> textures;
	HierarchyPanel* hierarchyPanel = nullptr;
	int localScreenWidth, localScreenHeight;
	bool isDragging = false;
};