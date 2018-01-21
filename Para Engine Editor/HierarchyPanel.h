#pragma once
#include <vector>
#include <string>
class HierarchyPanel
{
public:
	static HierarchyPanel instance;
	HierarchyPanel();
	HierarchyPanel(const HierarchyPanel&) = delete;
	int activeElement = -1;
	void addGameObject(const std::string gameObject);
	void removeGameObjectAtIndex(unsigned int index);
	void display(int screenWidth, int screenHeight);
	void handleInputData();
	~HierarchyPanel();
private:
	std::vector<std::string> gameObjectHierarchy;
};

