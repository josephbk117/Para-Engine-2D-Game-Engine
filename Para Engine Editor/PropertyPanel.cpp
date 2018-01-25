#include "PropertyPanel.h"
#include "imgui.h"
#include "ResourceManager.h"
#include <TextureLoader.h>
#include <Transform.h>
#include <Sprite.h>
#include <iostream>
PropertyPanel PropertyPanel::instance;
PropertyPanel::PropertyPanel()
{
}

void PropertyPanel::display(int screenWidth, int screenHeight)
{
	localScreenWidth = screenWidth;
	localScreenHeight = screenHeight;
	if (hierarchyPanel == nullptr)
	{
		hierarchyPanel = &HierarchyPanel::instance;
		return;
	}
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 1.1f);
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoScrollbar;
	window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	bool *p_open = NULL;
	ImGui::SetNextWindowPos(ImVec2(0, screenHeight - yLimiter), ImGuiSetCond_Always);
	ImGui::SetNextWindowSize(ImVec2(screenWidth - hierarchyPanel->xLimiter, yLimiter), ImGuiSetCond_Always);
	ImGui::Begin("Property Panel", p_open, window_flags);

	GameObject* obj = hierarchyPanel->getActiveGameObj();
	if (obj != nullptr)
	{
		ImGui::BeginGroup();
		std::string text = "Name : " + obj->getName();
		ImGui::Text(text.c_str());
		ImGui::Text("Transform");
		text = "Position : " + std::to_string(obj->getComponent<Transform>()->getPosition().x) + ", ";
		text += std::to_string(obj->getComponent<Transform>()->getPosition().y);
		ImGui::Text(text.c_str());
		ImGui::EndGroup();
		ImGui::SameLine();

		ImGui::BeginGroup();

		std::string filePath;
		unsigned int index = -1;
		if (obj->hasComponent<Sprite>())
		{
			ImGuiIO& io = ImGui::GetIO();
			ImGui::Text("Sprite");
			ImTextureID my_tex_id = (void *)obj->getComponent<Sprite>()->getTextureID();
			float my_tex_w, my_tex_h;
			float ratio;
			const float MAX_SIZE = 100.0f;

			float width, height;
			for (unsigned int i = 0; i < ResourceManager::instance.getImageVector()->size(); i++)
			{
				if (*ResourceManager::instance.getImageVector()->at(i).second.data2 == obj->getComponent<Sprite>()->getTextureID())
				{
					width = ResourceManager::instance.getImageVector()->at(i).second.data1->x;
					height = ResourceManager::instance.getImageVector()->at(i).second.data1->y;
					index = i;
					break;
				}
			}

			if (width > height)
				ratio = MAX_SIZE / width;
			else
				float ratio = MAX_SIZE / height;
			my_tex_w = ratio * width;
			my_tex_h = ratio * height;

			ImVec2 pos = ImGui::GetCursorScreenPos();
			ImGui::Image(my_tex_id, ImVec2(my_tex_w, my_tex_h), ImVec2(1, 1), ImVec2(0, 0), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));
			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				float focus_sz = 32.0f;
				float focus_x = io.MousePos.x - pos.x - focus_sz * 0.5f; if (focus_x < 0.0f) focus_x = 0.0f; else if (focus_x > my_tex_w - focus_sz) focus_x = my_tex_w - focus_sz;
				float focus_y = io.MousePos.y - pos.y - focus_sz * 0.5f; if (focus_y < 0.0f) focus_y = 0.0f; else if (focus_y > my_tex_h - focus_sz) focus_y = my_tex_h - focus_sz;
				ImGui::Text("Min: (%.2f, %.2f)", focus_x / ratio, focus_y / ratio);
				ImGui::Text("Max: (%.2f, %.2f)", (focus_x + focus_sz) / ratio, (focus_y + focus_sz) / ratio);
				ImVec2 uv0 = ImVec2((focus_x) / my_tex_w, (focus_y) / my_tex_h);
				ImVec2 uv1 = ImVec2((focus_x + focus_sz) / my_tex_w, (focus_y + focus_sz) / my_tex_h);
				ImGui::Image(my_tex_id, ImVec2(128, 128), uv1, uv0, ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));
				ImGui::EndTooltip();
			}
			ImGui::Text("%dx%d", (int)width, (int)height);
			filePath = "File Path : ";
			filePath += std::get<0>(ResourceManager::instance.getImageVector()->at(index));
			ImGui::TextWrapped(filePath.c_str());
			std::string fileSize = "File Size : " +
				std::to_string(std::get<1>(ResourceManager::instance.getImageVector()->at(index)).fileSize / 1000.0f) + " KB";
			ImGui::Text(fileSize.c_str());
		}
		ImGui::EndGroup();
	}
	ImGui::End();
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
}

void PropertyPanel::addTexture(const Texture & texture)
{
	textures.push_back(texture);
}

void PropertyPanel::handleInputData()
{
	ImGuiIO& io = ImGui::GetIO();
	if (io.MouseClicked[0] && !isDragging)
	{
		if (io.MouseClickedPos[0].y > (localScreenHeight - yLimiter) - 15 && io.MouseClickedPos[0].y < (localScreenHeight - yLimiter) + 15)
			isDragging = true;
	}
	else if (isDragging && io.MouseClicked[0])
	{
		isDragging = false;
	}
	if (isDragging)
		yLimiter = localScreenHeight - io.MousePos.y;
	yLimiter = glm::clamp(yLimiter, localScreenHeight / 6, localScreenHeight / 3);
}

PropertyPanel::~PropertyPanel()
{
}
