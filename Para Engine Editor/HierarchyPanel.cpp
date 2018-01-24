#include "HierarchyPanel.h"
#include "imgui.h"
#include <iostream>
#include <Transform.h>

HierarchyPanel HierarchyPanel::instance;
HierarchyPanel::HierarchyPanel()
{
}

void HierarchyPanel::removeGameObjectAtIndex(unsigned int index)
{
	std::string name = GameObject::getAllGameObjects()[index]->getName();
	GameObject::deleteGameObjectWithNameImmediate(name);
	activeElementIndex = -1;
}

void HierarchyPanel::display(int screenWidth, int screenHeight)
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 1.1f);
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoTitleBar;
	window_flags |= ImGuiWindowFlags_MenuBar;
	window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	bool *p_open = NULL;
	ImGui::SetNextWindowPos(ImVec2(screenWidth - xLimiter, 0), ImGuiSetCond_Always);
	ImGui::SetNextWindowSize(ImVec2(xLimiter, screenHeight), ImGuiSetCond_Always);
	ImGui::Begin("Hierarchy", p_open, window_flags);
	ImGui::Text("Hierarchy Of Objects");

	std::vector<GameObject *> localObjs = GameObject::getAllGameObjects();
	for (int i = 0; i < localObjs.size(); i++)
	{
		ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
		if (i == activeElementIndex)
			node_flags |= ImGuiTreeNodeFlags_Selected;
		bool node_open = ImGui::TreeNodeEx(localObjs[i]->getName().c_str(), node_flags);
		if (ImGui::IsItemClicked())
			activeElementIndex = i;
		if (node_open)
		{
			ImGui::Text("Child Stuff");
			ImGui::TreePop();
		}
	}
	ImGui::End();
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
}

GameObject* HierarchyPanel::getActiveGameObj()
{
	if (activeElementIndex == -1)
		return nullptr;
	return GameObject::getAllGameObjects()[activeElementIndex];
}

void HierarchyPanel::handleInputData()
{
	ImGuiIO& io = ImGui::GetIO();
	if (io.KeysDown[io.KeyMap[ImGuiKey_Delete]] && HierarchyPanel::instance.activeElementIndex != -1)
		HierarchyPanel::instance.removeGameObjectAtIndex(HierarchyPanel::instance.activeElementIndex);
}


HierarchyPanel::~HierarchyPanel()
{
}
