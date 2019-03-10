#include <iostream>
#include <ParaEngine/Transform.h>

#include "HierarchyPanel.h"
#include "imgui.h"

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
	localScreenWidth = screenWidth;
	localScreenHeight = screenHeight;
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 1.1f);
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	bool *p_open = NULL;
	ImGui::SetNextWindowPos(ImVec2(localScreenWidth - xLimiter, 22), ImGuiSetCond_Always);
	ImGui::SetNextWindowSize(ImVec2(xLimiter, localScreenHeight - 22), ImGuiSetCond_Always);
	ImGui::Begin("Hierarchy Panel", p_open, window_flags);

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
	if (io.MouseClicked[0])
	{
		if (!isDragging)
		{
			if (io.MouseClickedPos[0].x > (localScreenWidth - xLimiter) - 8 && io.MouseClickedPos[0].x < (localScreenWidth - xLimiter) + 8)
				isDragging = true;
		}
		else
		{
			isDragging = false;
			ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
		}
	}
	if (isDragging)
	{
		io.MouseDrawCursor = true;
		ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);
		xLimiter = localScreenWidth - io.MousePos.x;
		xLimiter = glm::clamp(xLimiter, localScreenWidth / 6, localScreenWidth / 4);
	}
}

HierarchyPanel::~HierarchyPanel()
{
}
