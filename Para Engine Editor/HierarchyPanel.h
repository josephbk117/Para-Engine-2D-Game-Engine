#pragma once
#include <vector>
#include <string>
#include <GameObject.h>
class HierarchyPanel
{
public:
	static HierarchyPanel instance;
	HierarchyPanel();
	HierarchyPanel(const HierarchyPanel&) = delete;
	void removeGameObjectAtIndex(unsigned int index);
	void display(int screenWidth, int screenHeight);
	GameObject* getActiveGameObj();
	void handleInputData();
	~HierarchyPanel();
private:
	int activeElementIndex = -1;
};

