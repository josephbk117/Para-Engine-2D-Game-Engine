#pragma once
#include <vector>
#include <string>
#include <ParaEngine/GameObject.h>
class HierarchyPanel
{
public:
	static HierarchyPanel instance;
	HierarchyPanel();
	HierarchyPanel(const HierarchyPanel&) = delete;
	int xLimiter = 280;
	void removeGameObjectAtIndex(unsigned int index);
	void display(int screenWidth, int screenHeight);
	GameObject* getActiveGameObj();
	void handleInputData();
	~HierarchyPanel();
private:
	int activeElementIndex = -1;
	int localScreenWidth, localScreenHeight;
	bool isDragging = false;
};

