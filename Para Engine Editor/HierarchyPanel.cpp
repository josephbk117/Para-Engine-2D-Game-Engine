#include "HierarchyPanel.h"
#include "imgui.h"
#include <iostream>
HierarchyPanel HierarchyPanel::instance;
HierarchyPanel::HierarchyPanel()
{
}
void HierarchyPanel::addGameObject(const std::string gameObject)
{
	gameObjectHierarchy.push_back(gameObject);
}

void HierarchyPanel::removeGameObjectAtIndex(unsigned int index)
{
	gameObjectHierarchy.erase(gameObjectHierarchy.begin() + index);
	activeElement = -1;
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
	ImGui::SetNextWindowPos(ImVec2(screenWidth - 320, 0), ImGuiSetCond_Always);
	ImGui::SetNextWindowSize(ImVec2(320, screenHeight), ImGuiSetCond_Always);
	ImGui::Begin("Hierarchy", p_open, window_flags);
	ImGui::Text("Hierarchy Of Objects");

	for (int i = 0; i < gameObjectHierarchy.size(); i++)
	{
		ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
		if (i == activeElement)
			node_flags |= ImGuiTreeNodeFlags_Selected;
		bool node_open = ImGui::TreeNodeEx(gameObjectHierarchy[i].c_str(), node_flags);
		if (ImGui::IsItemClicked())
			activeElement = i;
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

void HierarchyPanel::handleInputData()
{
	ImGuiIO& io = ImGui::GetIO();
	if (io.KeysDown[io.KeyMap[ImGuiKey_Delete]] && HierarchyPanel::instance.activeElement != -1)
		HierarchyPanel::instance.removeGameObjectAtIndex(HierarchyPanel::instance.activeElement);
}


HierarchyPanel::~HierarchyPanel()
{
}
